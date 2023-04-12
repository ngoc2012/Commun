/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/11 17:59:00 by ngoc             ###   ########.fr       */
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

void	init(t_academy *a)
{
	int		i;

	if (pthread_mutex_init(&a->m_a, NULL) != 0)
		exit(EXIT_FAILURE);
	if (pthread_mutex_init(&a->m_write, NULL) != 0)
		exit(EXIT_FAILURE);
	a->died = 0;
	a->start = 0;
	i = -1;
	while (++i < a->n_ph)
	{
		gettimeofday(&a->phs[i].last_eat, NULL);
		a->phs[i].id = i + 1;
		a->phs[i].n_e = 0;
		a->phs[i].created = 0;
		a->phs[i].eated = 0;
		a->phs[i].finished = 0;
		a->phs[i].a = a;
		a->phs[i].if1 = i;
		a->phs[i].if2 = i + 1;
		if (pthread_mutex_init(&a->phs[i].m_p, NULL) != 0)
			free_prog(a, EXIT_FAILURE);
		if (pthread_mutex_init(&a->forks[i], NULL) != 0)
			free_prog(a, EXIT_FAILURE);
	}
}

void	get_args(int argc, char **argv, t_academy *a)
{
	if (argc < 5 || argc > 6)
		exit(EXIT_FAILURE);
	a->n_ph = ft_atoi(argv[1]);
	a->t_d = ft_atoi(argv[2]) * 1000;
	a->t_e = ft_atoi(argv[3]) * 1000;
	a->t_s = ft_atoi(argv[4]) * 1000;
	a->t_t = (a->t_d - a->t_e - a->t_s) / 10;
	a->n_e = -1;
	if (argc == 6)
		a->n_e = ft_atoi(argv[5]);
	if (a->n_ph <= 0 || a->t_d <= 0 || a->t_e <= 0
		|| a->t_s <= 0 || a->t_t <= 0 || a->n_e <= 0)
		exit(EXIT_FAILURE);
	a->phs = malloc(sizeof(t_philo) * a->n_ph);
	if (!a->phs)
		exit(EXIT_FAILURE);
	if (a->n_ph == 1)
		a->forks = malloc(sizeof(pthread_mutex_t) * 2);
	else
		a->forks = malloc(sizeof(pthread_mutex_t) * a->n_ph);
	if (!a->forks)
	{
		free(a->phs);
		exit(EXIT_FAILURE);
	}
}

void	create(t_academy *a)
{
	int		i;

	if (a->n_ph == 1)
	{
		a->phs[0].if2 = 1;
		if (pthread_mutex_init(&a->forks[1], NULL) != 0)
			free_prog(a, EXIT_FAILURE);
	}
	else
	{
		a->phs[a->n_ph - 1].if1 = 0;
		a->phs[a->n_ph - 1].if2 = a->n_ph - 1;
	}
	gettimeofday(&a->t0, NULL);
	i = -1;
	while (++i < a->n_ph)
	{
		if (pthread_create(&a->phs[i].th, NULL, &life, &a->phs[i]))
			end_prog(a, EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	int			i;
	t_academy	a;

	get_args(argc, argv, &a);
	init(&a);
	create(&a);
	check(&a);
	i = -1;
	while (++i < a.n_ph)
		pthread_join(a.phs[i].th, NULL);
	end_prog(&a, EXIT_SUCCESS);
}
