/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/15 18:38:20 by ngoc             ###   ########.fr       */
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
	a->n_e = -1;
	if (argc == 6)
	{
		a->n_e = ft_atoi(argv[5]);
		if (a->n_e <= 0)
			exit(EXIT_FAILURE);
	}
	if (a->n_ph <= 0 || a->t_d <= 0 || a->t_e <= 0
		|| a->t_s <= 0 || a->t_t <= 0)
		exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	int			i;
	int			j;
	t_academy	a;

	get_args(argc, argv, &a);
	a.sem_write = sem_open(SEM_WRITE, O_CREAT | O_EXCL, SEM_PERMS, 1);
	a.sem_forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, SEM_PERMS, a.n_ph);
	if (a.sem_write == SEM_FAILED || a.sem_forks == SEM_FAILED)
	{
		printf("sem_open failed 1\n");
		return (1);
	}
	if (sem_close(a.sem_write) < 0 || sem_close(a.sem_forks) < 0) {
		printf("sem_close(3) failed\n");
		sem_unlink(SEM_FORKS);
		exit(EXIT_FAILURE);
	}
	a.phs = malloc(sizeof(pid_t) * a.n_ph);
	if (!a.phs)
	{
		printf("Malloc error\n");
		return (1);
	}
	gettimeofday(&a.t0, NULL);
	a.last_eat = a.t0;
	i = -1;
	while (++i < a.n_ph)
	{
		if ((a.phs[i] = fork()) < 0) {
			printf("fork(2) failed\n");
			exit(EXIT_FAILURE);
		}
		a.id = i + 1;
		if (a.phs[i] == 0) {
			philo(&a, i);
		}
	}

	int	status;
	i = -1;
	while (++i < a.n_ph)
	{
		if (waitpid(a.phs[i], &status, 0) != -1)
		{
			if ( WIFEXITED(status) ) {
				if (WEXITSTATUS(status) == 4)
				{
					printf("%d %d died\n", now_time_interval(&a.tv, &a.t0), a.id);
					j = -1;
					while (++j < a.n_ph)
						if (j != i)
							kill(a.phs[j], SIGINT);
					break ;
				}
			}
		}
	}
	if (sem_unlink(SEM_FORKS) < 0 || sem_unlink(SEM_WRITE) < 0)
		printf("sem_unlink(3) failed\n");
	free(a.phs);
}
