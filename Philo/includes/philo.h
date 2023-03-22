/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/22 12:28:30 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <sys/time.h>
# include "ft_printf.h"
# include "libft.h"

typedef struct	s_philo
{
	int	id;
	void	(*fork)(void);
	void	(*eating)(void);
	void	(*sleeping)(void);
	void	(*thinking)(void);
	void	(*died)(void);
}	t_philo;

typedef struct	s_academy
{
	int	n_ph;
	int	t_d;
	int	t_e;
	int	t_s;
	int	n_e;
	int	t0;
	t_philo	*phs;
}	t_academy;

#endif
