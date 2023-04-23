/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/22 19:25:33 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init2(t_academy *a)
{
	int	i;
	int	j;

	if (pthread_mutex_init(&a->m_a, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&a->m_write, NULL) != 0)
	{
		pthread_mutex_destroy(&a->m_a);
		return (0);
	}
	i = -1;
	while (++i < a->n_ph)
	{
		if (pthread_mutex_init(&a->phs[i].m_p, NULL) != 0)
		{
			pthread_mutex_destroy(&a->m_a);
			pthread_mutex_destroy(&a->m_write);
			j = -1;
			while (++j < i)
				pthread_mutex_destroy(&a->phs[j].m_p);
			return (0);
		}
	}
	return (1);
}

int	init3(t_academy *a)
{
	int	i;
	int	j;

	i = -1;
	while (++i < a->n_ph)
	{
		if (pthread_mutex_init(&a->forks[i], NULL) != 0)
		{
			pthread_mutex_destroy(&a->m_a);
			pthread_mutex_destroy(&a->m_write);
			j = -1;
			while (++j < a->n_ph)
				pthread_mutex_destroy(&a->phs[j].m_p);
			j = -1;
			while (++j < i)
				pthread_mutex_destroy(&a->forks[j]);
			return (0);
		}
	}
	return (1);
}

int	init(t_academy *a)
{
	int		i;

	i = -1;
	while (++i < a->n_ph)
	{
		gettimeofday(&a->phs[i].last_eat, NULL);
		a->phs[i].id = i + 1;
		a->phs[i].n_e = 0;
		a->phs[i].created = 0;
		a->phs[i].eated = 0;
		a->phs[i].finished = 0;
		a->phs[i].a = a;
		a->phs[i].if1 = i;
		a->phs[i].if2 = i + 1;
	}
	if (!init2(a))
		return (0);
	if (!init3(a))
		return (0);
	return (1);
}
