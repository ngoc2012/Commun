/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoinm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:40:57 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/31 16:14:50 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"
#include <stdio.h>

#define BUFFER_STRJOIN 5

static char	*check(char *des, char *src, int *len_des, int *len_src)
{
	if (*len_des < 0)
		*len_des = ft_strlen(des);
	if (*len_src < 0)
		*len_src = ft_strlen(src);
	if (!*len_des && !des)
	{
		des = malloc(BUFFER_STRJOIN);
		if (!des)
			return (0);
		des[0] = 0;
	}
	return (des);
}

char	*strjoinm(char *des, char *src, int len_des, int len_src)
{
	int		n;
	int		n0;
	char	*new_str;

	des = check(des, src, &len_des, &len_src);
	if (!len_des && !des)
		return (0);
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
