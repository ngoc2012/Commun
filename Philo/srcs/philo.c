/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/02 22:35:01 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_prog(t_academy *a, int erro)
{
	if (a->phs)
		free(a->phs);
	if (a->forks)
		free(a->forks);
	if (erro != -1)
		exit(erro);
}

void	end_prog(t_academy *a, int erro)
{
	int	i;

	i = -1;
	while (++i < a->n_ph)
	{
		if (&a->forks[i])
			pthread_mutex_destroy(&a->forks[i]);
		if (&a->writing)
			pthread_mutex_destroy(&a->writing);
	}
	free_prog(a, -1);
	exit(erro);
}

// Time in milliseconds
int	get_time_interval(struct timeval *tv1, struct timeval *tv2)
{
	return ((int) ((tv1->tv_sec - tv2->tv_sec) * 1000000 + tv1->tv_usec - tv2->tv_usec) / 1000);
}

int	get_time_interval_micro(struct timeval *tv1, struct timeval *tv2)
{
	return ((int) ((tv1->tv_sec - tv2->tv_sec) * 1000000 + (tv1->tv_usec - tv2->tv_usec)));
}

int	now_time_interval(struct timeval *tv1, struct timeval *tv2)
{
	gettimeofday(tv1, NULL);
	return (get_time_interval_micro(tv1, tv2));
}

long long	get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((long long) (tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	print_int(long long n)
{
	char	base[10] = "0123456789";
	if (n > 9)
		print_int(n / 10);
	write(1, &base[n % 10], 1);
}

void	print_int0(long long n)
{
	int	len;
	char	base[10] = "0123456789";
	char	s[100];

	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	len = 0;
	while (n > 0)
	{
		s[len] = base[n % 10];
		n /= 10;
		len++;
	}
	while (--len)
		write(1, &s[len], 1);
}

void	print(t_philo *ph, struct timeval *tv, const char *s)
{
	pthread_mutex_lock(&ph->a->writing);
	//print_int(get_time_interval(tv, &ph->a->t0));
	print_int((tv->tv_sec - ph->a->t0.tv_sec) * 1000000 + (tv->tv_usec - ph->a->t0.tv_usec));
	write(1, " ", 1);
	print_int(ph->id);
	while (*s)
		write(1, s++, 1);
	pthread_mutex_unlock(&ph->a->writing);
}

void	eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->a->forks[ph->if1]);
	gettimeofday(&ph->fork1, NULL);
	pthread_mutex_lock(&ph->a->forks[ph->if2]);
	gettimeofday(&ph->fork2, NULL);
	print(ph, &ph->fork2, " has taken a fork\n");
	print(ph, &ph->fork2, " has taken a fork\n");
	print(ph, &ph->fork2, " is eating\n");
	ph->n_e++;
	while (now_time_interval(&ph->last_eat, &ph->fork2) <= ph->a->t_e
			&& !ph->a->died)
		;
	pthread_mutex_unlock(&ph->a->forks[ph->if1]);
	pthread_mutex_unlock(&ph->a->forks[ph->if2]);
}

void	sleeping(t_philo *ph)
{
	gettimeofday(&ph->last_sleep, NULL);
	if (ph->n_e > 0)
	{
		print(ph, &ph->last_eat, " is sleeping\n");
		while (now_time_interval(&ph->last_sleep, &ph->last_eat) < ph->a->t_s
				&& !ph->a->died)
			;
		print(ph, &ph->last_sleep, " is thinking\n");
	}
}

void	*life(void *ph0)
{
	t_philo *ph;

	ph = (t_philo*) ph0;
	while (now_time_interval(&ph->last_eat, &ph->a->t0) < (ph->id - 1))
		;
	while ((ph->a->n_e == -1 || ph->n_e <= ph->a->n_e) && !ph->a->died)
	{
		eating(ph);
		sleeping(ph);
	}
	return (void*) NULL;
}

void	check(t_academy *a)
{
	int	i;
	int	dead;
	//t_academy	*a;
	struct timeval	tv;

	//a = (t_academy*) a0;
	dead = 0;
	while (!dead)
	{
		i = -1;
		while (++i < a->n_ph)
			if (now_time_interval(&tv, &a->phs[i].last_eat) > a->t_d)
			{
				//print(&a->phs[i], &a->phs[i].last_eat, " last eated\n");
				print(&a->phs[i], &tv, " died\n");
				a->died = 1;
				return ;
			}
	}
	//return (void*) NULL;
}

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

int	main(int argc, char **argv)
{
	int		i;
	int		t;
	t_academy	a;

	if (argc < 5 || argc > 6)
		return (1);
	a.n_ph = ft_atoi(argv[1]);
	a.t_d = ft_atoi(argv[2]) * 1000;
	a.t_e = ft_atoi(argv[3]) * 1000;
	a.t_s = ft_atoi(argv[4]) * 1000;
	a.n_e = -1;
	if (argc == 6)
		a.n_e = ft_atoi(argv[5]);
	a.died = 0;
	a.phs = malloc(sizeof(t_philo) * a.n_ph);
	if (!a.phs)
		return (1);
	a.forks = malloc(sizeof(pthread_mutex_t) * a.n_ph);
	if (!a.forks)
	{
		free(a.forks);
		return (1);
	}
	if (pthread_mutex_init(&a.writing, NULL) != 0)
		return (1);
	gettimeofday(&a.t0, NULL);
	t = 1000 * a.n_ph;
	a.t0.tv_sec += t / 1000000;
	a.t0.tv_usec += t % 1000000;
	i = -1;
	while (++i < a.n_ph)
	{
		a.phs[i].id = i + 1;
		a.phs[i].n_e = 0;
		a.phs[i].a = &a;
		a.phs[i].last_eat = a.t0;
		a.phs[i].if1 = i;
		a.phs[i].if2 = (i + 1) % a.n_ph;
		if (pthread_mutex_init(&a.forks[i], NULL) != 0)
			free_prog(&a, EXIT_FAILURE);
	}
	//if (pthread_create(&a.survey, NULL, &check, &a))
	//	end_prog(&a, EXIT_FAILURE);
	i = -1;
	while (++i < a.n_ph)
		if (pthread_create(&a.phs[i].th, NULL, &life, &a.phs[i]))
			end_prog(&a, EXIT_FAILURE);
	check(&a);
	i = -1;
	while (++i < a.n_ph)
		pthread_join(a.phs[i].th, NULL);
	//pthread_join(a.survey, NULL);
	printf("End\n");
	end_prog(&a, EXIT_SUCCESS);
}
