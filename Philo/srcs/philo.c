/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/22 16:20:11 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((long long) (tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	eating(t_academy *a, t_philo *ph)
{
	long long t0;

	t0 = get_time();
	ft_printf("%d %d is eating\n", get_time() - a->t0, ph->id);
	while (get_time() - t0 < a->t_e)
		usleep(1);
	ph->last_eat = get_time() - a->t0;
}

void	sleeping(t_academy *a, t_philo *ph)
{
	long long t0;

	t0 = get_time();
	ft_printf("%d %d is sleeping\n", get_time() - a->t0, ph->id);
	while (get_time() - t0 < a->t_e)
		usleep(1);
}

void	thinking(t_academy *a, t_philo *ph)
{
	ft_printf("%d %d is thinking\n", get_time() - a->t0, ph->id);
}

void	init(t_philo *ph, int id)
{
	ph->id = id;
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
		init(&a.phs[i], i + 1);
	ft_printf("Time to eat %d\n", a.t_e);
	ft_printf("Time to sleep %d\n", a.t_s);
	ft_printf("Time to die %d\n", a.t_d);
	a.t0 = get_time();
	eating(&a, &a.phs[0]);
	sleeping(&a, &a.phs[0]);
	thinking(&a, &a.phs[0]);
	ft_printf("%d last eat at %d\n", a.phs[0].id, a.phs[0].last_eat);
	free(a.phs);
	free(a.forks);
}
