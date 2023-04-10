/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/10 00:23:27 by ngoc             ###   ########.fr       */
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
		//if (&a->phs[i].m_eated)
		//	pthread_mutex_destroy(&a->phs[i].m_eated);
		if (&a->forks[i])
			pthread_mutex_destroy(&a->forks[i]);
	}
	if (&a->m_write)
		pthread_mutex_destroy(&a->m_write);
	if (&a->m_order)
		pthread_mutex_destroy(&a->m_order);
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
	pthread_mutex_lock(&ph->a->m_write);
	//print_int(get_time_interval(tv, &ph->a->t0));
	//print_int(((tv->tv_sec - ph->a->t0.tv_sec) * 1000000 + (tv->tv_usec - ph->a->t0.tv_usec)) / 1000);
	print_int((tv->tv_sec - ph->a->t0.tv_sec) * 1000000 + (tv->tv_usec - ph->a->t0.tv_usec));
	write(1, " ", 1);
	print_int(ph->id);
	while (*s)
		write(1, s++, 1);
	pthread_mutex_unlock(&ph->a->m_write);
}

void	eating(t_philo *ph)
{
	struct timeval	tv;
	t_timestamp	*ts;

	pthread_mutex_lock(&ph->a->forks[ph->if1]);
	gettimeofday(&ph->fork1, NULL);
	pthread_mutex_lock(&ph->a->forks[ph->if2]);
	gettimeofday(&ph->fork2, NULL);
	pthread_mutex_lock(&ph->a->m_a);
	ts = malloc(sizeof(t_timestamp));
	ts->tv = ph->fork2;
	ts->id = ph->id;
	ts->state = e_eat;
	ts->next = 0;
	if (ph->a->ts == 0)
	{
		ph->a->ts = ts;
		ph->a->ts0 = ts;
	}
	else
	{
		ph->a->ts.next = ts;
		ph->a->ts = ts;
	}
	pthread_mutex_unlock(&ph->a->m_a);
	pthread_mutex_lock(&ph->a->m_order);
	if (m_get(&ph->a->died, &ph->a->m_a))
	{
		pthread_mutex_unlock(&ph->a->m_order);
		pthread_mutex_unlock(&ph->a->forks[ph->if2]);
		pthread_mutex_unlock(&ph->a->forks[ph->if1]);
		return ;
	}
	print(ph, &ph->fork2, " has taken a fork\n");
	print(ph, &ph->fork2, " has taken a fork\n");
	print(ph, &ph->fork2, " is eating\n");
	pthread_mutex_lock(&ph->m_p);
	ph->last_eat = ph->fork2;
	pthread_mutex_unlock(&ph->m_p);
	m_set(&ph->eated, 1, &ph->m_p);
	ph->n_e++;
	if (ph->a->n_e != -1 && ph->n_e == ph->a->n_e)
	{
		m_set(&ph->finished, 1, &ph->m_p);
		pthread_mutex_unlock(&ph->a->m_order);
		pthread_mutex_unlock(&ph->a->forks[ph->if2]);
		pthread_mutex_unlock(&ph->a->forks[ph->if1]);
		return ;
	}
	pthread_mutex_unlock(&ph->a->m_order);
	while (now_time_interval(&tv, &ph->fork2) <= ph->a->t_e
			&& !m_get(&ph->a->died, &ph->a->m_a))
		;
	pthread_mutex_lock(&ph->m_p);
	ph->last_eat = tv;
	pthread_mutex_unlock(&ph->m_p);
	pthread_mutex_unlock(&ph->a->forks[ph->if2]);
	pthread_mutex_unlock(&ph->a->forks[ph->if1]);
}

void	sleeping(t_philo *ph)
{
	pthread_mutex_lock(&ph->a->m_order);
	print(ph, &ph->last_eat, " is sleeping\n");
	pthread_mutex_unlock(&ph->a->m_order);
	while (now_time_interval(&ph->last_sleep, &ph->last_eat) < ph->a->t_s
			&& !m_get(&ph->a->died, &ph->a->m_a))
		;
	if (m_get(&ph->finished, &ph->m_p) || m_get(&ph->a->died, &ph->a->m_a))
		return ;
	pthread_mutex_lock(&ph->a->m_order);
	print(ph, &ph->last_sleep, " is thinking\n");
	pthread_mutex_unlock(&ph->a->m_order);
	usleep((ph->a->t_d - ph->a->t_e) / 2);
}

void	*life(void *ph0)
{
	t_philo *ph;

	ph = (t_philo*) ph0;
	m_set(&ph->created, 1, &ph->m_p);
	while (!m_get(&ph->a->start, &ph->a->m_a))
		usleep(1);
	while (!m_get(&ph->finished, &ph->m_p) && !m_get(&ph->a->died, &ph->a->m_a))
	{
		eating(ph);
		if (m_get(&ph->finished, &ph->m_p) || m_get(&ph->a->died, &ph->a->m_a))
			break;
		sleeping(ph);
	}
	return (void*) NULL;
}

void	check(t_academy *a)
{
	struct timeval	tv;
	char	finished;
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
	t_timestamp	*prev;
	finished = 0;
	while (!a->died && !finished)
	{
		while (a->ts0 != 0)
		{
			prev = a->ts0;
			print(&a->phs[a->ts.id - 1], a->tv, " hehe\n");
			a->ts = a->ts.next;
		}
		finished = 1;
		i = -1;
		while (++i < a->n_ph && !m_get(&a->phs[i].finished, &a->phs[i].m_p))
		{
			if (now_time_interval(&tv, &a->phs[i].last_eat) > a->t_d && get_time_interval_micro(&tv, &a->phs[i].last_eat) > 0)
			{
				m_set(&a->died, 1, &a->m_a);
				pthread_mutex_lock(&a->m_order);
				print(&a->phs[i], &tv, " died\n");
				pthread_mutex_unlock(&a->m_order);
				//print(&a->phs[i], &a->phs[i].last_eat, " last eat\n");
				break ;
			}
			finished = 0;
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
	a.n_e = -1;
	if (argc == 6)
		a.n_e = ft_atoi(argv[5]);
	a.died = 0;
	a.start = 0;
	a.ts = 0;
	a.ts0 = 0;
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
	if (pthread_mutex_init(&a.m_order, NULL) != 0)
		return (1);
	i = -1;
	while (++i < a.n_ph)
	{
		gettimeofday(&a.phs[i].last_eat, NULL);
		a.phs[i].id = i + 1;
		a.phs[i].n_e = 0;
		a.phs[i].created = 0;
		a.phs[i].eated = 0;
		a.phs[i].finished = 0;
		a.phs[i].a = &a;
		a.phs[i].if1 = i;
		a.phs[i].if2 = i + 1;
		a.ts = 0;
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
