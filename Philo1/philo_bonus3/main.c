/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/20 15:35:33 by ngoc             ###   ########.fr       */
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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if ((!dest) && (!src))
		return (dest);
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_itoa(char *s, int n)
{
	int	i;
	char	base[10] = "0123456789";
	
	if (n == 0)
	{
		s[0] = '0';
		s[1] = 0;
		return;
	}
	i = -1;
	while (n > 0)
	{
		s[++i] = base[n % 10];
		n = n / 10;
	}
	s[++i] = 0;
}

void	end_prog(t_academy *a, int erro)
{
	int	i;

	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_START);
	i = -1;
	while (++i < a->n_ph)
	{
		sem_unlink(a->sem_died_str[i]);
		sem_unlink(a->sem_started_str[i]);
	}
	end_process(a, erro);
}

int	main(int argc, char **argv)
{
	int			i;
	int			n;
	t_academy	a;

	get_args(argc, argv, &a);
	a.phs = malloc(sizeof(pid_t) * a.n_ph);
	if (!a.phs)
		exit(EXIT_FAILURE);
	a.sem_died = malloc(sizeof(sem_t *) * a.n_ph);
	if (!a.sem_died)
		exit(EXIT_FAILURE);
	a.sem_died_str = malloc(sizeof(char *) * a.n_ph);
	if (!a.sem_died_str)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < a.n_ph)
	{
		n = ft_strlen(SEM_DIED);
		a.sem_died_str[i] = malloc(sizeof(char) * (n + 5));
		ft_memcpy(a.sem_died_str[i], SEM_DIED, n);
		ft_itoa(&a.sem_died_str[i][n], i);
	}
	i = -1;
	while (++i < a.n_ph)
	{
		a.sem_died[i] = sem_open(a.sem_died_str[i], O_CREAT | O_EXCL, SEM_PERMS, 0);
		if (a.sem_died[i] == SEM_FAILED)
		{
			printf("sem_open failed %d\n", i);
			exit(EXIT_FAILURE);
		}
	}
	a.sem_started = malloc(sizeof(sem_t *) * a.n_ph);
	if (!a.sem_started)
		exit(EXIT_FAILURE);
	a.sem_started_str = malloc(sizeof(char *) * a.n_ph);
	if (!a.sem_started_str)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < a.n_ph)
	{
		n = ft_strlen(SEM_STARTED);
		a.sem_started_str[i] = malloc(sizeof(char) * (n + 5));
		ft_memcpy(a.sem_started_str[i], SEM_STARTED, n);
		ft_itoa(&a.sem_started_str[i][n], i);
	}
	i = -1;
	while (++i < a.n_ph)
	{
		a.sem_started[i] = sem_open(a.sem_started_str[i], O_CREAT | O_EXCL, SEM_PERMS, 0);
		if (a.sem_started[i] == SEM_FAILED)
		{
			printf("sem_open failed %d\n", i);
			exit(EXIT_FAILURE);
		}
	}
	a.sem_write = sem_open(SEM_WRITE, O_CREAT | O_EXCL, SEM_PERMS, 1);
	a.sem_forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, SEM_PERMS, a.n_ph);
	a.sem_start = sem_open(SEM_START, O_CREAT | O_EXCL, SEM_PERMS, 0);
	sem_init(&a.sem_last_eat, 0, 1);
	sem_init(&a.sem_die, 0, 1);
	if (a.sem_write == SEM_FAILED || a.sem_forks == SEM_FAILED || a.sem_start == SEM_FAILED)
	{
		printf("sem_open failed 1\n");
		exit(EXIT_FAILURE);
	}
	//if (pthread_create(&a.th_stopped, NULL, &thread_stopped, &a))
	//	end_process(&a, 1);
	//if (pthread_create(&a.th_died, NULL, &thread_died, &a))
	//	end_process(&a, 1);
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
		if (a.phs[i] == 0)
			philo(&a, i);
	}
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
	/*
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
	*/
	end_prog(&a, 0);
}
