/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/28 14:59:29 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start(t_academy *a)
{
	int		i;
	char	start;

	//printf("start0");
	start = 0;
	while (!start)
	{
		start = 1;
		i = -1;
		while (++i < a->n_ph)
			if (!m_get(&a->phs[i].created, &a->phs[i].m_p))
				start = 0;
		usleep(1);
	}
	//printf("start");
	m_set(&a->start, 1, &a->m_a);
	gettimeofday(&a->t0, NULL);
	i = -1;
	while (++i < a->n_ph)
	{
		a->phs[i].last_eat = a->t0;
		a->phs[i].last_eat0 = a->t0;
	}
}

void	eated(t_academy *a)
{
	int		i;
	char	eated;

	eated = 0;
	while (!eated)
	{
		eated = 1;
		i = -1;
		while (++i < a->n_ph)
			if (!m_get(&a->phs[i].eated, &a->phs[i].m_p))
				eated = 0;
		usleep(1);
	}
}

void	check(t_academy *a)
{
	int		i;
	struct timeval	tv;
	struct timeval	last_eat;

	//printf("check0\n");
	start(a);
	eated(a);
	while (!m_get(&a->died, &a->m_a))
	{
		i = -1;
		while (++i < a->n_ph)
		{
			last_eat = m_get_time(&a->phs[i].last_eat0, &a->phs[i].m_p);
			if (now_time_interval(&tv, &last_eat) > a->t_d
					&& m_get(&a->phs[i].eated, &a->phs[i].m_e))
			{
				m_set(&a->died, 1, &a->m_a);
				pthread_mutex_lock(&a->m_write);
				printf("%d %d died\n", get_time_interval(&tv, &a->t0), a->phs[i].id);
				pthread_mutex_unlock(&a->m_write);
				return ;
			}
		}
	}
	//printf("check1\n");
}
