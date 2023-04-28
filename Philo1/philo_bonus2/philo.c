/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/19 16:07:41 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <signal.h>

void    *thread_stopped(void *a0)
{
	t_academy	*a;
	struct timeval	tv;

	a = (t_academy *) a0;
	sem_wait(a->sem_write);
	printf("%d %d thread stopped\n", now_time_interval(&tv, &a->t0), a->id);
	sem_post(a->sem_write);
//	sem_wait(a->sem_died[a->id - 1]);
//	if (sem_wait(&a->sem_die) < 0)
//		end_process(a, 1);
//	a->died = 1;
//	if (sem_post(&a->sem_die) < 0)
//		end_process(a, 1);
	return ((void *) NULL);
}

void    *thread_died(void *a0)
{
	t_academy	*a;
	//int	i;
	struct timeval	tv;

	a = (t_academy *) a0;
	sem_wait(a->sem_write);
	printf("%d %d thread died\n", now_time_interval(&tv, &a->t0), a->id);
	sem_post(a->sem_write);
//	if (sem_wait(&a->sem_die) < 0)
//		end_process(a, 1);
//	while (!a->died)
//	{
//		if (sem_post(&a->sem_die) < 0)
//			end_process(a, 1);
//		usleep(1);
//		if (sem_wait(&a->sem_last_eat) < 0)
//			end_process(a, 1);
//		if ((a->eated || a->n_ph == 1) && now_time_interval(&tv, &a->last_eat) > a->t_d)
//		{
//			i = -1;
//			while (++i < a->n_ph)
//				sem_post(a->sem_died[i]);
//			if (sem_wait(a->sem_write) < 0)
//				end_process(a, 1);
//			printf("%d %d died\n", get_time_interval_micro(&tv, &a->t0), a->id);
//			if (sem_post(a->sem_write) < 0)
//				end_process(a, 1);
//			if (sem_post(&a->sem_last_eat) < 0)
//				end_process(a, 1);
//			break ;
//		}
//		if (sem_post(&a->sem_last_eat) < 0)
//			end_process(a, 1);
//		if (sem_wait(&a->sem_die) < 0)
//			end_process(a, 1);
//	}
//	if (a->n_ph == 1)
//		sem_post(a->sem_forks);
//	if (sem_post(&a->sem_die) < 0)
//		end_process(a, 1);
	return ((void *) NULL);
}

void	philo(t_academy	*a, int i)
{
	int			n_e;

	if (pthread_create(&a->th_stopped, NULL, &thread_stopped, a))
		end_process(a, 1);
	if (pthread_create(&a->th_died, NULL, &thread_died, a))
		end_process(a, 1);
	//sem_post(a->sem_started[i]);
	//sem_wait(a->sem_start);
	n_e = 0;
	usleep((i % 2) * a->t_e);
	while (a->n_e == -1 || n_e <= a->n_e)
	{
		sem_wait(a->sem_forks);

		if (sem_wait(&a->sem_die) < 0)
			end_process(a, 1);
		if (a->died)
		{
			if (sem_post(&a->sem_die) < 0)
				end_process(a, 1);
			break ;
		}
		if (sem_post(&a->sem_die) < 0)
			end_process(a, 1);

		if (sem_wait(a->sem_write) < 0)
			end_process(a, 1);
		printf("%d %d has taken a fork\n", now_time_interval(&a->tv, &a->t0), a->id);
		if (sem_post(a->sem_write) < 0)
			end_process(a, 1);

		sem_wait(a->sem_forks);

		if (sem_wait(&a->sem_last_eat) < 0)
			end_process(a, 1);
		gettimeofday(&a->last_eat, NULL);
		if (sem_post(&a->sem_last_eat) < 0)
			end_process(a, 1);

		if (sem_wait(&a->sem_die) < 0)
			end_process(a, 1);
		if (a->died)
		{
			if (sem_post(&a->sem_die) < 0)
				end_process(a, 1);
			break ;
		}
		if (sem_post(&a->sem_die) < 0)
			end_process(a, 1);

		if (sem_wait(a->sem_write) < 0)
			end_process(a, 1);
		printf("%d %d has taken a fork\n", get_time_interval_micro(&a->last_eat, &a->t0), a->id);
		printf("%d %d is eating\n", get_time_interval_micro(&a->last_eat, &a->t0), a->id);
		//printf("%d %d is eating%d\n", get_time_interval_micro(&a->last_eat, &a->t0), a->id, n_e + 1);
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

		if (sem_wait(&a->sem_die) < 0)
			end_process(a, 1);
		if (n_e == a->n_e || a->died)
		{
			if (sem_post(&a->sem_die) < 0)
				end_process(a, 1);
			break ;
		}
		if (sem_post(&a->sem_die) < 0)
			end_process(a, 1);

		if (sem_wait(a->sem_write) < 0)
			end_process(a, 1);
		printf("%d %d is sleeping\n", get_time_interval_micro(&a->last_sleep, &a->t0), a->id);
		if (sem_post(a->sem_write) < 0)
			end_process(a, 1);
		
		while (now_time_interval(&a->last_think, &a->last_sleep) < a->t_s)
			;
		if (a->eated && now_time_interval(&a->last_think, &a->last_eat) > a->t_d)
			end_process(a, 4);

		if (sem_wait(&a->sem_die) < 0)
			end_process(a, 1);
		if (a->died)
		{
			if (sem_post(&a->sem_die) < 0)
				end_process(a, 1);
			break ;
		}
		if (sem_post(&a->sem_die) < 0)
			end_process(a, 1);

		if (sem_wait(a->sem_write) < 0)
			end_process(a, 1);
		printf("%d %d is thinking\n", get_time_interval_micro(&a->last_think, &a->t0), a->id);
		if (sem_post(a->sem_write) < 0)
			end_process(a, 1);

		while (now_time_interval(&a->tv, &a->last_think) < a->t_t)
			;
	}
	sem_post(a->sem_died[i]);
	if (pthread_join(a->th_stopped, NULL))
		end_process(a, 1);
	if (pthread_join(a->th_died, NULL))
		end_process(a, 1);
	end_process(a, 3);
}
