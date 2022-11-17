/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:28:59 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/17 14:41:40 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	i;
	int	l;

	l = ft_strlen(little);
	if (l == 0)
		return ((char *) big);
	i = 0;
	while (((i < ((int) ft_strlen(big) - l + 1)
				&& i <= ((int) len - l)) || ((int) len < 0)) && big[i])
	{
		if (!ft_strncmp(&big[i], little, l))
			return ((char *) &(big[i]));
		i++;
	}
	return (0);
}
