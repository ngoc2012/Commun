/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/17 17:30:58 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	loop(char *s, char charset, t_c *c, char ***out)
{
	char	d;
	char	**out0;

	while (s[c->i] && charset != s[c->i])
	{
		if (ft_strchr("\"\'", s[c->i]))
		{
			d = s[c->i++];
			while (s[c->i] && s[c->i] != d)
				c->i++;
		}
		if (s[c->i])
			c->i++;
	}
	if (s[c->i] == charset)
	{
		out0 = astr_addback(*out, ft_strndup(&s[c->i0], c->i - c->i0));
		if (!out0)
			return (free_array_str(out, 0));
		*out = out0;
		c->i++;
		c->i0 = c->i;
	}
	return (1);
}

char	**ft_split_quote(char *s, char charset)
{
	t_c		c;
	char	**out;
	char	**out0;

	c.i = 0;
	c.i0 = 0;
	out = 0;
	while (s[c.i])
	{
		while (s[c.i] && ft_strchr(" 	", s[c.i]))
			c.i++;
		c.i0 = c.i;
		if (!loop(s, charset, &c, &out))
			return (0);
	}
	out0 = astr_addback(out, ft_strndup(&s[c.i0], c.i - c.i0));
	if (!out0)
	{
		free_array_str(&out, 0);
		return (0);
	}
	out = out0;
	return (out);
}
