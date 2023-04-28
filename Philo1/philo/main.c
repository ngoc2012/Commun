/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/28 14:27:27 by minh-ngu         ###   ########.fr       */
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

int	free_prog(t_academy *a, int erro)
{
	if (a->phs)
		free(a->phs);
	if (a->forks)
		free(a->forks);
	return (erro);
}

int	end_prog(t_academy *a, int erro)
{
	int		i;

	i = -1;
	while (++i < a->n_ph)
	{
		pthread_mutex_destroy(&a->phs[i].m_p);
		pthread_mutex_destroy(&a->phs[i].m_f);
		pthread_mutex_destroy(&a->phs[i].m_e);
		pthread_mutex_destroy(&a->forks[i]);
	}
	pthread_mutex_destroy(&a->m_write);
	pthread_mutex_destroy(&a->m_a);
	free_prog(a, -1);
	return (erro);
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
	{
		a->n_e = ft_atoi(argv[5]);
		if (a->n_e <= 0)
			return (0);
	}
	if (a->n_ph <= 0 || a->n_ph > 200 || a->t_d <= 0
		|| a->t_e <= 0 || a->t_s <= 0)
		return (0);
	if (a->t_t < 1)
		a->t_t = 1;
	a->phs = malloc(sizeof(t_philo) * a->n_ph);
	a->forks = malloc(sizeof(pthread_mutex_t) * a->n_ph);
	if (!a->phs || !a->forks)
		return (free_prog(a, 0));
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
	{
		printf("check\n");
		check(&a);
	}
	else
		return (end_prog(&a, 0));
	i = -1;
	while (++i < a.n_ph)
		pthread_join(a.phs[i].th, NULL);
	return (end_prog(&a, 0));
}
