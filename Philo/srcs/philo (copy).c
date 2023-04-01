/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/01 05:25:55 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Time in milliseconds
unsigned int	get_time_interval(struct timeval *tv1, struct timeval *tv2)
{
	return ((unsigned int) ((tv1->tv_sec - tv2->tv_sec) * 1000 + (tv1->tv_usec - tv2->tv_usec) / 1000));
}

unsigned int	get_time_interval_micro(struct timeval *tv1, struct timeval *tv2)
{
	return ((int) ((tv1->tv_sec - tv2->tv_sec) * 1000000 + (tv1->tv_usec - tv2->tv_usec)));
}

unsigned int	now_time_interval(struct timeval *tv, struct timeval *tv2)
{
	gettimeofday(tv, NULL);
	return (get_time_interval_micro(tv, tv2));
}

void	correct_time(struct timeval *tv, struct timeval *tv0)
{
	unsigned int	n;

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

void	print(t_philo *ph, struct timeval *tv, const char *s0)
{
	char	*s;
	char	*s1;
	char	*s2;

	s = ft_calloc(1000, 1);
	s1 = ft_itoa(get_time_interval(tv, &ph->a->t0));
	s2 = ft_itoa(ph->id);
	ft_strlcat(s, s1, ft_strlen(s1) + 1);
	ft_strlcat(s, " ", ft_strlen(s) + 2);
	ft_strlcat(s, s2, ft_strlen(s) + ft_strlen(s2) + 1);
	ft_strlcat(s, s0, ft_strlen(s) + ft_strlen(s0) + 1);
	write(1, s, ft_strlen(s));
	free(s);
	free(s1);
	free(s2);
}

void	eating(t_philo *ph)
{
	struct timeval	tv;
	struct timeval	tv1;
	struct timeval	tv2;

	pthread_mutex_lock(&ph->a->forks[ph->fork1]);
	gettimeofday(&tv1, NULL);
	print(ph, &tv1, " has taken a fork\n");
	pthread_mutex_lock(&ph->a->forks[ph->fork2]);
	gettimeofday(&tv2, NULL);
	print(ph, &tv2, " has taken a fork\n");
	gettimeofday(&tv, NULL);
	print(ph, &tv, " is eating\n");
	//correct_time(&tv, &ph->a->t0);
	while (now_time_interval(&ph->last_eat, &tv) < ph->a->t_e)
		usleep(1);
	pthread_mutex_unlock(&ph->a->forks[ph->id - 1]);
	pthread_mutex_unlock(&ph->a->forks[ph->id % ph->a->n_ph]);
	ph->n_e++;
}

void	sleeping(t_philo *ph)
{
	struct timeval	tv;

	if (ph->n_e > 0)
	{
		gettimeofday(&tv, NULL);
		print(ph, &tv, " is sleeping\n");
		//correct_time(&tv, &ph->a->t0);
		while (now_time_interval(&ph->last_sleep, &tv) < ph->a->t_s)
			usleep(1);
	}
}

void	*life(void *ph0)
{
	t_philo *ph;

	ph = (t_philo*) ph0;
	while (ph->n_e <= ph->a->n_e)
	{
		eating(ph);
		sleeping(ph);
	}
	return (void*) NULL;
}

int	main(int argc, char **argv)
{
	int		i;
	t_academy	a;

	if (argc < 5 || argc > 6)
		return (1);
	a.n_ph = ft_atoi(argv[1]);
	a.t_d = ft_atoi(argv[2]) * 1000;
	a.t_e = ft_atoi(argv[3]) * 1000;
	a.t_s = ft_atoi(argv[4]) * 1000;
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
	{
		a.phs[i].id = i + 1;
		a.phs[i].n_e = 0;
		a.phs[i].a = &a;
		a.phs[i].fork1 = i;
		a.phs[i].fork2 = (i + 1) % a.n_ph;
		if (pthread_mutex_init(&a.forks[i], NULL) != 0)
		{
			free(a.phs);
			free(a.forks);
		}
	}
	ft_printf("Time to eat %d\n", a.t_e);
	ft_printf("Time to sleep %d\n", a.t_s);
	ft_printf("Time to die %d\n", a.t_d);
	ft_printf("Eat times %d\n", a.n_e);
	ft_printf("\n");
	gettimeofday(&a.t0, NULL);
	i = -1;
	while (++i < a.n_ph)
		pthread_create(&a.phs[i].th, NULL, &life, &a.phs[i]);
	i = -1;
	while (++i < a.n_ph)
	{
		pthread_join(a.phs[i].th, NULL);
		pthread_mutex_destroy(&a.forks[i]);
	}
	free(a.phs);
	free(a.forks);
}
