/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/21 00:49:13 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <signal.h>

char	get_sem(char *v, sem_t *s)
{
	char	i;

	if (sem_wait(s) < 0)
		return (-1);
	i = *v;
	if (sem_post(s) < 0)
		return (-1);
	return (i);
}

char	set_sem(char *v, int v0, sem_t *s)
{
	if (sem_wait(s) < 0)
		return (0);
	*v = v0;
	if (sem_post(s) < 0)
		return (0);
	return (1);
}

void    *thread_stopped(void *a0)
{
	t_academy	*a;

	a = (t_academy *) a0;
	sem_wait(a->sem_died[a->id - 1]);
	if (!set_sem(&a->died, 1, &a->sem_die))
		end_process(a, 1);
	//struct timeval	tv;
	//printf("%d %d stopped\n", now_time_interval(&tv, &a->t0), a->id);
	return ((void *) NULL);
}

void    *thread_died(void *a0)
{
	t_academy	*a;
	int	i;
	struct timeval	tv;

	a = (t_academy *) a0;
	while (!get_sem(&a->died, &a->sem_die))
	{
		usleep(1);
		if (sem_wait(&a->sem_last_eat) < 0)
			end_process(a, 1);
		if ((a->eated || a->n_ph == 1) && now_time_interval(&tv, &a->last_eat) > a->t_d)
		{
			i = -1;
			while (++i < a->n_ph)
				sem_post(a->sem_died[i]);
			if (!set_sem(&a->died, 1, &a->sem_die))
				end_process(a, 1);
			if (sem_wait(a->sem_write) < 0)
				end_process(a, 1);
			printf("%d %d died\n", get_time_interval(&tv, &a->t0), a->id);
			if (sem_post(a->sem_write) < 0)
				end_process(a, 1);
			if (sem_post(&a->sem_last_eat) < 0)
				end_process(a, 1);
			break ;
		}
		if (sem_post(&a->sem_last_eat) < 0)
			end_process(a, 1);
	}
	if (a->n_ph == 1)
		sem_post(a->sem_forks);
	//sem_post(a->sem_forks);
	//printf("%d %d out of died\n", now_time_interval(&tv, &a->t0), a->id);
	return ((void *) NULL);
}

void	philo(t_academy	*a, int i)
{
	int	n_e;

	if (pthread_create(&a->th_stopped, NULL, &thread_stopped, a))
		end_process(a, 1);
	if (pthread_create(&a->th_died, NULL, &thread_died, a))
		end_process(a, 1);
	sem_post(a->sem_started[i]);
	sem_wait(a->sem_start);
	n_e = 0;
	if (a->t_d > 2 * a->t_e)
		usleep((i % 2) * a->t_e + (i / 2) * (a->t_d - a->t_e * 2) / a->n_ph);
	else
		usleep((i % 2) * a->t_e + (i / 2) * a->t_e / a->n_ph);
	while (a->n_e == -1 || n_e <= a->n_e)
	{
		sem_wait(a->sem_forks);

		if (get_sem(&a->died, &a->sem_die))
		{
			sem_post(a->sem_forks);
			break ;
		}

		if (sem_wait(a->sem_write) < 0)
			end_process(a, 1);
		printf("%d %d has taken a fork\n", now_time_interval(&a->tv, &a->t0) / 1000, a->id);
		if (sem_post(a->sem_write) < 0)
			end_process(a, 1);

		sem_wait(a->sem_forks);

		if (sem_wait(&a->sem_last_eat) < 0)
			end_process(a, 1);
		gettimeofday(&a->last_eat, NULL);
		if (sem_post(&a->sem_last_eat) < 0)
			end_process(a, 1);

		if (get_sem(&a->died, &a->sem_die))
		{
			sem_post(a->sem_forks);
			break ;
		}

		if (sem_wait(a->sem_write) < 0)
			end_process(a, 1);
		printf("%d %d has taken a fork\n", get_time_interval(&a->last_eat, &a->t0), a->id);
		printf("%d %d is eating\n", get_time_interval(&a->last_eat, &a->t0), a->id);
		//printf("%d %d is eating%d\n", get_time_interval(&a->last_eat, &a->t0), a->id, n_e + 1);
		if (sem_post(a->sem_write) < 0)
			end_process(a, 1);

		if (sem_wait(&a->sem_last_eat) < 0)
			end_process(a, 1);
		a->eated = 1;
		if (sem_post(&a->sem_last_eat) < 0)
			end_process(a, 1);

		while (now_time_interval(&a->last_sleep, &a->last_eat) < a->t_e)
			;
		if (sem_post(a->sem_forks) < 0)
			end_process(a, 1);
		if (sem_post(a->sem_forks) < 0)
			end_process(a, 1);
		n_e++;
		if (n_e == a->n_e)
			break ;
		if (get_sem(&a->died, &a->sem_die))
			break ;

		if (sem_wait(a->sem_write) < 0)
			end_process(a, 1);
		printf("%d %d is sleeping\n", get_time_interval(&a->last_sleep, &a->t0), a->id);
		if (sem_post(a->sem_write) < 0)
			end_process(a, 1);
		
		while (now_time_interval(&a->last_think, &a->last_sleep) < a->t_s)
			;

		if (get_sem(&a->died, &a->sem_die))
			break ;

		if (sem_wait(a->sem_write) < 0)
			end_process(a, 1);
		printf("%d %d is thinking\n", get_time_interval(&a->last_think, &a->t0), a->id);
		if (sem_post(a->sem_write) < 0)
			end_process(a, 1);

		while (now_time_interval(&a->tv, &a->last_think) < a->t_t)
			;

		if (get_sem(&a->died, &a->sem_die))
			break ;
	}
	//printf("%d %d end\n", now_time_interval(&a->last_think, &a->t0), a->id);
	sem_post(a->sem_died[i]);
	if (pthread_join(a->th_stopped, NULL))
		end_process(a, 1);
	if (pthread_join(a->th_died, NULL))
		end_process(a, 1);
	end_process(a, 3);
}
