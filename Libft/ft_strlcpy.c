/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 09:55:02 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/09/22 03:59:51 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

unsigned int	str_len(char *str)
{
	unsigned int	size;

	size = 0;
	while (*str != '\0')
	{
		str++;
		size++;
	}
	return (size);
}

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	char			*s;
	char			*d;
	unsigned int	size_src;
	unsigned int	i;

	size_src = str_len(src);
	s = src;
	d = dest;
	i = 0;
	while (i < (size - 1) && i < size_src && size != 0)
	{
		*dest = *src;
		src++;
		dest++;
		i++;
	}
	*dest = 0;
	dest = d;
	src = s;
	return (size_src);
}
