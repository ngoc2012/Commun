/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/20 23:08:23 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <signal.h>

void	end_process(t_academy *a, int erro)
{
	int	i;

	sem_destroy(&a->sem_last_eat);
	sem_destroy(&a->sem_die);
	sem_close(a->sem_forks);
	sem_close(a->sem_write);
	sem_close(a->sem_start);
	i = -1;
	while (++i < a->n_ph)
	{
		free(a->sem_died_str[i]);
		free(a->sem_started_str[i]);
		sem_close(a->sem_died[i]);
		sem_close(a->sem_started[i]);
	}
	free(a->sem_died);
	free(a->sem_died_str);
	free(a->sem_started);
	free(a->sem_started_str);
	free(a->sem_write_str);
	free(a->sem_forks_str);
	free(a->sem_start_str);
	free(a->phs);
	exit(erro);
}
