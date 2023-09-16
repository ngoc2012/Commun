/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/16 15:45:15 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_quote(char *s, t_c *c)
{
	char	d;

	if (s[c->i] == '\"')
	{
		if (c->in_double_quotes)
			c->in_double_quotes = 0;
		else
			c->in_double_quotes = 1;
	}
	if (s[c->i] == '\'' && !c->in_double_quotes)
	{
		c->o = strjoinm(c->o, &s[c->i0], ft_strlen(c->o), c->i - c->i0);
		c->i0 = c->i;
		d = s[c->i++];
		while (s[c->i] && c->i < c->len && s[c->i] != d)
			c->i++;
		if (s[c->i] == d)
			c->o = strjoinm(c->o, &s[c->i0], ft_strlen(c->o), c->i - c->i0 + 1);
		c->i++;
		c->i0 = c->i;
		return (1);
	}
	return (0);
}

char	*str_env(char *s, int len, t_m *m, int first_arg)
{
	t_c	c;

	c.o = 0;
	c.i = 0;
	c.i0 = 0;
	c.in_double_quotes = 0;
	c.first_arg = first_arg;
	c.len = len;
	while (s[c.i] && c.i < len)
	{
		if (!c.in_double_quotes && ft_strchr(" 	", s[c.i]))
		{
			c.first_arg = 0;
		}
		if (remove_quote(s, &c))
			;
		else if (get_str_env(s, m, &c))
			;
		else
			c.i++;
	}
	if (!c.i)
		return (ft_strdup(""));
	c.o = strjoinm(c.o, &s[c.i0], ft_strlen(c.o), c.i - c.i0);
	return (c.o);
}

static void	convert_env(char *s, t_c *c, t_m *m)
{
	c->o = strjoinm(c->o, &s[c->i0], ft_strlen(c->o), c->i - c->i0);
	if (ft_isdigit(s[c->i + 1]))
		c->i += 2;
	else
		get_str_env3(s, m, c);
	c->i0 = c->i;
}

char	*str_env2(char *s, int len, t_m *m)
{
	t_c	c;

	c.o = 0;
	c.i = 0;
	c.i0 = 0;
	c.in_double_quotes = 0;
	c.first_arg = 1;
	c.len = len;
	while (s[c.i] && c.i < len)
	{
		if (s[c.i] == '$' && isenv(s[c.i + 1]))
			convert_env(s, &c, m);
		else
			c.i++;
	}
	if (!c.i)
		return (ft_strdup(""));
	c.o = strjoinm(c.o, &s[c.i0], ft_strlen(c.o), c.i - c.i0);
	return (c.o);
}
