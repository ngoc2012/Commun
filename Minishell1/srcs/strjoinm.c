/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoinm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:40:57 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/04 22:55:43 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFFER_STRJOIN 5

#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"
#include <stdio.h>

char	*strjoinm(char *des, char *src, int len_des, int len_src)
{
	int		n;
	int		n0;
	char	*new_str;

	if (!len_des && !des)
	{
		des = malloc(BUFFER_STRJOIN);
		if (!des)
			return (0);
		des[0] = 0;
	}
	if (!len_src || !src)
		return (des);
	n0 = len_des % BUFFER_STRJOIN;
	if (len_src + 1 + n0 > BUFFER_STRJOIN)
	{
		n = (len_src + len_des) / BUFFER_STRJOIN + 1;
		new_str = malloc(n * BUFFER_STRJOIN);
		if (!new_str)
			return (0);
		ft_memcpy(new_str, des, len_des);
		free(des);
		des = new_str;
	}
	ft_memcpy(&des[len_des], src, len_src);
	des[len_des + len_src] = 0;
	return (des);
}
