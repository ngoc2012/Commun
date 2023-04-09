/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:11:40 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/18 08:40:58 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static unsigned long	pow_(int n)
{
	int	i;
	int	o;

	i = 0;
	o = 1;
	while (i++ < n)
		o *= (unsigned long) 10;
	return (o);
}

static int	get_len(unsigned long n)
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

static void	get_num(unsigned long n, char *s, int len)
{
	unsigned long	i;
	char			*base;

	base = "0123456789";
	while (len)
	{
		i = n / pow_(len - 1);
		*s = base[i];
		n -= i * pow_(len - 1);
		len--;
		s++;
	}
	*s = 0;
}

char	*ft_usitoa(unsigned int n)
{
	int		len;
	char	*s;

	if (n == 0)
		return (ft_strdup("0"));
	len = get_len(n);
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (0);
	get_num((unsigned long) n, s, len);
	return (s);
}
