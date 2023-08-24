/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:14:50 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/08 13:53:35 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strdcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 == *s2 && *s1 && *s2
		&& !ft_strchr("=+", *s1) && !ft_strchr("=+", *s2))
	{
		s1++;
		s2++;
	}
	if ((!*s1 && ft_strchr("=+", *s2)) || (!*s2 && ft_strchr("=+", *s1))
		|| (ft_strchr("=+", *s1) && ft_strchr("=+", *s2)))
		return (0);
	return ((unsigned char) *s1 - (unsigned char) *s2);
}
