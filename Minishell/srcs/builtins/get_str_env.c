/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_str_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/14 12:18:18 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_str_env3(char *s, t_m *m, t_c *c)
{
	char	*s1;
	char	*s0;

	c->i0 = ++c->i;
	while (s[c->i] && c->i < c->len && isenv(s[c->i]))
		c->i++;
	s0 = ft_strndup(&s[c->i0], c->i - c->i0);
	s1 = get_env(s0, m->env);
	while (s1 && *s1)
	{
		if (*s1 == '\"' && c->in_double_quotes)
			c->o = strjoinm(c->o, "\"\'\"\'\"", -1, -1);
		else if (*s1 == '\"' && !c->in_double_quotes)
			c->o = strjoinm(c->o, "\'\"\'", -1, -1);
		else if (*s1 == '\'' && !c->in_double_quotes)
			c->o = strjoinm(c->o, "\"\'\"", -1, -1);
		else
			c->o = strjoinm(c->o, s1, -1, 1);
		s1++;
	}
	free(s0);
	return (0);
}

static int	get_str_env0(char *s, t_m *m, t_c *c)
{
	if (s[c->i] == '$' && ft_strchr("\'\"", s[c->i + 1]) && !c->in_double_quotes)
	{
		c->o = strjoinm(c->o, &s[c->i0], ft_strlen(c->o), c->i - c->i0);
		c->i++;
		c->i0 = c->i;
		return (1);
	}
	if (s[c->i] == '$' && isenv(s[c->i + 1]))
	{
		c->o = strjoinm(c->o, &s[c->i0], ft_strlen(c->o), c->i - c->i0);
		if (ft_isdigit(s[c->i + 1]))
			c->i += 2;
		else
			get_str_env3(s, m, c);
		c->i0 = c->i;
		return (1);
	}
	return (0);
}

static int	get_str_env1(char *s, t_m *m, t_c *c)
{
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
	return (0);
}

int	get_str_env(char *s, t_m *m, t_c *c)
{
	if (get_str_env0(s, m, c))
		return (1);
	if (get_str_env1(s, m, c))
		return (1);
	return (0);
}
