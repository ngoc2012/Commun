/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 08:38:58 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/19 09:39:47 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	binary(int n, int level)
{
	char	base[] = "01";

	if (level > 1)
		binary(n / 2, level - 1);
	write(1, &base[n % 2], 1);
}

unsigned char	swap_bits(unsigned char c)
{
	unsigned char d = c;
	unsigned char o;

	binary((int) c, 8);
	write(1, "\n", 1);
	c <<= 4;
	binary((int) c, 8);
	write(1, "\n", 1);
	o = 0;
	binary((int) o, 8);
	write(1, "\n", 1);
	o |= c;
	binary((int) o, 8);
	write(1, "\n", 1);
	d >>= 4;
	binary((int) d, 8);
	write(1, "\n", 1);
	o |= d;
	binary((int) o, 8);
	write(1, "\n", 1);
	return (d);
}

int	main()
{
	//swap_bits('a');
	//binary(1L << 4, 8);
	//write(1, "\n", 1);
}
