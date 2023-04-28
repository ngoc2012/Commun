/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/21 23:03:18 by ngoc             ###   ########.fr       */
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

void	*thread_stopped(void *a0)
{
	t_academy	*a;

	a = (t_academy *) a0;
	sem_wait(a->sem_died[a->id - 1]);
	if (!set_sem(&a->died, 1, &a->sem_die))
		end_process(a, 1);
	return ((void *) NULL);
}

void	print_now_sem(t_academy *a, char *s)
{
	struct timeval	tv;

	if (sem_wait(a->sem_write) < 0)
		end_process(a, 1);
	printf("%d %d %s\n", now_time_interval(&tv, &a->t0) / 1000, a->id, s);
	if (sem_post(a->sem_write) < 0)
		end_process(a, 1);
}

void	*thread_died(void *a0)
{
	t_academy		*a;
	int				i;
	struct timeval	tv;

	a = (t_academy *) a0;
	while (!get_sem(&a->died, &a->sem_die))
	{
		usleep(1);
		if ((get_sem(&a->eated, &a->sem_last_eat) || a->n_ph == 1)
			&& now_time_interval(&tv, &a->last_eat) > a->t_d)
		{
			i = -1;
			while (++i < a->n_ph)
				sem_post(a->sem_died[i]);
			print_now_sem(a, "died");
			if (!set_sem(&a->died, 1, &a->sem_die))
				end_process(a, 1);
			if (sem_post(&a->sem_last_eat) < 0)
				end_process(a, 1);
			break ;
		}
	}
	if (a->n_ph == 1)
		sem_post(a->sem_forks);
	return ((void *) NULL);
}
