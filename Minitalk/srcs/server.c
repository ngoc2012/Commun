/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:39:09 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/03/10 16:02:11 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include<signal.h>

void	signal_handler(int sig, siginfo_t *info, void *)
{
	static int		i = 0;
	static unsigned char	c = 0;

	if (sig == SIGUSR2)
		c |= (1 << i);
	i++;
	if (i == 8)
	{
		i = 0;
		if (c == 0)
		{
			write(1, "\n", 1);
			kill((int) info->si_pid, SIGUSR2);
			return ;
		}
		else
			write(1, &c, 1);
		c = 0;
	}
	kill((int) info->si_pid, SIGUSR1);
}

int	main()
{
	struct sigaction	act;

	act.sa_flags = SA_NODEFER | SA_RESTART | SA_SIGINFO;
	act.sa_sigaction = &signal_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	ft_printf("%d\n", getpid());
	while (pause() == -1)
	{
		sigemptyset(&act.sa_mask);
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGUSR2, &act, NULL);
	}
	exit(EXIT_SUCCESS);
}
