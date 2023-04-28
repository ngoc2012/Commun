/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/28 16:46:39 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->a->forks[ph->if1]);
	pthread_mutex_lock(&ph->a->m_write);
	gettimeofday(&ph->fork1, NULL);
	if (!m_get(&ph->a->died, &ph->a->m_a))
	{
		printf("%d %d has taken a fork %d\n", get_time_interval(&ph->fork1, &ph->a->t0), ph->id, ph->if1);
		pthread_mutex_unlock(&ph->a->m_write);
	}
	if (ph->if1 == ph->if2)
	{
		m_set(&ph->eated, 1, &ph->m_p);
		while (now_time_interval(&ph->a->tv, &ph->a->t0) < ph->a->t_d + 10)
			usleep(1);
		pthread_mutex_unlock(&ph->a->forks[ph->if1]);
		pthread_mutex_lock(&ph->a->m_write);
		return (0);
	}
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
	int	d = get_time_interval(&ph->fork2, &ph->a->t0);
	ph->n_e++;
	printf("%d %d has taken a fork %d\n", d, ph->id, ph->if2);
	printf("%d %d is eating %d\n", d, ph->id, ph->n_e);
	pthread_mutex_unlock(&ph->a->m_write);
	m_set(&ph->eated, 1, &ph->m_e);
	while (now_time_interval(&ph->last_eat, &ph->fork2) <= ph->a->t_e)
		usleep(1);
	if (ph->a->n_e != -1 && ph->n_e == ph->a->n_e)
	{
		m_set(&ph->finished, 1, &ph->m_p);
		pthread_mutex_unlock(&ph->a->forks[ph->if2]);
		pthread_mutex_unlock(&ph->a->forks[ph->if1]);
		return (0);
	}
	pthread_mutex_lock(&ph->a->m_write);
	pthread_mutex_unlock(&ph->a->forks[ph->if2]);
	pthread_mutex_unlock(&ph->a->forks[ph->if1]);
	return (1);
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
	usleep(((ph->id - 1) % 2));
	while (!m_get(&ph->a->died, &ph->a->m_a))
	{
		if (!eating(ph))
			break ;
		if (m_get(&ph->a->died, &ph->a->m_a))
			break ;
		sleeping(ph);
	}
	pthread_mutex_unlock(&ph->a->m_write);
	m_set(&ph->finished, 1, &ph->m_f);
	return ((void *) NULL);
}
