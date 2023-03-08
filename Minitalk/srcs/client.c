/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:39:09 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/03/06 15:42:47 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include<signal.h>

int	pid;

void	convert(int n)
{
	int	i;

	if (n < 0)
		n += 256;
	i = -1;
	while (n)
	{
		if (n % 2 == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		n = n / 2;
		i++;
		usleep(SLEEP);
	}
	while (++i < BITS)
	{
		kill(pid, SIGUSR1);
		usleep(SLEEP);
	}
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc != 3)
		exit(EXIT_FAILURE);
	pid = ft_atoi(argv[1]);
	i = -1;
	while (argv[2][++i])
		convert((int) argv[2][i]);
	exit(EXIT_SUCCESS);
}
