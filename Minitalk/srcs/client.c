/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:39:09 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/03/21 09:21:37 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_server_catched;

void	sigusr_handler(int sig)
{
	g_server_catched = 1;
	if (sig == SIGUSR2)
		ft_printf("Message sent\n");
	return ;
}

void	connection_fail(void)
{
	ft_printf("Connection to server failed\n");
	exit(EXIT_FAILURE);
}

void	send_bits(int server_id, unsigned char c)
{
	int				i;
	int				j;
	unsigned char	c0;

	c0 = 1;
	i = -1;
	while (++i < 8)
	{
		j = 0;
		g_server_catched = 0;
		if (c0 & c)
			kill(server_id, SIGUSR2);
		else
			kill(server_id, SIGUSR1);
		while (!g_server_catched && ++j)
		{
			usleep(1);
			if (j > 10000)
				connection_fail();
		}
		c0 <<= 1;
	}
}

int	main(int argc, char **argv)
{
	int					i;
	int					server_id;
	struct sigaction	act;

	if (argc != 3)
		exit(EXIT_FAILURE);
	act.sa_flags = SA_NODEFER | SA_RESTART;
	act.sa_handler = sigusr_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	server_id = ft_atoi(argv[1]);
	i = -1;
	while (argv[2][++i])
	{
		if (!send_unicode(&argv[2][i], server_id, &i))
			send_bits(server_id, argv[2][i]);
	}
	send_bits(server_id, 0);
	exit(EXIT_SUCCESS);
}
