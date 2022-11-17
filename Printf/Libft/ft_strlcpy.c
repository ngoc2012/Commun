/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 09:55:02 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/08 08:05:32 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	char	*s;
	char	*d;
	size_t	size_src;
	size_t	i;

	size_src = ft_strlen(src);
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
