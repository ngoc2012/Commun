/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/11 16:00:29 by ngoc             ###   ########.fr       */
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

void	free_prog(t_academy *a, int erro)
{
	if (a->phs)
		free(a->phs);
	if (a->forks)
		free(a->forks);
	if (erro != -1)
		exit(erro);
}

void	end_prog(t_academy *a, int erro)
{
	int	i;

	i = -1;
	while (++i < a->n_ph)
	{
		if (&a->phs[i].m_p)
			pthread_mutex_destroy(&a->phs[i].m_p);
		if (&a->forks[i])
			pthread_mutex_destroy(&a->forks[i]);
	}
	if (&a->m_write)
		pthread_mutex_destroy(&a->m_write);
	if (&a->m_a)
		pthread_mutex_destroy(&a->m_a);
	if (a->n_ph == 1)
		pthread_mutex_destroy(&a->forks[1]);
	free_prog(a, -1);
	exit(erro);
}
