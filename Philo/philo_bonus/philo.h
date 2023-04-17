/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/17 00:27:26 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define SEM_FORKS "SEM_FORKS6"
# define SEM_WRITE "SEM_WRITE6"
# define SEM_DIED "SEM_DIED6"
# define SEM_STARTED "SEM_STARTED6"
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
	struct timeval	last_eat0;
	struct timeval	last_eat;
	struct timeval	last_sleep;
	struct timeval	last_think;
	sem_t	*sem_forks;
	sem_t	*sem_write;
	sem_t	**sem_died;
	sem_t	**sem_started;
	sem_t	sem_has_fork;
	char			eated;
	char			died;
	//char			finished;
	char			has_fork;
	char			**sem_died_str;
	char			**sem_started_str;
};

int	now_time_interval(struct timeval *tv1, struct timeval *tv2);
int	get_time_interval(struct timeval *tv1, struct timeval *tv2);
int	get_time_interval_micro(struct timeval *tv1, struct timeval *tv2);
void	philo(t_academy	*a, int i);

#endif
