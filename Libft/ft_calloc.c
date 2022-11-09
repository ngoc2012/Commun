/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:48:48 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/08 16:38:51 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*o;

	o = 0;
	if ((nmemb * size) == 0)
		return (o);
	if (nmemb > (INT_MAX / size))
		return (o);
	o = malloc(nmemb * size);
	ft_memset(o, 0, nmemb * size);
	return (o);
}
