/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/28 16:41:10 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_academy	t_academy;

typedef struct s_philo
{
	int				id;
	t_academy		*a;
	pthread_t		th;
	int				if1;
	int				if2;
	struct timeval	fork1;
	struct timeval	fork2;
	struct timeval	last_eat0;
	struct timeval	last_eat;
	struct timeval	last_think;
	struct timeval	last_sleep;
	int				n_e;
	char			created;
	char			started;
	char			eated;
	char			finished;
	pthread_mutex_t	m_p;
	pthread_mutex_t	m_f;
	pthread_mutex_t	m_e;
	pthread_mutex_t	m_s;
}	t_philo;

struct	s_academy
{
	int				n_ph;
	int				t_d;
	int				t_e;
	int				t_s;
	int				t_t;
	int				n_e;
	struct timeval	t0;
	struct timeval	tv;
	t_philo			*phs;
	pthread_mutex_t	*forks;
	char			died;
	pthread_mutex_t	m_write;
	pthread_mutex_t	m_a;
	pthread_mutex_t	m_s;
};

int				now_time_interval(struct timeval *tv1, struct timeval *tv2);
int				get_time_interval(struct timeval *tv1, struct timeval *tv2);
char			m_get(char *v, pthread_mutex_t *m);
void			m_set(char *v, char i, pthread_mutex_t *m);
int				free_prog(t_academy *a, int erro);
int				end_prog(t_academy *a, int erro);
int				eating(t_philo *ph);
void			sleeping(t_philo *ph);
void			*life(void *ph0);
void			check(t_academy *a);
int				init(t_academy *a);
int				create(t_academy *a);
void			m_set_time(struct timeval *v,
					struct timeval *i, pthread_mutex_t *m);
struct timeval	m_get_time(struct timeval *v, pthread_mutex_t *m);

#endif
