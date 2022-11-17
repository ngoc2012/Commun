/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:28:59 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/08 15:20:31 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	m;
	size_t	l;
	char	*o;

	l = ft_strlen(little);
	if (l == 0)
		return ((char *) big);
	m = 0;
	i = 0;
	while (i < len && big[i])
	{
		if (big[i] == little[m])
			m++;
		else
			m = 0;
		if (m == l)
		{
			o = (char *) &(big[i - m + 1]);
			return (o);
		}
		i++;
	}
	return (0);
}
