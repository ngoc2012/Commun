/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_val.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/12 22:29:08 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static float	abs_val(int i)
{
	if (i < 0)
		return ((float)(i + 256));
	if (i >= 65 && i <= 90)
		return ((float)(i + 32) - 0.5);
	return (i);
}

int	ft_strcmp_val(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	if (*s1 == '\\')
		s1++;
	if (*s2 == '\\')
		s2++;
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
		if (*s1 == '\\')
			s1++;
		if (*s2 == '\\')
			s2++;
	}
	if (abs_val(*s1) <= abs_val(*s2))
		return (1);
	return (0);
}
