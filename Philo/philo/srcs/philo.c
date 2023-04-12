/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/11 16:01:49 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating2(t_philo *ph)
{
	int	d;

	d = get_time_interval(&ph->fork2, &ph->a->t0);
	printf("%d %d has taken a fork\n", d, ph->id);
	printf("%d %d has taken a fork\n", d, ph->id);
	printf("%d %d is eating\n", d, ph->id);
	pthread_mutex_unlock(&ph->a->m_write);
	m_set(&ph->eated, 1, &ph->m_p);
	ph->n_e++;
	if (ph->a->n_e != -1 && ph->n_e == ph->a->n_e)
	{
		m_set(&ph->finished, 1, &ph->m_p);
		pthread_mutex_unlock(&ph->a->forks[ph->if2]);
		pthread_mutex_unlock(&ph->a->forks[ph->if1]);
		return (0);
	}
	while (now_time_interval(&ph->last_eat, &ph->fork2) <= ph->a->t_e)
		usleep(1);
	pthread_mutex_lock(&ph->a->m_write);
	pthread_mutex_unlock(&ph->a->forks[ph->if2]);
	pthread_mutex_unlock(&ph->a->forks[ph->if1]);
	return (1);
}

void	eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->a->forks[ph->if1]);
	gettimeofday(&ph->fork1, NULL);
	pthread_mutex_lock(&ph->a->forks[ph->if2]);
	gettimeofday(&ph->fork2, NULL);
	pthread_mutex_lock(&ph->a->m_write);
	pthread_mutex_lock(&ph->m_p);
	ph->last_eat0 = ph->fork2;
	pthread_mutex_unlock(&ph->m_p);
	if (m_get(&ph->a->died, &ph->a->m_a))
	{
		pthread_mutex_unlock(&ph->a->m_write);
		pthread_mutex_unlock(&ph->a->forks[ph->if2]);
		pthread_mutex_unlock(&ph->a->forks[ph->if1]);
		return ;
	}
	if (!eating2(ph))
		return ;
}

void	sleeping(t_philo *ph)
{
	printf("%d %d is sleeping\n",
		get_time_interval(&ph->last_eat, &ph->a->t0), ph->id);
	pthread_mutex_unlock(&ph->a->m_write);
	while (now_time_interval(&ph->last_sleep, &ph->last_eat) < ph->a->t_s)
		usleep(1);
	if (m_get(&ph->finished, &ph->m_p) || m_get(&ph->a->died, &ph->a->m_a))
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
	while (!m_get(&ph->a->start, &ph->a->m_a))
		usleep(1);
	usleep((ph->id % 2) * ph->a->t_e);
	while (!m_get(&ph->finished, &ph->m_p) && !m_get(&ph->a->died, &ph->a->m_a))
	{
		eating(ph);
		if (m_get(&ph->finished, &ph->m_p) || m_get(&ph->a->died, &ph->a->m_a))
		{
			pthread_mutex_unlock(&ph->a->m_write);
			return ((void *) NULL);
		}
		sleeping(ph);
	}
	return ((void *) NULL);
}
