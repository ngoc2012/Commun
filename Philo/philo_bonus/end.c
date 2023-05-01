/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/29 16:17:32 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_prog(t_academy *a, int erro)
{
	int	i;

	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_START);
	sem_unlink(SEM_LAST_EAT);
	sem_unlink(SEM_DIE);
	i = -1;
	while (++i < a->n_ph)
	{
		sem_unlink(a->sem_died_str[i]);
		sem_unlink(a->sem_started_str[i]);
	}
	end_process(a, erro);
}

void	free1(t_academy *a, int erro)
{
	int	i;

	if (a->sem_died)
		free(a->sem_died);
	if (a->sem_started)
		free(a->sem_started);
	if (a->phs)
		free(a->phs);
	i = -1;
	while (++i < a->n_ph)
	{
		if (a->sem_died_str && a->sem_died_str[i])
			free(a->sem_died_str[i]);
		if (a->sem_started_str && a->sem_started_str[i])
			free(a->sem_started_str[i]);
	}
	if (a->sem_died_str)
		free(a->sem_died_str);
	if (a->sem_started_str)
		free(a->sem_started_str);
	exit(erro);
}

void	end_process(t_academy *a, int erro)
{
	int	i;

	sem_close(a->sem_forks);
	sem_close(a->sem_write);
	sem_close(a->sem_start);
	sem_close(a->sem_last_eat);
	sem_close(a->sem_die);
	i = -1;
	while (++i < a->n_ph)
	{
		sem_close(a->sem_died[i]);
		sem_close(a->sem_started[i]);
	}
	free1(a, erro);
}
