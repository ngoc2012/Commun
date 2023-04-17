/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/17 00:11:11 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <signal.h>

void	end_process(t_academy *a, int erro)
{
	int	i;

	sem_close(a->sem_forks);
	sem_close(a->sem_write);
	sem_destroy(&a->sem_has_fork);
	i = -1;
	while (++i < a->n_ph)
	{
		free(a->sem_died_str[i]);
		sem_close(a->sem_died[i]);
		free(a->sem_started_str[i]);
		sem_close(a->sem_started[i]);
	}
	free(a->sem_died);
	free(a->sem_died_str);
	free(a->sem_started);
	free(a->sem_started_str);
	free(a->phs);
	exit(erro);
}

t_academy	*g_a;

void	handler(int sig)
{
	if (sig == SIGUSR1)
		return ;
	end_process(g_a, EXIT_SUCCESS);
}

void    *thread_fork(void *a0)
{
	t_academy	*a;

	a = (t_academy *) a0;
	//printf("%d %d try to take fork\n", now_time_interval(&a->tv, &a->t0), a->id);
	if (sem_wait(a->sem_forks) < 0)
		end_process(a, 1);
	sem_wait(&a->sem_has_fork);
	a->has_fork = 1;
	sem_post(&a->sem_has_fork);
	return ((void *) NULL);
}

void    get_fork(t_academy *a)
{
	pthread_t	th;
	int	i;
	int	has_fork;

	a->has_fork = 0;
	has_fork = 0;
	if (pthread_create(&th, NULL, &thread_fork, a))
		end_process(a, 1);
	while (!has_fork)
	{
		if (a->eated && now_time_interval(&a->tv, &a->last_eat) > a->t_d)
		{
			i = -1;
			while (++i < a->n_ph)
				sem_wait(a->sem_died[i]);
			usleep((a->n_ph + 10) * DELAY);
			if (pthread_join(th, NULL))
				end_process(a, 1);
			end_process(a, 4);
		}
		sem_wait(&a->sem_has_fork);
		has_fork = a->has_fork;
		sem_post(&a->sem_has_fork);
		usleep(1);
	}
	if (pthread_join(th, NULL))
		end_process(a, 1);
}

void	philo(t_academy	*a, int i)
{
	int			n_e;
	struct sigaction	act;

	g_a = a;
	act.sa_flags = SA_NODEFER;
	act.sa_handler = &handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	n_e = 0;
	a->sem_forks = sem_open(SEM_FORKS, O_RDWR);
	a->sem_write = sem_open(SEM_WRITE, O_RDWR);
	if (sem_init(&a->sem_has_fork, 0, 1))
		end_process(a, 1);
	if (a->sem_forks == SEM_FAILED || a->sem_write == SEM_FAILED)
		end_process(a, 1);
	i = -1;
	while (++i < a->n_ph)
	{
		a->sem_died[i] = sem_open(a->sem_died_str[i], O_RDWR);
		if (a->sem_died[i] == SEM_FAILED)
			end_process(a, 1);
	}
	i = -1;
	while (++i < a->n_ph)
	{
		a->sem_started[i] = sem_open(a->sem_started_str[i], O_RDWR);
		if (a->sem_started[i] == SEM_FAILED)
			end_process(a, 1);
	}
	usleep((i % 2) * a->t_e);
	while (a->n_e == -1 || n_e <= a->n_e)
	{
		get_fork(a);

		if (sem_wait(a->sem_write) < 0)
			end_process(a, 1);
		printf("%d %d has taken a fork\n", now_time_interval(&a->tv, &a->t0), a->id);
		if (sem_post(a->sem_write) < 0)
			end_process(a, 1);

		if (a->n_ph == 1)
			a->eated = 1;
		get_fork(a);

		if (sem_wait(a->sem_write) < 0)
			end_process(a, 1);
		printf("%d %d has taken a fork\n", now_time_interval(&a->last_eat, &a->t0), a->id);
		printf("%d %d is eating\n", get_time_interval_micro(&a->last_eat, &a->t0), a->id);
		if (sem_post(a->sem_write) < 0)
			end_process(a, 1);

		a->eated = 1;
		while (now_time_interval(&a->last_sleep, &a->last_eat) < a->t_e)
			;
		if (sem_post(a->sem_forks) < 0)
			end_process(a, 1);
		if (sem_post(a->sem_forks) < 0)
			end_process(a, 1);
		n_e++;
		if (n_e == a->n_e)
			end_process(a, 3);

		if (sem_wait(a->sem_write) < 0)
			end_process(a, 1);
		printf("%d %d is sleeping\n", get_time_interval_micro(&a->last_sleep, &a->t0), a->id);
		if (sem_post(a->sem_write) < 0)
			end_process(a, 1);

		while (now_time_interval(&a->last_think, &a->last_sleep) < a->t_s)
			;
		if (a->eated && now_time_interval(&a->last_think, &a->last_eat) > a->t_d)
			end_process(a, 4);

		if (sem_wait(a->sem_write) < 0)
			end_process(a, 1);
		printf("%d %d is thinking\n", get_time_interval_micro(&a->last_think, &a->t0), a->id);
		if (sem_post(a->sem_write) < 0)
			end_process(a, 1);

		while (now_time_interval(&a->tv, &a->last_think) < a->t_t)
			;
	}
	end_process(a, 3);
}
