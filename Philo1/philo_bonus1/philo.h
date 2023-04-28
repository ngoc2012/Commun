/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/19 20:02:31 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define SEM_FORKS "SEM_FORKS3"
# define SEM_WRITE "SEM_WRITE3"
# define SEM_DIED "SEM_DIED3"
# define SEM_START "SEM_START3"
# define SEM_STARTED "SEM_STARTED3"
# define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
# define DELAY 100

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
	pthread_t	th_stopped;
	pthread_t	th_died;
	sem_t	*sem_forks;
	sem_t	*sem_write;
	sem_t	**sem_died;
	sem_t	**sem_started;
	sem_t	*sem_start;
	sem_t	sem_last_eat;
	sem_t	sem_die;
	char			eated;
	char			died;
	char			**sem_died_str;
	char			**sem_started_str;
};

int	now_time_interval(struct timeval *tv1, struct timeval *tv2);
int	get_time_interval(struct timeval *tv1, struct timeval *tv2);
int	get_time_interval_micro(struct timeval *tv1, struct timeval *tv2);
void	philo(t_academy	*a, int i);
void	end_process(t_academy *a, int erro);
void    *thread_stopped(void *a0);
void    *thread_died(void *a0);

#endif
