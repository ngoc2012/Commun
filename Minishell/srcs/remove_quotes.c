/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/02 08:35:28 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quotes_omit(char *s, int len, t_m *m, t_c *c)
{
	char	d;

	if (c->i > c->i0)
		c->o = strjoinm(c->o, &s[c->i0], ft_strlen(c->o), c->i - c->i0);
	d = s[c->i++];
	c->i0 = c->i;
	while (s[c->i] && c->i < len && s[c->i] != d)
	{
		if (s[c->i] == '\\' && s[c->i + 1])
		{
			c->o = strjoinm(c->o, &s[c->i0], ft_strlen(c->o), c->i - c->i0);
			c->i++;
			c->i0 = c->i;
		}
		c->i++;
	}
	if (s[c->i] == d)
	{
		if (c->i > c->i0)
			c->o = strjoinm(c->o, &s[c->i0], ft_strlen(c->o), c->i - c->i0);
	}
	else
		return (0);
	c->i++;
	c->i0 = c->i;
}

//printf(" after remove quotes| %s |\n", o);
//printf("before remove quotes|%s|\n", s);
char	*remove_quotes(char *s, int len, t_m *m)
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
			quotes_omit(s, len, m, &c);
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
