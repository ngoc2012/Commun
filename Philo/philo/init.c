/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/28 14:56:06 by minh-ngu         ###   ########.fr       */
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
		if (pthread_mutex_init(&a->phs[i].m_p, NULL)
			|| pthread_mutex_init(&a->phs[i].m_f, NULL)
			|| pthread_mutex_init(&a->phs[i].m_e, NULL))
		{
			pthread_mutex_destroy(&a->m_a);
			pthread_mutex_destroy(&a->m_write);
			j = -1;
			while (++j < i)
			{
				pthread_mutex_destroy(&a->phs[j].m_p);
				pthread_mutex_destroy(&a->phs[j].m_f);
				pthread_mutex_destroy(&a->phs[j].m_e);
			}
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
			{
				pthread_mutex_destroy(&a->phs[j].m_p);
				pthread_mutex_destroy(&a->phs[j].m_f);
				pthread_mutex_destroy(&a->phs[j].m_e);
			}
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

	//printf("init0\n");
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
	//printf("init\n");
	return (1);
}

int	create(t_academy *a)
{
	int	i;
	int	j;

	//printf("created0\n");
	a->phs[a->n_ph - 1].if1 = 0;
	a->phs[a->n_ph - 1].if2 = a->n_ph - 1;
	gettimeofday(&a->t0, NULL);
	i = -1;
	while (++i < a->n_ph)
	{
		if (pthread_create(&a->phs[i].th, NULL, &life, &a->phs[i]))
		{
			j = -1;
			while (++j < i)
			{
				m_set(&a->died, 1, &a->m_a);
				m_set(&a->phs[j].finished, 1, &a->phs[j].m_p);
				m_set(&a->start, 1, &a->m_a);
				pthread_join(a->phs[j].th, NULL);
			}
			return (0);
		}
	}
	//printf("created11\n");
	return (1);
}
