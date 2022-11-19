/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:51:10 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/19 05:29:37 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	write_nbr(long x, int fd)
{
	char	*base;

	base = "0123456789";
	if (x > 9)
		write_nbr(x / 10, fd);
	write(fd, &base[x % 10], 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	x;

	x = (long) n;
	if (x < 0)
		write(fd, "-", 1);
	if (x < 0)
		write_nbr(-x, fd);
	else
		write_nbr(x, fd);
}
