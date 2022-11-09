/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 09:55:02 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/09/26 10:18:33 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

void	write_characters(unsigned char *str, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < 16 && i < size)
	{
		if (str[i] >= 32 && str[i] <= 126)
			write(1, &str[i], 1);
		else
			write(1, ".", 1);
		i++;
	}
}

void	write_hex(unsigned char *str, unsigned int size)
{
	unsigned int	i;
	char			*hex;

	hex = "0123456789abcdef";
	i = 0;
	while (i < 16 && i < size)
	{
		write(1, &hex[((str[i] - str[i] % 16) / 16) % 16], 1);
		write(1, &hex[str[i] % 16], 1);
		if (i % 2 == 1)
			write(1, " ", 1);
		i++;
	}
	while (i < 16)
	{
		write(1, "  ", 2);
		if (i % 2 == 1)
			write(1, " ", 1);
		i++;
	}
}

void	write_address(long unsigned int i)
{
	int		j;
	int		mod;
	char	str[16];
	char	*hex;

	hex = "0123456789abcdef";
	j = 0;
	while (i != 0)
	{
		mod = i % 16;
		i = (i - mod) / 16;
		str[j++] = hex[mod];
	}
	while (j < 16)
		str[j++] = '0';
	j = 0;
	while (j <= 15)
		write(1, &str[15 - j++], 1);
	write(1, ": ", 2);
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	unsigned int	i;

	if (size == 0)
		return (addr);
	i = 0;
	while (i < size)
	{
		write_address((long unsigned int) addr + i);
		write_hex(addr + i, size - i);
		write_characters(addr + i, size - i);
		write(1, "\n", 1);
		i += 16;
	}
	return (addr);
}
