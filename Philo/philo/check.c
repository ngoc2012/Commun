/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/29 15:27:57 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start(t_academy *a)
{
	int		i;
	char	all_created;

	all_created = 0;
	while (!all_created)
	{
		all_created = 1;
		i = -1;
		while (++i < a->n_ph)
			if (!m_get(&a->phs[i].created, &a->phs[i].m_p))
				all_created = 0;
		usleep(1);
	}
	i = -1;
	while (++i < a->n_ph)
		m_set(&a->phs[i].started, 1, &a->phs[i].m_s);
	gettimeofday(&a->t0, NULL);
	i = -1;
	while (++i < a->n_ph)
	{
		a->phs[i].last_eat = a->t0;
		a->phs[i].last_eat0 = a->t0;
	}
}

static void	die(t_academy *a, struct timeval *tv, int i)
{
	m_set(&a->died, 1, &a->m_a);
	pthread_mutex_lock(&a->m_write);
	printf("%d %d died\n", get_time_interval(tv, &a->t0),
		a->phs[i].id);
	pthread_mutex_unlock(&a->m_write);
}

void	check(t_academy *a)
{
	int				i;
	int				n_finished;
	struct timeval	tv;
	struct timeval	last_eat;

	n_finished = 1;
	start(a);
	while (!m_get(&a->died, &a->m_a) && n_finished)
	{
		n_finished = 0;
		i = -1;
		while (++i < a->n_ph && !m_get(&a->phs[i].finished, &a->phs[i].m_f))
		{
			last_eat = m_get_time(&a->phs[i].last_eat0, &a->phs[i].m_p);
			if (now_time_interval(&tv, &last_eat) > a->t_d
				&& m_get(&a->phs[i].eated, &a->phs[i].m_e))
			{
				die(a, &tv, i);
				return ;
			}
			n_finished++;
		}
		usleep(1);
	}
}
