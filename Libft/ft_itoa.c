/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:11:40 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/12 14:56:39 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

void	get_num(int len, long n, char *s, int level)
{
	int		i;
	char	*base;

	i = 0;
	base = "0123456789";
	if (n != 0)
	{
		get_num(len, (n - n % 10) / 10, s, level + 1);
		i++;
	}
	s[len - 1 - level] = base[n % 10];
}

int	get_len(long n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n = (n - n % 10) / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n0)
{
	int		i;
	int		j;
	long	n;
	char	*s;

	n = (long) n0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n0 < 0)
		n = -n;
	i = get_len(n);
	j = 0;
	if (n0 < 0)
		j = 1;
	s = malloc(sizeof(char) * (i + 1 + j));
	if (s == NULL)
		return (0);
	if ((long) n0 < 0)
		s[0] = '-';
	get_num(i, n, &s[j], 0);
	s[i + j] = 0;
	return (s);
}
