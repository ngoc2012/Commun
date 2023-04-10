/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/10 20:02:58 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	m_get(char *v, pthread_mutex_t *m)
{
	char	i;
	pthread_mutex_lock(m);
	i = *v;
	pthread_mutex_unlock(m);
	return (i);
}

void	m_set(char *v, char i, pthread_mutex_t *m)
{
	pthread_mutex_lock(m);
	*v = i;
	pthread_mutex_unlock(m);
}

int	trylock(pthread_mutex_t *m)
{
	if (pthread_mutex_lock(m) == -1)
		return (-1);
	pthread_mutex_unlock(m);
	return (0);
}

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
		if (&a->phs[i].m_p)
			pthread_mutex_destroy(&a->phs[i].m_p);
		if (&a->forks[i])
			pthread_mutex_destroy(&a->forks[i]);
	}
	if (&a->m_write)
		pthread_mutex_destroy(&a->m_write);
	if (&a->m_a)
		pthread_mutex_destroy(&a->m_a);
	if (a->n_ph == 1)
		pthread_mutex_destroy(&a->forks[1]);
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
	return ((int) ((int) (tv1->tv_sec - tv2->tv_sec) * 1000000 + (int) (tv1->tv_usec - tv2->tv_usec)));
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

void	eating(t_philo *ph)
{
	//t_timestamp	*ts;
	int	d;

	pthread_mutex_lock(&ph->a->forks[ph->if1]);
	gettimeofday(&ph->fork1, NULL);
	pthread_mutex_lock(&ph->a->forks[ph->if2]);
	gettimeofday(&ph->fork2, NULL);
	pthread_mutex_lock(&ph->a->m_write);
	pthread_mutex_lock(&ph->m_p);
	ph->last_eat = ph->fork2;
	pthread_mutex_unlock(&ph->m_p);
	if (m_get(&ph->a->died, &ph->a->m_a))
	{
		pthread_mutex_unlock(&ph->a->m_write);
		pthread_mutex_unlock(&ph->a->forks[ph->if2]);
		pthread_mutex_unlock(&ph->a->forks[ph->if1]);
		return ;
	}
	d = get_time_interval(&ph->fork2, &ph->a->t0);
	printf("%d %d has taken a fork\n", d, ph->id);
	printf("%d %d has taken a fork\n", d, ph->id);
	printf("%d %d is eating\n", d, ph->id);
	pthread_mutex_unlock(&ph->a->m_write);
	m_set(&ph->eated, 1, &ph->m_p);
	ph->n_e++;
	if (ph->a->n_e != -1 && ph->n_e == ph->a->n_e)
	{
		m_set(&ph->finished, 1, &ph->m_p);
		pthread_mutex_unlock(&ph->a->forks[ph->if2]);
		pthread_mutex_unlock(&ph->a->forks[ph->if1]);
		return ;
	}
	while (now_time_interval(&ph->last_eat0, &ph->fork2) <= ph->a->t_e)
		usleep(1);
	pthread_mutex_lock(&ph->a->m_write);
	pthread_mutex_unlock(&ph->a->forks[ph->if2]);
	pthread_mutex_unlock(&ph->a->forks[ph->if1]);
}

void	sleeping(t_philo *ph)
{
	printf("%d %d is sleeping\n", get_time_interval(&ph->last_eat0, &ph->a->t0), ph->id);
	pthread_mutex_unlock(&ph->a->m_write);
	while (now_time_interval(&ph->last_sleep, &ph->last_eat0) < ph->a->t_s)
		usleep(1);
	if (m_get(&ph->finished, &ph->m_p) || m_get(&ph->a->died, &ph->a->m_a))
		return ;
	pthread_mutex_lock(&ph->a->m_write);
	printf("%d %d is thinking\n", get_time_interval(&ph->last_sleep, &ph->a->t0), ph->id);
	pthread_mutex_unlock(&ph->a->m_write);
	while (now_time_interval(&ph->last_think, &ph->last_sleep) < ph->a->t_t)
		usleep(1);
}

void	*life(void *ph0)
{
	t_philo *ph;

	ph = (t_philo*) ph0;
	m_set(&ph->created, 1, &ph->m_p);
	while (!m_get(&ph->a->start, &ph->a->m_a))
		usleep(1);
		//usleep(ph->a->t_t);
	//usleep((ph->id % 2) * (ph->a->t_e + ph->a->t_t / 2));
	//if (ph->a->n_ph % 
	usleep((ph->id % 2) * ph->a->t_e);
	while (!m_get(&ph->finished, &ph->m_p) && !m_get(&ph->a->died, &ph->a->m_a))
	{
		eating(ph);
		if (m_get(&ph->finished, &ph->m_p) || m_get(&ph->a->died, &ph->a->m_a))
		{
			pthread_mutex_unlock(&ph->a->m_write);
			return (void*) NULL;
		}
		sleeping(ph);
	}
	return (void*) NULL;
}

