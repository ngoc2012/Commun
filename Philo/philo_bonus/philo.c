/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/30 07:46:25 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <signal.h>

int	eating(t_academy *a)
{
	sem_wait(a->sem_forks);
	if (get_sem(&a->died, a->sem_die))
	{
		sem_post(a->sem_forks);
		return (0);
	}
	print_now_sem(a, "has taken a fork");
	sem_wait(a->sem_forks);
	sem_wait(a->sem_last_eat);
	gettimeofday(&a->last_eat, NULL);
	sem_post(a->sem_last_eat);
	if (get_sem(&a->died, a->sem_die))
	{
		sem_post(a->sem_forks);
		return (0);
	}
	sem_wait(a->sem_write);
	printf("%d %d has taken a fork\n",
		get_time_interval(&a->last_eat, &a->t0), a->id);
	printf("%d %d is eating\n", get_time_interval(&a->last_eat, &a->t0), a->id);
	sem_post(a->sem_write);
	set_sem(&a->eated, 1, a->sem_last_eat);
	while (now_time_interval(&a->last_sleep, &a->last_eat) < a->t_e)
		;
	return (1);
}

int	sleeping(t_academy *a, int *n_e)
{
	sem_post(a->sem_forks);
	sem_post(a->sem_forks);
	(*n_e)++;
	if (*n_e == a->n_e)
		return (0);
	if (get_sem(&a->died, a->sem_die))
		return (0);
	print_sem(a, &a->last_sleep, "is sleeping");
	while (now_time_interval(&a->last_think, &a->last_sleep) < a->t_s)
		;
	if (get_sem(&a->died, a->sem_die))
		return (0);
	print_sem(a, &a->last_think, "is thinking");
	while (now_time_interval(&a->tv, &a->last_think) < a->t_t)
		;
	if (get_sem(&a->died, a->sem_die))
		return (0);
	return (1);
}

void	create_thread(t_academy *a, int i)
{
	if (pthread_create(&a->th_stopped, NULL, &thread_stopped, a))
	{
		sem_post(a->sem_died[i]);
		sem_post(a->sem_started[i]);
		end_process(a, EXIT_FAILURE);
	}
	if (pthread_create(&a->th_died, NULL, &thread_died, a))
	{
		sem_post(a->sem_died[i]);
		sem_post(a->sem_started[i]);
		pthread_join(a->th_stopped, NULL);
		end_process(a, EXIT_FAILURE);
	}
}

void	end_thread(t_academy *a, int i)
{
	sem_post(a->sem_died[i]);
	if (pthread_join(a->th_stopped, NULL))
		end_process(a, EXIT_FAILURE);
	if (pthread_join(a->th_died, NULL))
		end_process(a, EXIT_FAILURE);
	end_process(a, EXIT_SUCCESS);
}

void	philo(t_academy *a, int i)
{
	int	n_e;

	create_thread(a, i);
	sem_post(a->sem_started[i]);
	sem_wait(a->sem_start);
	n_e = 0;
	if (a->t_d > 2 * a->t_e)
		usleep((i % 2) * a->t_e + (i / 2) * (a->t_d - a->t_e * 2) / a->n_ph);
	else
		usleep((i % 2) * a->t_e + (i / 2) * a->t_e / a->n_ph);
	while (a->n_e == -1 || n_e <= a->n_e)
	{
		if (!eating(a))
			break ;
		if (!sleeping(a, &n_e))
			break ;
	}
	end_thread(a, i);
}
