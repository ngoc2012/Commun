/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:56:59 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/08 14:11:42 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*o;
	char	*p;

	o = (char *) malloc(sizeof(char) * (ft_strlen(src) + 1));
	p = o;
	while (*src)
	{
		*o = *src;
		src++;
		o++;
	}
	*o = 0;
	return (p);
}
