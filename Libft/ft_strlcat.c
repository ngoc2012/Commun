/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 09:55:02 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/08 08:02:55 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	size_dst;
	size_t	i;

	size_dst = ft_strlen(dest);
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
	if (size_dst > size)
		return (size + ft_strlen(src));
	else
		return (size_dst + ft_strlen(src));
}
