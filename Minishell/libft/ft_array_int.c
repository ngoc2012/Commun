/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:24:45 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/16 19:31:11 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	aint_addback(int *a)
{
	int	*new;
	int	len;

	len = sizeof(a) / sizeof(int);
	new = malloc(sizeof(int) * (len + 1));

}