void	check(t_academy *a)
{
	struct timeval	tv;
	struct timeval	last_eat;
	char	finished;
	char	finished0;
	char	start;
	int	i;

	start = 0;
	while (!start)
	{
		start = 1;
		i = -1;
		while (++i < a->n_ph)
			if (!m_get(&a->phs[i].created, &a->phs[i].m_p))
				start = 0;
		usleep(1);
	}
	m_set(&a->start, 1, &a->m_a);
	gettimeofday(&a->t0, NULL);
	i = -1;
	while (++i < a->n_ph)
		a->phs[i].last_eat = a->t0;
	char	eated;
	eated = 0;
	while (!eated)
	{
		eated = 1;
		i = -1;
		while (++i < a->n_ph)
			if (!m_get(&a->phs[i].eated, &a->phs[i].m_p))
				eated = 0;
		usleep(1);
	}
	finished = 0;
	while (!a->died && !finished)
	{
		finished = 1;
		i = -1;
		while (++i < a->n_ph)
		{
			pthread_mutex_lock(&a->phs[i].m_p);
			finished0 = a->phs[i].finished;
			pthread_mutex_unlock(&a->phs[i].m_p);
			if (!finished0)
			{
				pthread_mutex_lock(&a->phs[i].m_p);
				last_eat = a->phs[i].last_eat;
				pthread_mutex_unlock(&a->phs[i].m_p);
				if (now_time_interval(&tv, &last_eat) > a->t_d)
				{
					m_set(&a->died, 1, &a->m_a);
					pthread_mutex_lock(&a->m_write);
					printf("%d %d died\n", get_time_interval(&tv, &a->t0), a->phs[i].id);
					pthread_mutex_unlock(&a->m_write);
					break ;
				}
				finished = 0;
			}
		}
	}
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
	t_academy	a;

	if (argc < 5 || argc > 6)
		return (1);
	a.n_ph = ft_atoi(argv[1]);
	a.t_d = ft_atoi(argv[2]) * 1000;
	a.t_e = ft_atoi(argv[3]) * 1000;
	a.t_s = ft_atoi(argv[4]) * 1000;
	//a.t_t = (a.t_d - a.t_e) / 4;
	if (a.t_s < a.t_e)
		a.t_t = a.t_s;
	else
		a.t_t = a.t_e;
	a.n_e = -1;
	if (argc == 6)
		a.n_e = ft_atoi(argv[5]);
	a.died = 0;
	a.start = 0;
	a.phs = malloc(sizeof(t_philo) * a.n_ph);
	if (!a.phs)
		return (1);
	if (a.n_ph == 1)
		a.forks = malloc(sizeof(pthread_mutex_t) * 2);
	else
		a.forks = malloc(sizeof(pthread_mutex_t) * a.n_ph);
	if (!a.forks)
	{
		free(a.forks);
		return (1);
	}
	if (pthread_mutex_init(&a.m_a, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&a.m_write, NULL) != 0)
		return (1);
	i = -1;
	while (++i < a.n_ph)
	{
		gettimeofday(&a.phs[i].last_eat, NULL);
		//a.phs[i].last_eat = NULL;
		a.phs[i].id = i + 1;
		a.phs[i].n_e = 0;
		a.phs[i].created = 0;
		a.phs[i].eated = 0;
		a.phs[i].finished = 0;
		a.phs[i].a = &a;
		a.phs[i].if1 = i;
		a.phs[i].if2 = i + 1;
		if (pthread_mutex_init(&a.phs[i].m_p, NULL) != 0)
			free_prog(&a, EXIT_FAILURE);
		if (pthread_mutex_init(&a.forks[i], NULL) != 0)
			free_prog(&a, EXIT_FAILURE);
	}
	if (a.n_ph == 1)
	{
		a.phs[0].if2 = 1;
		if (pthread_mutex_init(&a.forks[1], NULL) != 0)
			free_prog(&a, EXIT_FAILURE);
	}
	else
	{
		a.phs[i - 1].if1 = 0;
		a.phs[i - 1].if2 = i - 1;
	}
	gettimeofday(&a.t0, NULL);
	i = -1;
	while (++i < a.n_ph)
	{
		if (pthread_create(&a.phs[i].th, NULL, &life, &a.phs[i]))
			end_prog(&a, EXIT_FAILURE);
	}
	check(&a);
	i = -1;
	while (++i < a.n_ph)
		pthread_join(a.phs[i].th, NULL);
	//printf("End\n");
	end_prog(&a, EXIT_SUCCESS);
}
