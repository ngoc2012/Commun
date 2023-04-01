/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/01 12:17:40 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	correct_time(struct timeval *tv, struct timeval *tv0)
{
	int	n;

	n = get_time_interval(tv, tv0);
	tv->tv_sec = tv0->tv_sec + n / 1000;
	tv->tv_usec = tv0->tv_usec + ((n % 1000) * 1000);
}

long long	get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((long long) (tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	print_int0(long long n)
{
	char	base[10] = "0123456789";
	if (n > 9)
		print_int0(n / 10);
	write(1, &base[n % 10], 1);
}

void	print_int(long long n)
{
	int	i;
	char	base[10] = "0123456789";
	char	s[100];
	long long	n0;

	n0 = n;
	i = 0;
	while (n > 0)
	{
		print_int(n / 10);
	}
	write(1, &base[n % 10], 1);
}

void	print(t_philo *ph, struct timeval *tv, const char *s)
{
	pthread_mutex_lock(&ph->a->writing);
	//print_int(get_time_interval(tv, &ph->a->t0));

	//write(1, " | ", 3);
	print_int0((tv->tv_sec - ph->a->t0.tv_sec) * 1000000 + (tv->tv_usec - ph->a->t0.tv_usec));
	print_int((tv->tv_sec - ph->a->t0.tv_sec) * 1000000 + (tv->tv_usec - ph->a->t0.tv_usec));
	//write(1, " | ", 3);

	write(1, " ", 1);
	print_int(ph->id);
	while (*s)
		write(1, s++, 1);
	pthread_mutex_unlock(&ph->a->writing);
}

void	eating(t_philo *ph)
{
	//int	f1;
	//int	f2;
	struct timeval	tv1;
	struct timeval	tv2;

	//f1 = -1;
	//f2 = -1;
	//while (f1 == -1 || f2 == -1)	
	//{
		pthread_mutex_lock(&ph->a->forks[ph->fork1]);
		gettimeofday(&tv1, NULL);
		print(ph, &tv1, " has taken a fork\n");
		pthread_mutex_lock(&ph->a->forks[ph->fork2]);
		gettimeofday(&tv2, NULL);
		print(ph, &tv2, " has taken a fork 2\n");
	//}
	print(ph, &tv2, " is eating\n");
	ph->n_e++;
	while (now_time_interval(&ph->last_eat, &tv2) <= ph->a->t_e)
		;
	pthread_mutex_unlock(&ph->a->forks[ph->fork1]);
	pthread_mutex_unlock(&ph->a->forks[ph->fork2]);
}

void	sleeping(t_philo *ph)
{
	if (ph->n_e > 0)
	{
		gettimeofday(&ph->a->tv, NULL);
		print(ph, &ph->a->tv, " is sleeping\n");
		//correct_time(&tv, &ph->a->t0);
		while (now_time_interval(&ph->last_sleep, &ph->a->tv) < ph->a->t_s)
			;
		print(ph, &ph->last_sleep, " is thinking\n");
	}
}

void	*life(void *ph0)
{
	t_philo *ph;
	struct timeval t0;

	ph = (t_philo*) ph0;
	t0 = ph->a->t0;
	t0.tv_usec += ph->id * 50;
	while (now_time_interval(&ph->a->tv, &t0) < 0)
		usleep(1);
	while (ph->n_e != -1 && ph->n_e <= ph->a->n_e)
	{
		eating(ph);
		sleeping(ph);
	}
	return (void*) NULL;
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
	//a.t_d = ft_atoi(argv[2]);
	//a.t_e = ft_atoi(argv[3]);
	//a.t_s = ft_atoi(argv[4]);
	a.n_e = -1;
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
	if (pthread_mutex_init(&a.writing, NULL) != 0)
		return (1);
	gettimeofday(&a.t0, NULL);
	t = 1000 * a.n_ph;
	//printf("1 - %ld %ld\n", a.t0.tv_sec, a.t0.tv_usec);
	a.t0.tv_sec += t / 1000000;
	a.t0.tv_usec += t % 1000000;
	//printf("2 - %ld %ld\n", a.t0.tv_sec, a.t0.tv_usec);
	i = -1;
	while (++i < a.n_ph)
	{
		a.phs[i].id = i + 1;
		a.phs[i].n_e = 0;
		a.phs[i].a = &a;
		a.phs[i].last_sleep = a.t0;
		a.phs[i].fork1 = i;
		a.phs[i].fork2 = (i + 1) % a.n_ph;
		if (pthread_mutex_init(&a.forks[i], NULL) != 0)
		{
			free(a.phs);
			free(a.forks);
		}
	}
	//ft_printf("Time to eat %d\n", a.t_e);
	//ft_printf("Time to sleep %d\n", a.t_s);
	//ft_printf("Time to die %d\n", a.t_d);
	//ft_printf("Eat times %d\n", a.n_e);
	//ft_printf("\n");
	i = -1;
	while (++i < a.n_ph)
		pthread_create(&a.phs[i].th, NULL, &life, &a.phs[i]);
	i = -1;
	while (++i < a.n_ph)
	{
		pthread_join(a.phs[i].th, NULL);
		pthread_mutex_destroy(&a.forks[i]);
		pthread_mutex_destroy(&a.writing);
	}
	free(a.phs);
	free(a.forks);
}
