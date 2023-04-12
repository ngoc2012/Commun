/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/11 16:22:56 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start(t_academy *a)
{
	int		i;
	char	start;

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
	m_set(&a->start, 1, &a->m_a);
	gettimeofday(&a->t0, NULL);
	i = -1;
	while (++i < a->n_ph)
		a->phs[i].last_eat = a->t0;
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

	pthread_mutex_lock(&ph->m_p);
	finished0 = ph->finished;
	pthread_mutex_unlock(&ph->m_p);
	if (!finished0)
	{
		pthread_mutex_lock(&ph->m_p);
		last_eat = ph->last_eat0;
		pthread_mutex_unlock(&ph->m_p);
		if (now_time_interval(&tv, &last_eat) > a->t_d)
		{
			m_set(&a->died, 1, &a->m_a);
			pthread_mutex_lock(&a->m_write);
			printf("%d %d died\n", get_time_interval(&tv, &a->t0), ph->id);
			pthread_mutex_unlock(&a->m_write);
			return (0);
		}
		*finished = 0;
	}
	return (1);
}

void	check(t_academy *a)
{
	char	finished;
	int		i;

	start(a);
	eated(a);
	finished = 0;
	while (!a->died && !finished)
	{
		finished = 1;
		i = -1;
		while (++i < a->n_ph)
			if (!died(a, &a->phs[i], &finished))
				break ;
	}
}
