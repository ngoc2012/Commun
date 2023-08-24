/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/07 17:45:56 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isenv(char c)
{
	return (ft_isalnum(c) || c == '_');
}

// All character is alpha num or _
int	is_all_env(char *s, int p)
{
	int	i;

	i = -1;
	while (++i < p)
		if (!isenv(s[i]))
			return (0);
	return (1);
}

char	*get_env(char *s, char **ss)
{
	while (*ss)
	{
		if (!ft_strdcmp(*ss, s))
			return (&(*ss)[chr_pos(*ss, '=') + 1]);
		ss++;
	}
	return (0);
}
