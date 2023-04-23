/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/22 19:15:57 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		nbr;
	int		sign;

	nbr = 0;
	sign = 1;
	while (*str == 9 || *str == 10 || *str == 11
		|| *str == 12 || *str == 13 || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str != '\0' && (*str >= 48 && *str <= 57))
	{
		if (*str >= 48 && *str <= 57)
		{
			nbr *= 10;
			nbr += *str - 48;
		}
		str++;
	}
	return (sign * nbr);
}

int	get_args(int argc, char **argv, t_academy *a)
{
	if (argc < 5 || argc > 6)
		return (0);
	a->n_ph = ft_atoi(argv[1]);
	a->t_d = ft_atoi(argv[2]) * 1000;
	a->t_e = ft_atoi(argv[3]) * 1000;
	a->t_s = ft_atoi(argv[4]) * 1000;
	a->t_t = (a->t_d - a->t_e - a->t_s) / 10;
	if (argc == 6)
		a->n_e = ft_atoi(argv[5]);
	if (a->n_ph <= 0 || a->n_ph > 200 || a->t_d <= 0
		|| a->t_e <= 0 || a->t_s <= 0 || a->t_t <= 0)
		return (0);
	a->phs = malloc(sizeof(t_philo) * a->n_ph);
	a->forks = malloc(sizeof(pthread_mutex_t) * a->n_ph);
	if (!a->phs || !a->forks)
		return (free_prog(a, 0));
	return (1);
}

int	create(t_academy *a)
{
	int	i;
	int	j;

	a->phs[a->n_ph - 1].if1 = 0;
	a->phs[a->n_ph - 1].if2 = a->n_ph - 1;
	gettimeofday(&a->t0, NULL);
	i = -1;
	while (++i < a->n_ph)
	{
		if (pthread_create(&a->phs[i].th, NULL, &life, &a->phs[i]))
		{
			j = -1;
			while (++j < i)
			{
				m_set(&a->phs[j].finished, 1, &a->phs[j].m_p);
				m_set(&a->start, 1, &a->m_a);
				pthread_join(a->phs[j].th, NULL);
			}
			return (0);
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int			i;
	t_academy	a;

	a.n_e = -1;
	if (!get_args(argc, argv, &a))
		return (1);
	a.died = 0;
	a.start = 0;
	if (!init(&a))
		return (free_prog(&a, 1));
	if (create(&a))
		check(&a);
	else
		return (end_prog(&a, 0));
	i = -1;
	while (++i < a.n_ph)
		pthread_join(a.phs[i].th, NULL);
	return (end_prog(&a, 0));
}
