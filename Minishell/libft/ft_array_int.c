/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:24:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/16 21:23:29 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	*aint_addback(int *a, int n)
{
	int	*new;
	int	i;
	int	len;

	if (!a)
		len = 0;
	else
		len = sizeof(a) / sizeof(int);
	new = malloc(sizeof(int) * (len + 1));
	if (!new)
		return (a);
	i = -1;
	while (++i < len) 
		new[i] = a[i];
	if (!a)
		new[0] = n;
	else
	{
		free(a);
		new[++i] = n;
	}
	return (new);
}
