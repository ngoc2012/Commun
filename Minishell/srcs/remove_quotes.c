/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/12 20:45:11 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quotes_omit(char *s, int len, t_c *c)
{
	char	d;

	if (c->i > c->i0)
		c->o = strjoinm(c->o, &s[c->i0], ft_strlen(c->o), c->i - c->i0);
	d = s[c->i++];
	c->i0 = c->i;
	while (s[c->i] && c->i < len && s[c->i] != d)
		c->i++;
	if (s[c->i] != d)
		return ;
	if (c->i > c->i0)
		c->o = strjoinm(c->o, &s[c->i0], ft_strlen(c->o), c->i - c->i0);
	c->i++;
	c->i0 = c->i;
}

char	*remove_quotes(char *s, int len)
{
	t_c	c;

	c.o = 0;
	c.i = 0;
	if (s[0] == '~')
		c.o = strjoinm(c.o, get_home(), c.i++, -1);
	c.i0 = c.i;
	while (s[c.i] && c.i < len)
	{
		if (ft_strchr("\"'", s[c.i]))
			quotes_omit(s, len, &c);
		else
		{
			while (s[c.i] && c.i < len && !ft_strchr("\"'", s[c.i]))
				c.i++;
			if (c.i > c.i0)
				c.o = strjoinm(c.o, &s[c.i0], ft_strlen(c.o), c.i - c.i0);
			c.i0 = c.i;
		}
	}
	if (!c.o)
		return (ft_strdup(""));
	return (c.o);
}
