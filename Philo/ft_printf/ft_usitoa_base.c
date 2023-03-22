/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usitoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:58:11 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/18 08:41:59 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "libft.h"

static int	get_base(char *base)
{
	int		i;
	int		j;
	char	*c;

	c = base;
	i = 0;
	while (*base)
	{
		if (*base == '+' || *base == '-' || (!(*base >= 33 && *base <= 126)))
			return (0);
		j = 0;
		while (j < i)
		{
			if (c[j] == *base)
				return (0);
			j++;
		}
		i++;
		base++;
	}
	if (i < 2)
		return (0);
	return (i);
}

static char	*itoa_base(char *base, int n_base, unsigned int i)
{
	int				j;
	int				mod;
	char			*str;
	unsigned int	i0;

	i0 = i;
	j = 0;
	while (i)
	{
		i = (i - i % n_base) / n_base;
		j++;
	}
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (0);
	str[j] = 0;
	i = i0;
	j--;
	while (i)
	{
		mod = i % n_base;
		i = (i - mod) / n_base;
		str[j--] = base[mod];
	}
	return (str);
}

char	*ft_usitoa_base(char *base, unsigned int i)
{
	int					n_base;
	char				*str;

	if (!i)
	{
		str = malloc(sizeof(char) * 2);
		if (!str)
			return (0);
		ft_strlcpy(str, "0", 2);
		return (str);
	}
	n_base = get_base(base);
	if (n_base == 0)
		return (0);
	return (itoa_base(base, n_base, i));
}
