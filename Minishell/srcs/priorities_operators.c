/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priorities_operators.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 08:41:16 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/24 18:44:49 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parantheses(char *s, t_m *m, t_c *c)
{
	char	d;
	int		i;
	int		j;

	d = s[c->i];
	if (s[c->i] == '(')
		(c->n_o)++;
	else
		(c->n_c)++;
	j = c->i;
	while (--j >= 0 && ft_strchr(" 	\n", s[j]))
		;
	j++;
	if (j > c->i0)
		ft_lstadd_back(&m->infix,
			ft_lstnew(ft_strndup(&s[c->i0], j - c->i0)));
	ft_lstadd_back(&m->infix, ft_lstnew(ft_strndup(&s[c->i], 1)));
	while (s[++(c->i)] && ft_strchr(" 	\n", s[c->i]))
		;
	if ((d == '(' && s[c->i] == ')') || (d == ')' && s[c->i]
			&& !ft_strchr(");&|", s[c->i])))
		return (return_error(m, "syntaxe error", 2, 0));
	c->i0 = c->i;
}

static int	operators(char *s, t_m *m, t_c *c)
{
	int		i1;

	i1 = c->i;
	while (--i1 >= 0 && ft_strchr(" 	\n", s[i1]))
		;
	i1++;
	if (i1 > c->i0)
		ft_lstadd_back(&m->infix, ft_lstnew(ft_strndup(&s[c->i0], i1 - c->i0)));
	ft_lstadd_back(&m->infix, ft_lstnew(ft_strndup(&s[c->i], 1)));
	c->i++;
	while (s[++c->i] && ft_strchr(" 	\n", s[c->i]))
		;
	if (!s[c->i] || ft_strchr("&|", s[c->i]))
		return (return_error(m, "syntaxe error", 2, 0));
	c->i0 = c->i;
}

static int	end(char *s, t_m *m, t_c *c)
{
	int		i1;

	i1 = c->i;
	while (--i1 >= 0 && ft_strchr(" 	\n", s[i1]))
		;
	i1++;
	if (i1 <= c->i0)
		return (return_error(m, "syntaxe error", 2, 0));
	ft_lstadd_back(&m->infix, ft_lstnew(ft_strndup(&s[c->i0], i1 - c->i0)));
	ft_lstadd_back(&m->infix, ft_lstnew(ft_strdup(";")));
	while (s[++c->i] && ft_strchr(" \n", s[c->i]))
		;
	if (s[c->i] && ft_strchr(";&|", s[c->i]))
		return (return_error(m, "syntaxe error", 2, 0));
	c->i0 = c->i;
}

static int	loop(char *s, t_m *m, t_c *c)
{
	char	d;

	while (s[c->i])
	{
		if (ft_strchr("()", s[c->i]))
			parantheses(s, m, c);
		else if (!ft_strncmp("&&", &s[c->i], 2)
			|| !ft_strncmp("||", &s[c->i], 2))
			operators(s, m, c);
		else if (ft_strchr("\n;", s[c->i]))
			end(s, m, c);
		else if (ft_strchr("\"'", s[c->i]))
		{
			d = s[c->i];
			while (s[++c->i] && s[c->i] != d)
				;
			if (!s[c->i])
				return (return_error(m, "syntaxe error", 2, 0));
			c->i++;
		}
		else
			c->i++;
	}
	return (1);
}

// Check syntax error: ( command (
// Check syntax error: ) command )
int	priorities_operators(char *s, t_m *m)
{
	int	i1;
	t_c	c;

	while (*s && ft_strchr(" 	\n", *s))
		s++;
	if (ft_strchr(";&|", *s))
	{
		m->exit_code = 2;
		return (0);
	}
	c.n_o = 0;
	c.n_c = 0;
	c.i0 = 0;
	c.i = 0;
	if (!loop(s, m, &c))
		return (0);
	if (c.i > c.i0)
		ft_lstadd_back(&m->infix, ft_lstnew(ft_strndup(&s[c.i0], c.i - c.i0)));
	if (c.n_o != c.n_c)
		return (return_error(m, "syntaxe error", 2, 0));
	return (1);
}
