/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:39:09 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/03/16 14:56:45 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

unsigned char	*g_s;

void	end(int *len)
{
	write(1, g_s, *len + 1);
	free(g_s);
	g_s = malloc(sizeof(unsigned char));
	if (!g_s)
		exit(EXIT_FAILURE);
	g_s[0] = 0;
	*len = 0;
	ft_printf("\nServer ID: %d | Waiting for the signal...\n", getpid());
}

void	get_char(unsigned char c, int *len)
{
	unsigned char	*new;
	unsigned char	*tmp;

	(*len)++;
	if (*len % BUFFER == 1)
	{
		new = malloc(sizeof(unsigned char) * (*len + BUFFER + 1));
		if (!new)
		{
			free(g_s);
			exit(EXIT_FAILURE);
		}
		ft_memcpy(new, g_s, *len);
		tmp = g_s;
		g_s = new;
		free(tmp);
	}
	ft_memcpy(&g_s[*len], &c, 1);
	g_s[*len + 1] = 0;
}

void	end_handler(int sig)
{
	(void)sig;
	free(g_s);
	exit(EXIT_SUCCESS);
}

void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	static int				len = 0;
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
			end(&len);
			kill((int) info->si_pid, SIGUSR2);
			return ;
		}
		else
			get_char(c, &len);
		c = 0;
	}
	kill((int) info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;

	g_s = malloc(sizeof(unsigned char));
	if (!g_s)
		exit(EXIT_FAILURE);
	g_s[0] = 0;
	act.sa_flags = SA_NODEFER | SA_RESTART | SA_SIGINFO;
	act.sa_sigaction = &signal_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	signal(SIGINT, &end_handler);
	ft_printf("Server ID: %d | Waiting for the signal...\n", getpid());
	while (pause() == -1)
	{
		sigemptyset(&act.sa_mask);
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGUSR2, &act, NULL);
	}
	exit(EXIT_SUCCESS);
}
