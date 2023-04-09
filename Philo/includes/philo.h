/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/08 15:50:00 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

enum e_state {e_fork1, e_fork2, e_eating, e_sleeping, e_thinking};

typedef struct	s_academy t_academy;

typedef struct	s_philo
{
	int		id;
	t_academy	*a;
	pthread_t	th;
	int		if1;
	int		if2;
	enum e_state	state;
	struct timeval	fork1;
	struct timeval	fork2;
	struct timeval	last_eat;
	struct timeval	last_sleep;
	int		n_e;
	char	created;
	char	eated;
	char	finished;
	pthread_mutex_t	m_p;
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
	pthread_t	survey;
	pthread_mutex_t	*forks;
	char	start;
	char	died;
	pthread_mutex_t	m_write;
	pthread_mutex_t	m_order;
	pthread_mutex_t	m_a;
};

#endif
