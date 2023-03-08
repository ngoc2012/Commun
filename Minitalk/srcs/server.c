/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:39:09 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/03/06 14:39:29 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include<signal.h>

/*
 * You can't have data of your own passed to the signal handler as parameters. Instead you'll have to store your parameters in global variables. (And be really, really careful if you ever need to change those data after installing the the signal handler).
 */
int	con[BITS + 1];

void	signal_handler(int sig)
{
	int	i;
	int	c;
	int	k;

	con[0]++;
	if (sig == SIGUSR1)
		con[con[0]] = 0;
	else if (sig == SIGUSR2)
		con[con[0]] = 1;
	else
		exit(EXIT_FAILURE);
	if (con[0] == 8)
	{
		c = 0;
		k = 1;
		i = 0;
		while (++i < BITS + 1)
		{
			c += k*con[i];
			k *= 2;
		}
		con[0] = 0;
		write(1, &c, 1);
	}
}

int	main()
{
	struct sigaction	act;

	act.sa_handler = signal_handler;
	act.sa_flags = SA_NODEFER;
	sigemptyset(&act.sa_mask);
	//sigaddset(&act.sa_mask, SIGUSR1);
	//sigaddset(&act.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	//signal(SIGUSR1, signal_handler);
	//signal(SIGUSR2, signal_handler);
	con[0] = 0;
	ft_printf("%d\n", getpid());
	while (pause() == -1)
	{
		//sleep(100);
		//signal(SIGUSR1, signal_handler);
		//signal(SIGUSR2, signal_handler);
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGUSR2, &act, NULL);
	}
	exit(EXIT_SUCCESS);
}
