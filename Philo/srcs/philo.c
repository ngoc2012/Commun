/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/24 16:08:05 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((long long) (tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	eating(t_philo *ph)
{
	long long t0;

	pthread_mutex_lock(&ph->a->forks[ph->id - 1]);
	pthread_mutex_lock(&ph->a->forks[ph->id % ph->a->n_ph]);
	t0 = get_time();
	ft_printf("%d %d is eating\n", get_time() - ph->a->t0, ph->id);
	while (get_time() - t0 < ph->a->t_e)
		usleep(1);
	ph->last_eat = get_time() - ph->a->t0;
	pthread_mutex_unlock(&ph->a->forks[ph->id - 1]);
	pthread_mutex_unlock(&ph->a->forks[ph->id % ph->a->n_ph]);
}

void	sleeping(t_philo *ph)
{
	long long t0;

	t0 = get_time();
	ft_printf("%d %d is sleeping\n", get_time() - ph->a->t0, ph->id);
	while (get_time() - t0 < ph->a->t_e)
		usleep(1);
}

void	thinking(t_philo *ph)
{
	ft_printf("%d %d is thinking\n", get_time() - ph->a->t0, ph->id);
}

int	main(int argc, char **argv)
{
	int		i;
	t_academy	a;

	if (argc < 5 || argc > 6)
		return (1);
	a.n_ph = ft_atoi(argv[1]);
	a.t_d = ft_atoi(argv[2]);
	a.t_e = ft_atoi(argv[3]);
	a.t_s = ft_atoi(argv[4]);
	if (argc == 6)
		a.n_e = ft_atoi(argv[5]);
	a.phs = malloc(sizeof(t_philo) * a.n_ph);
	if (!a.phs)
		return (1);
	a.forks = malloc(sizeof(pthread_mutex_t) * a.n_ph);
	if (!a.forks)
	{
		free(a.forks);
		return (1);
	}
	i = -1;
	while (++i < a.n_ph)
	{
		a.phs[i].id = i + 1;
		a.phs[i].a = &a;
		if (pthread_mutex_init(&a.forks[i], NULL) != 0)
		{
			free(a.phs);
			free(a.forks);
		}
	}
	ft_printf("Time to eat %d\n", a.t_e);
	ft_printf("Time to sleep %d\n", a.t_s);
	ft_printf("Time to die %d\n", a.t_d);
	a.t0 = get_time();
	//eating(&a, &a.phs[0]);
	//sleeping(&a, &a.phs[0]);
	//thinking(&a, &a.phs[0]);
	//ft_printf("%d last eat at %d\n", a.phs[0].id, a.phs[0].last_eat);
	i = -1;
	while (++i < a.n_ph)
	{
		pthread_join(a.phs[i].th, NULL);
		pthread_mutex_destroy(&a.forks[i]);
	}
	free(a.phs);
	free(a.forks);
}
