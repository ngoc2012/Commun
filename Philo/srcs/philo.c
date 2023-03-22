/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/22 12:34:28 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((int) tv.tv_usec);
}

void	eating(t_academy *a, t_philo *ph)
{
	ft_printf("%d %d is eating\n", get_time() - a->t0, ph->id);
	//usleep(a->t_e);
}

void	sleeping(t_academy *a, t_philo *ph)
{
	ft_printf("%d %d is sleeping\n", get_time() - a->t0, ph->id);
	//usleep(a->t_s);
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
	free(a.phs);
}
