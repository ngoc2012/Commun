/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 08:45:31 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/11 22:06:51 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

// Get number of strings at the out put, must be 0 if all match
int	get_n_strs(char *str, char *charset)
{
	int	i;
	int	n_strs;

	i = 0;
	n_strs = 0;
	while (str[i])
	{
		while (ft_strchr(charset, str[i]) && str[i])
			i++;
		if (str[i])
			n_strs++;
		while (!ft_strchr(charset, str[i]) && str[i])
			i++;
	}
	return (n_strs);
}

// Get chunks (begin and end) of string to output
void	get_strs(char *str, char *charset, char **out)
{
	int		i;
	int		start;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (ft_strchr(charset, str[i]) && str[i])
			i++;
		start = i;
		while (!ft_strchr(charset, str[i]) && str[i])
			i++;
		if (i > start)
		{
			out[j] = malloc(sizeof(char) * (i - start + 1));
			ft_strlcpy(out[j], &(str[start]), i - start + 1);
			j++;
		}
	}
}

char	**ft_split(char *str, char *charset)
{
	int		n_strs;
	char	**out;

	n_strs = get_n_strs(str, charset);
	out = malloc(sizeof(char *) * (n_strs + 1));
	if (!out)
		return (NULL);
	if (n_strs > 0)
		get_strs(str, charset, out);
	out[n_strs] = 0;
	return (out);
}
