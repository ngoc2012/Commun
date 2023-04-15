/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:53:28 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/11 16:05:12 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Time in milliseconds
int	get_time_interval(struct timeval *tv1, struct timeval *tv2)
{
	return ((int)((tv1->tv_sec - tv2->tv_sec) * 1000000
		+ tv1->tv_usec - tv2->tv_usec) / 1000);
}

int	get_time_interval_micro(struct timeval *tv1, struct timeval *tv2)
{
	return ((int)((int)(tv1->tv_sec - tv2->tv_sec) * 1000000 +
			(int)(tv1->tv_usec - tv2->tv_usec)));
}

int	now_time_interval(struct timeval *tv1, struct timeval *tv2)
{
	gettimeofday(tv1, NULL);
	return (get_time_interval_micro(tv1, tv2));
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}
