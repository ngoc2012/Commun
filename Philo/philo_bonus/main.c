/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/21 12:31:43 by ngoc             ###   ########.fr       */
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

void	get_args(int argc, char **argv, t_academy *a)
{
	if (argc < 5 || argc > 6)
		exit(EXIT_FAILURE);
	a->n_ph = ft_atoi(argv[1]);
	a->t_d = ft_atoi(argv[2]) * 1000;
	a->t_e = ft_atoi(argv[3]) * 1000;
	a->t_s = ft_atoi(argv[4]) * 1000;
	a->t_t = (a->t_d - a->t_e - a->t_s) / 10;
	a->eated = 0;
	a->died = 0;
	a->n_e = -1;
	if (argc == 6)
	{
		a->n_e = ft_atoi(argv[5]);
		if (a->n_e <= 0)
			exit(EXIT_FAILURE);
	}
	if (a->n_ph <= 0 || a->n_ph > 200 || a->t_d <= 0 || a->t_e <= 0
		|| a->t_s <= 0 || a->t_t <= 0)
		exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	int			i;
	t_academy	a;

	get_args(argc, argv, &a);
	init(&a);
	i = -1;
	while (++i < a.n_ph)
		if (sem_wait(a.sem_started[i]) < 0)
			end_prog(&a, 1);
	i = -1;
	while (++i < a.n_ph)
		if (sem_post(a.sem_start) < 0)
			end_prog(&a, 1);
	i = -1;
	while (++i < a.n_ph)
		waitpid(a.phs[i], NULL, 0);
	end_prog(&a, 0);
}
