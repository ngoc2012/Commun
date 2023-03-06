/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:39:09 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/03/05 18:52:22 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include<signal.h>

void	convert(int n)
{
	int	i;

	i = -1;
	while (n)
	{
		//ft_printf("%d", n % 2);
		if (n % 2 == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		n = n / 2;
		i++;
	}
	while (++i < BITS)
		kill(pid, SIGUSR1);
		//ft_printf("0");
}

int	main(int argc, char **argv)
{
	//int	pid;
	int	i;

	if (argc != 3)
		exit(EXIT_FAILURE);
	//pid = ft_atoi(argv[1]);
	//ft_printf("%d\n", pid);
	i = -1;
	while (argv[2][++i])
		convert((int) argv[2][i]);
	ft_printf("%c", 222);
	printf("%c", 222);
	char happy[] = { 0xe2, 0x98, 0xba };  /* U+263A */
	write(1, happy, 3);
	exit(EXIT_SUCCESS);
}
