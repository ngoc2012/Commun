/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/29 15:20:43 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating1(t_philo *ph)
{
	int	d;

	pthread_mutex_lock(&ph->a->forks[ph->if2]);
	pthread_mutex_lock(&ph->a->m_write);
	gettimeofday(&ph->fork2, NULL);
	m_set_time(&ph->last_eat0, &ph->fork2, &ph->m_p);
	if (m_get(&ph->a->died, &ph->a->m_a))
	{
		pthread_mutex_unlock(&ph->a->m_write);
		pthread_mutex_unlock(&ph->a->forks[ph->if2]);
		pthread_mutex_unlock(&ph->a->forks[ph->if1]);
		return (0);
	}
	d = get_time_interval(&ph->fork2, &ph->a->t0);
	ph->n_e++;
	printf("%d %d has taken a fork\n", d, ph->id);
	printf("%d %d is eating\n", d, ph->id);
	pthread_mutex_unlock(&ph->a->m_write);
	return (1);
}

int	eating2(t_philo *ph)
{
	m_set(&ph->eated, 1, &ph->m_e);
	while (now_time_interval(&ph->last_eat, &ph->fork2) <= ph->a->t_e)
		usleep(1);
	if (ph->a->n_e != -1 && ph->n_e == ph->a->n_e)
	{
		m_set(&ph->finished, 1, &ph->m_f);
		pthread_mutex_unlock(&ph->a->forks[ph->if2]);
		pthread_mutex_unlock(&ph->a->forks[ph->if1]);
		return (0);
	}
	if (m_get(&ph->a->died, &ph->a->m_a))
	{
		pthread_mutex_unlock(&ph->a->forks[ph->if2]);
		pthread_mutex_unlock(&ph->a->forks[ph->if1]);
		return (0);
	}
	pthread_mutex_lock(&ph->a->m_write);
	pthread_mutex_unlock(&ph->a->forks[ph->if2]);
	pthread_mutex_unlock(&ph->a->forks[ph->if1]);
	return (1);
}

int	eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->a->forks[ph->if1]);
	pthread_mutex_lock(&ph->a->m_write);
	gettimeofday(&ph->fork1, NULL);
	if (m_get(&ph->a->died, &ph->a->m_a))
	{
		pthread_mutex_unlock(&ph->a->m_write);
		pthread_mutex_unlock(&ph->a->forks[ph->if1]);
		return (0);
	}
	printf("%d %d has taken a fork\n",
		get_time_interval(&ph->fork1, &ph->a->t0), ph->id);
	pthread_mutex_unlock(&ph->a->m_write);
	if (ph->if1 == ph->if2)
	{
		m_set_time(&ph->last_eat0, &ph->fork1, &ph->m_p);
		m_set(&ph->eated, 1, &ph->m_e);
		while (now_time_interval(&ph->a->tv, &ph->last_eat0) < ph->a->t_d + 100)
			usleep(1);
		pthread_mutex_unlock(&ph->a->forks[ph->if1]);
		return (0);
	}
	if (!eating1(ph))
		return (0);
	return (eating2(ph));
}

void	sleeping(t_philo *ph)
{
	printf("%d %d is sleeping\n",
		get_time_interval(&ph->last_eat, &ph->a->t0), ph->id);
	pthread_mutex_unlock(&ph->a->m_write);
	while (now_time_interval(&ph->last_sleep, &ph->last_eat) < ph->a->t_s)
		usleep(1);
	if (m_get(&ph->a->died, &ph->a->m_a))
		return ;
	pthread_mutex_lock(&ph->a->m_write);
	printf("%d %d is thinking\n",
		get_time_interval(&ph->last_sleep, &ph->a->t0), ph->id);
	pthread_mutex_unlock(&ph->a->m_write);
	while (now_time_interval(&ph->last_think, &ph->last_sleep) < ph->a->t_t)
		usleep(1);
}

void	*life(void *ph0)
{
	t_philo	*ph;

	ph = (t_philo *) ph0;
	m_set(&ph->created, 1, &ph->m_p);
	while (!m_get(&ph->started, &ph->m_s))
		usleep(1);
	if (ph->a->n_ph % 2)
		usleep((ph->id % 2 * 5));
	else
		usleep((ph->id % 2 * ph->a->t_e / 2));
	while (!m_get(&ph->a->died, &ph->a->m_a))
	{
		if (!eating(ph))
			break ;
		if (m_get(&ph->a->died, &ph->a->m_a))
		{
			pthread_mutex_unlock(&ph->a->m_write);
			break ;
		}
		sleeping(ph);
	}
	m_set(&ph->finished, 1, &ph->m_f);
	return ((void *) NULL);
}
