/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/28 13:05:32 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	m_get(char *v, pthread_mutex_t *m)
{
	char	i;

	pthread_mutex_lock(m);
	i = *v;
	pthread_mutex_unlock(m);
	return (i);
}

void	m_set(char *v, char i, pthread_mutex_t *m)
{
	pthread_mutex_lock(m);
	*v = i;
	pthread_mutex_unlock(m);
}

struct timeval	m_get_time(struct timeval *v, pthread_mutex_t *m)
{
	struct timeval	i;

	pthread_mutex_lock(m);
	i = *v;
	pthread_mutex_unlock(m);
	return (i);
}

void	m_set_time(struct timeval *v, struct timeval *i, pthread_mutex_t *m)
{
	pthread_mutex_lock(m);
	*v = *i;
	pthread_mutex_unlock(m);
}
