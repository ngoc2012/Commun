/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priorities_operators.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 08:41:16 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/21 16:36:04 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parentheses(char *s, t_m *m, t_c *c)
{
	char	d;
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
	if ((d == '(' && s[c->i] && ft_strchr(")&|", s[c->i]))
		|| (d == ')' && s[c->i] && ft_strchr("(", s[c->i])))
		//|| (d == ')' && s[c->i] && !ft_strchr(")&|", s[c->i])))
		return (return_error(m, "syntaxe error 2", 2, 0));
	c->i0 = c->i;
	return (1);
}

static int	operators(char *s, t_m *m, t_c *c)
{
	int		i1;

	i1 = c->i;
	while (--i1 >= 0 && ft_strchr(" 	\n", s[i1]))
		;
	i1++;
	if (i1 > c->i0)
		ft_lstadd_back(&m->infix,
			ft_lstnew(ft_strndup(&s[c->i0], i1 - c->i0)));
	ft_lstadd_back(&m->infix, ft_lstnew(ft_strndup(&s[c->i], 2)));
	c->i++;
	while (s[++c->i] && ft_strchr(" 	\n", s[c->i]))
		;
	if (!s[c->i] || ft_strchr("&|", s[c->i]))
		return (return_error(m, "syntaxe error 1", 2, 0));
	c->i0 = c->i;
	return (1);
}

static int	loop(char *s, t_m *m, t_c *c)
{
	char	d;

	if (ft_strchr("()", s[c->i]))
	{
		if (!parentheses(s, m, c))
			return (0);
	}
	else if (!ft_strncmp("&&", &s[c->i], 2) || !ft_strncmp("||", &s[c->i], 2))
	{
		if (!operators(s, m, c))
			return (0);
	}
	else if (ft_strchr("\"'", s[c->i]))
	{
		d = s[c->i];
		while (s[++c->i] && s[c->i] != d)
			;
		if (!s[c->i])
			return (return_error(m, "syntaxe error 5", 2, 0));
		c->i++;
	}
	else
		c->i++;
	return (1);
}

// Check syntax error: ( command (
// Check syntax error: ) command )
int	priorities_operators(char *s, t_m *m)
{
	t_c	c;

	printf("here\n");
	while (*s && ft_strchr(" 	\n", *s))
		s++;
	if (ft_strchr(";&|", *s))
		return (return_error(m, "syntaxe error 4", 2, 0));
	c.n_o = 0;
	c.n_c = 0;
	c.i0 = 0;
	c.i = 0;
	while (s[c.i])
	{
		if (!loop(s, m, &c))
			return (0);
	}
	if (c.i > c.i0)
		ft_lstadd_back(&m->infix, ft_lstnew(ft_strndup(&s[c.i0], c.i - c.i0)));
	if (c.n_o != c.n_c)
		return (return_error(m, "syntaxe error 3", 2, 0));
	return (1);
}
