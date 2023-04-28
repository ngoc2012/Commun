/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/28 14:29:26 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start(t_academy *a)
{
	int		i;
	char	start;

	printf("start0");
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
	printf("start");
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

int	died(t_academy *a, t_philo *ph, char *finished)
{
	struct timeval	tv;
	struct timeval	last_eat;
	char			finished0;

	printf("died0\n");
	finished0 = m_get(&ph->finished, &ph->m_f);
	if (!finished0)
	{
		last_eat = m_get_time(&ph->last_eat0, &ph->m_p);
		if (now_time_interval(&tv, &last_eat) > a->t_d
			&& m_get(&ph->eated, &ph->m_e))
		{
			m_set(&a->died, 1, &a->m_a);
			pthread_mutex_lock(&a->m_write);
			printf("%d %d died\n", get_time_interval(&tv, &a->t0), ph->id);
			pthread_mutex_unlock(&a->m_write);
			return (1);
		}
		*finished = 0;
	}
	printf("died1\n");
	return (0);
}

void	check(t_academy *a)
{
	char	finished;
	int		i;

	printf("check0\n");
	start(a);
	finished = 0;
	while (!a->died && !finished)
	{
		finished = 1;
		i = -1;
		while (++i < a->n_ph)
			if (died(a, &a->phs[i], &finished))
				break ;
	}
	printf("check1\n");
}
