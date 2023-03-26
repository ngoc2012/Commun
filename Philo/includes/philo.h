/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/24 16:02:32 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "ft_printf.h"
# include "libft.h"

typedef struct	s_academy t_academy;

typedef struct	s_philo
{
	int		id;
	int		last_eat;
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
	int	t0;
	t_philo	*phs;
	pthread_mutex_t	*forks;
};

#endif
