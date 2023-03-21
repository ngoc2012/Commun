/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:39:09 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/03/21 09:24:26 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//https://r12a.github.io/app-conversion/
int	base16(char c)
{
	if (c >= 48 && c <= 57)
		return ((int) c - 48);
	if (c >= 97 && c <= 102)
		return ((int) c - 87);
	if (c >= 65 && c <= 70)
		return ((int) c - 55);
	return (0);
}

void	bits_op1(unsigned char *c, int *n)
{
	*c |= *n;
	*c |= (1 << 7);
	*c &= ~(1 << 6);
	*n >>= 6;
}

void	bits_op2(unsigned char *c, int *n, int i)
{
	*c |= *n;
	while (i-- > 0)
		*c |= (1 << (7 - i));
}

void	send_bits_unicode(int server_id, int n)
{
	int				i;
	int				j;
	unsigned char	c[4];

	i = -1;
	while (++i < 4)
		c[i] = 0;
	i = 0;
	if (n <= 127)
		send_bits(server_id, (unsigned char) n);
	else if (n <= 2047)
		i = 2;
	else if (n <= 65535)
		i = 3;
	else if (n <= 1114111)
		i = 4;
	j = -1;
	while (++j < i)
		bits_op1(&c[j], &n);
	if (i > 0)
		bits_op2(&c[i - 1], &n, i);
	while (--i >= 0)
		send_bits(server_id, c[i]);
}

//https://en.wikipedia.org/wiki/UTF-8#Description
int	send_unicode(char *s, int server_id, int *ind)
{
	int	i;
	int	n;

	if (ft_tolower(*s) != 'u')
		return (0);
	if (*(++s) != '+')
		return (0);
	s++;
	n = 0;
	i = -1;
	while (++i < 6 && n <= 1114111 && ((s[i] >= 48 && s[i] <= 57)
			|| (s[i] >= 97 && s[i] <= 102) || (s[i] >= 65 && s[i] <= 70)))
		n = n * 16 + base16(s[i]);
	if (i < 4)
		return (0);
	if (i == 6 && n > 1114111)
		n = (n - base16(s[i - 1])) / 16;
	*ind += i + 1;
	send_bits_unicode(server_id, n);
	return (1);
}
