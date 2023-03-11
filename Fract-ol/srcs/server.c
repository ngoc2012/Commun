/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:39:09 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/03/10 19:56:34 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	static int				i = 0;
	static unsigned char	c = 0;

	(void)ucontext;
	if (sig == SIGUSR2)
		c |= (1 << i);
	i++;
	if (i == 8)
	{
		i = 0;
		if (c == 0)
		{
			ft_printf("\nServer ID: %d | Waiting for the signal...\n", getpid());
			kill((int) info->si_pid, SIGUSR2);
			return ;
		}
		else
			write(1, &c, 1);
		c = 0;
	}
	kill((int) info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;

	act.sa_flags = SA_NODEFER | SA_RESTART | SA_SIGINFO;
	act.sa_sigaction = &signal_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	ft_printf("Server ID: %d | Waiting for the signal...\n", getpid());
	while (pause() == -1)
	{
		sigemptyset(&act.sa_mask);
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGUSR2, &act, NULL);
	}
	exit(EXIT_SUCCESS);
}
