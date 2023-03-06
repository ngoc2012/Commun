/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:39:09 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/03/05 18:57:15 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include<signal.h>

/*
 * You can't have data of your own passed to the signal handler as parameters. Instead you'll have to store your parameters in global variables. (And be really, really careful if you ever need to change those data after installing the the signal handler).
 */
int	con[BITS];

void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		ft_printf("SIGUSR1 %d\n", sig);
	}
	else if (sig == SIGUSR2)
	{
		ft_printf("SIGUSR2 %d\n", sig);
	}
	else
	{
		ft_printf("Other signal %d\n", sig);
	}
}

int	main()
{
	int	i;

	i = -1;
	while (++i < BITS)
		con[i] = -1;
	ft_printf("%d\n", getpid());
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (pause() == -1)
	{
		signal(SIGUSR1, signal_handler);
		signal(SIGUSR2, signal_handler);
	}
	exit(EXIT_SUCCESS);
}
