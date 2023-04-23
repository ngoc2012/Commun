/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/21 12:47:15 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_open(t_academy *a)
{
	int			i;

	i = -1;
	while (++i < a->n_ph)
	{
		a->sem_died[i] = try_open(a->sem_died_str[i], 0);
		a->sem_started[i] = try_open(a->sem_started_str[i], 0);
	}
	a->sem_write = try_open(SEM_WRITE, 1);
	a->sem_forks = try_open(SEM_FORKS, a->n_ph);
	a->sem_start = try_open(SEM_START, 0);
	sem_init(&a->sem_last_eat, 0, 1);
	sem_init(&a->sem_die, 0, 1);
}

int	init_start(t_academy *a)
{
	int	i;
	int	no_erro;

	no_erro = 1;
	i = -1;
	while (++i < a->n_ph)
	{
		a->phs[i] = fork();
		if (a->phs[i] < 0)
			no_erro = 0;
		a->id = i + 1;
		if (a->phs[i] == 0)
			philo(a, i);
	}
	return (no_erro);
}

void	init_end(t_academy *a)
{
	int	i;

	i = -1;
	while (++i < a->n_ph)
	{
		sem_post(a->sem_died[i]);
		sem_post(a->sem_start);
	}
	i = -1;
	while (++i < a->n_ph)
		waitpid(a->phs[i], NULL, 0);
	end_prog(a, EXIT_FAILURE);
}

void	init(t_academy *a)
{
	int			i;

	a->phs = malloc(sizeof(pid_t) * a->n_ph);
	a->sem_died = malloc(sizeof(sem_t *) * a->n_ph);
	a->sem_died_str = malloc(sizeof(char *) * a->n_ph);
	a->sem_started = malloc(sizeof(sem_t *) * a->n_ph);
	a->sem_started_str = malloc(sizeof(char *) * a->n_ph);
	if (!a->phs || !a->sem_died || !a->sem_died_str || !a->sem_started
		|| !a->sem_started_str)
		free1(a, EXIT_FAILURE);
	i = -1;
	while (++i < a->n_ph)
	{
		a->sem_died_str[i] = get_sem_str(SEM_DIED, i);
		a->sem_started_str[i] = get_sem_str(SEM_STARTED, i);
	}
	i = -1;
	while (++i < a->n_ph)
		if (!a->sem_died_str[i] || !a->sem_started_str[i])
			free1(a, EXIT_FAILURE);
	init_open(a);
	gettimeofday(&a->t0, NULL);
	a->last_eat = a->t0;
	if (!init_start(a))
		init_end(a);
}
