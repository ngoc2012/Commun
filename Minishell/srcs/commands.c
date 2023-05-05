/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 08:41:16 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/05 14:01:23 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_ops(char *s, t_list ops)
{
	int		i;
	int		i0;

	ops = 0;
	while (*s && ft_strchr(" \n", *s))
		s++;
	i0 = 0;
	i = 0;
	while (s[i])
	{
		if (ft_strchr("()", s[i]))
		if (ft_strchr("\"'", s[i]))
		{
			i0 = ++i;
			while (s[++i] && s[i] != d)
				;
			i++;
		}
		else if (s[i] == ' ')
		{
			*ss = malloc(i - i0 + 1);
			ft_memcpy(*ss, &s[i0], i - i0);
			(*ss)[i - i0] = 0;
			ss++;
			while (s[++i] && s[i] == ' ')
				;
			i0 = i;
		}
		else
			i++;
	}
	return (1);
}
