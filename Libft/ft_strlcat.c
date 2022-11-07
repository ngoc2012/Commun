/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 09:55:02 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/09/23 08:38:58 by minh-ngu         ###   ########.fr       */
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

void	process(char *dest, char *src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (*dest)
	{
		dest++;
		i++;
	}
	while (i < (size - 1) && *src && size != 0)
	{
		*dest = *src;
		src++;
		dest++;
		i++;
	}
	*dest = 0;
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	size_dst;

	size_dst = str_len(dest);
	process(dest, src, size);
	if (size_dst > size)
		return (size + str_len(src));
	else
		return (size_dst + str_len(src));
}
