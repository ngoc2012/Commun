/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/21 23:40:27 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define SEM_FORKS "SEM_FORKS"
# define SEM_WRITE "SEM_WRITE"
# define SEM_DIED "SEM_DIED"
# define SEM_START "SEM_START"
# define SEM_STARTED "SEM_STARTED"

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>

typedef struct s_academy	t_academy;

struct	s_academy
{
	int				id;
	int				n_ph;
	int				t_d;
	int				t_e;
	int				t_s;
	int				t_t;
	int				n_e;
	pid_t			*phs;
	struct timeval	t0;
	struct timeval	tv;
	struct timeval	last_eat;
	struct timeval	last_sleep;
	struct timeval	last_think;
	pthread_t		th_stopped;
	pthread_t		th_died;
	sem_t			*sem_forks;
	sem_t			*sem_write;
	sem_t			**sem_died;
	sem_t			**sem_started;
	sem_t			*sem_start;
	sem_t			sem_last_eat;
	sem_t			sem_die;
	char			eated;
	char			died;
	char			**sem_died_str;
	char			**sem_started_str;
};

int		now_time_interval(struct timeval *tv1, struct timeval *tv2);
int		get_time_interval(struct timeval *tv1, struct timeval *tv2);
int		get_time_interval_micro(struct timeval *tv1, struct timeval *tv2);
void	philo(t_academy	*a, int i);
void	end_process(t_academy *a, int erro);
void	end_prog(t_academy *a, int erro);
void	free1(t_academy *a, int erro);
void	*thread_stopped(void *a0);
void	*thread_died(void *a0);
sem_t	*try_open(char *s, int n);
char	*get_sem_str(const char *s, int j);
void	init(t_academy *a);
char	get_sem(char *v, sem_t *s);
char	set_sem(char *v, int v0, sem_t *s);
void	print_now_sem(t_academy *a, char *s);

#endif
