/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoffaux <sgoffaux@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:01:47 by sgoffaux          #+#    #+#             */
/*   Updated: 2023/04/01 08:29:37 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
	//return ((time.tv_sec * (unsigned long)1000000) + (time.tv_usec));
}

void	new_sleep(unsigned long duration, t_env *env)
{
	unsigned long	start;

	start = get_time();
	while (!env->stop_condition)
	{
		if (get_time() - start >= duration)
			break ;
		usleep(env->count * 2);
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_return_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (0);
}

int	ft_isint(const char *nptr)
{
	int		i;
	int		neg;
	long	value;

	i = 0;
	value = 0;
	neg = 0;
	while ((nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if (nptr[i] == '-')
		neg = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && (nptr[i] >= 48 && nptr[i] <= 57))
	{
		if (value > 214748364 || (value == 214748364
				&& ((!neg && nptr[i] - '0' > 7) || (neg && nptr[i] - '0' > 8))))
			return (0);
		else
			value = (value * 10) + nptr[i++] - '0';
	}
	return (1);
}
