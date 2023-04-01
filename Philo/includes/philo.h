/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/01 11:12:47 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_academy t_academy;

typedef struct	s_philo
{
	int		id;
	int		fork1;
	int		fork2;
	struct timeval	last_eat;
	struct timeval	last_sleep;
	int		n_e;
	pthread_t	th;
	t_academy	*a;
}	t_philo;

struct	s_academy
{
	int	n_ph;
	int	t_d;
	int	t_e;
	int	t_s;
	int	n_e;
	struct timeval t0;
	struct timeval tv;
	t_philo	*phs;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
};

#endif
