/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/28 14:44:49 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating2(t_philo *ph)
{
	int	d;

	d = get_time_interval(&ph->fork2, &ph->a->t0);
	printf("%d %d has taken a fork\n", d, ph->id);
	printf("%d %d is eating\n", d, ph->id);
	pthread_mutex_unlock(&ph->a->m_write);
	m_set(&ph->eated, 1, &ph->m_e);
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
	pthread_mutex_unlock(&ph->a->forks[ph->if2]);
	pthread_mutex_unlock(&ph->a->forks[ph->if1]);
	return (1);
}

void	eating3(t_philo *ph)
{
	m_set(&ph->eated, 1, &ph->m_p);
	while (now_time_interval(&ph->a->tv, &ph->a->t0) < ph->a->t_d + 10)
		usleep(1);
	pthread_mutex_unlock(&ph->a->forks[ph->if1]);
	pthread_mutex_lock(&ph->a->m_write);
}

void	eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->a->forks[ph->if1]);
	gettimeofday(&ph->fork1, NULL);
	if (!m_get(&ph->a->died, &ph->a->m_a))
	{
		pthread_mutex_lock(&ph->a->m_write);
		printf("%d %d has taken a fork\n", get_time_interval(&ph->fork1, &ph->a->t0), ph->id);
		pthread_mutex_unlock(&ph->a->m_write);
	}
	if (ph->if1 == ph->if2)
	{
		eating3(ph);
		return ;
	}
	pthread_mutex_lock(&ph->a->forks[ph->if2]);
	gettimeofday(&ph->fork2, NULL);
	pthread_mutex_lock(&ph->a->m_write);
	m_set_time(&ph->last_eat0, &ph->fork2, &ph->m_p);
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
	pthread_mutex_lock(&ph->a->m_write);
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
	int	n_e;

	ph = (t_philo *) ph0;
	m_set(&ph->created, 1, &ph->m_p);
	while (!m_get(&ph->a->start, &ph->a->m_a))
		usleep(1);
	if (ph->a->t_d > 2 * ph->a->t_e)
		usleep(((ph->id - 1) % 2) * ph->a->t_e + ((ph->id - 1) / 2) * (ph->a->t_d - ph->a->t_e * 2) / ph->a->n_ph);
	else
		usleep(((ph->id - 1) % 2) * ph->a->t_e + ((ph->id - 1) / 2) * ph->a->t_e / ph->a->n_ph);
	n_e = 0;
	while (!m_get(&ph->a->died, &ph->a->m_a))
	{
		eating(ph);
		if ((ph->a->n_e > 0 && n_e < ph->a->n_e) || m_get(&ph->a->died, &ph->a->m_a))
			break ;
		sleeping(ph);
		n_e++;
	}
	return ((void *) NULL);
}
