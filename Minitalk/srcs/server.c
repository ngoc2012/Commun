/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:39:09 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/03/13 16:39:24 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

unsigned char	*s;

int	slen(unsigned char *str)
{
	int	i;

	i = 0;
	while (*(str++))
		i++;
	return (i);
}

void	end()
{
	write(1, s, slen(s));
	free(s);
	s = malloc(sizeof(unsigned char));
	s[0] = 0;
	ft_printf("\nServer ID: %d | Waiting for the signal...\n", getpid());
}


void	get_char(unsigned char c)
{
	size = slen(s);
	new = malloc(sizeof(unsigned char) * (size + 2));
	ft_memcpy(new, s, size);
	ft_memcpy(&new[size], &c, 1);
	new[size + 1] = 0;
	tmp = s;
	s = new;
	free(tmp);
}

void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	static int				i = 0;
	static unsigned char	c = 0;
	unsigned char	*new;
	unsigned char	*tmp;
	int	size;

	(void)ucontext;
	if (sig == SIGUSR2)
		c |= (1 << i);
	i++;
	if (i == 8)
	{
		i = 0;
		if (c == 0)
		{
			end();
			kill((int) info->si_pid, SIGUSR2);
			return ;
		}
		else
			get_char(c);
		c = 0;
	}
	kill((int) info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;

	s = malloc(sizeof(unsigned char));
	s[0] = 0;
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
