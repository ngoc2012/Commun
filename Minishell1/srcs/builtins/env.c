/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/17 17:13:29 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_quote(char *s, t_m *m, t_c *c)
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

int	get_str_env(char *s, t_m *m, t_c *c)
{
	char	*s1;
	char	*s0;

	if (s[c->i] == '$' && isenv(s[c->i + 1]))
	{
		c->o = strjoinm(c->o, &s[c->i0], ft_strlen(c->o), c->i - c->i0);
		if (ft_isdigit(s[c->i + 1]))
			c->i += 2;
		else
		{
			c->i0 = ++c->i;
			while (s[c->i] && c->i < c->len && isenv(s[c->i]))
				c->i++;
			s0 = ft_strndup(&s[c->i0], c->i - c->i0);
			s1 = get_env(s0, m->env);
			c->o = strjoinm(c->o, s1, ft_strlen(c->o), ft_strlen(s1));
			free(s0);
		}
		c->i0 = c->i;
		return (1);
	}
	return (0);
}

int	get_str_env_other(char *s, t_m *m, t_c *c)
{
	char	*s1;
	char	*s0;

	if (s[c->i] == '$' && s[c->i + 1] == '?')
	{
		c->o = strjoinm(c->o, &s[c->i0], ft_strlen(c->o), c->i - c->i0);
		s0 = ft_itoa(m->exit_code);
		c->o = strjoinm(c->o, s0, ft_strlen(c->o), ft_strlen(s0));
		free(s0);
		c->i += 2;
		c->i0 = c->i;
		return (1);
	}
	else if (s[c->i] == '\\' && s[c->i + 1]
		&& !ft_strchr(" 	\n", s[c->i + 1]))
	{
		c->o = strjoinm(c->o, &s[c->i0], ft_strlen(c->o), c->i - c->i0);
		c->i++;
		c->o = strjoinm(c->o, &s[c->i], ft_strlen(c->o), 1);
		c->i++;
		c->i0 = c->i;
		return (1);
	}
	return (0);
}

char	*str_env(char *s, int len, t_m *m)
{
	t_c	c;

	c.o = 0;
	c.i = 0;
	c.i0 = 0;
	c.in_double_quotes = 0;
	c.len = len;
	while (s[c.i] && c.i < len)
	{
		if (remove_quote(s, m, &c))
			;
		else if (get_str_env(s, m, &c))
			;
		else if (get_str_env_other(s, m, &c))
			;
		else
			c.i++;
	}
	if (!c.i)
		return (ft_strdup(""));
	c.o = strjoinm(c.o, &s[c.i0], ft_strlen(c.o), c.i - c.i0);
	return (c.o);
}
