/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/17 08:53:34 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_args(char *s, t_c *c)
{
	if (s[c->i] == c->d)
	{
		if (c->d == '>')
			ft_lstadd_back(&c->args, ft_lstnew(ft_strdup(">>")));
		else
			ft_lstadd_back(&c->args, ft_lstnew(ft_strdup("<<")));
		c->i++;
	}
	else
	{
		if (c->d == '>')
			ft_lstadd_back(&c->args, ft_lstnew(ft_strdup(">")));
		else
			ft_lstadd_back(&c->args, ft_lstnew(ft_strdup("<")));
	}
	while (ft_strchr(" 	", s[c->i]))
		c->i++;
	if (!s[c->i] || ft_strchr("|<>", s[c->i]))
	{
		c->err = 1;
		return (0);
	}
	c->i0 = c->i;
	return (1);
}

static void	end(char *s, t_c *c)
{
	while (c->i && s[c->i - 1] == ' ')
		c->i--;
	if (c->i > c->i0)
	{
		ft_lstadd_back(&c->args,
			ft_lstnew(strjoinm(0, &s[c->i0], 0, c->i - c->i0)));
	}
}

static void	wild_space(char *s, t_c *c)
{
	if (ft_strchr(" 	", s[c->i]))
	{
		if (c->i > c->i0)
		{
			if (c->i > c->i0)
				ft_lstadd_back(&c->args,
					ft_lstnew(strjoinm(0, &s[c->i0], 0, c->i - c->i0)));
		}
		while (ft_strchr(" 	", s[++c->i]))
			;
		c->i0 = c->i;
	}
}

static int	loop(char *s, t_c *c)
{
	if (ft_strchr("       ", s[c->i]))
		wild_space(s, c);
	else if (ft_strchr("<>", s[c->i]))
	{
		c->d = s[c->i];
		if (c->i > c->i0)
			ft_lstadd_back(&c->args,
				ft_lstnew(strjoinm(0, &s[c->i0], 0, c->i - c->i0)));
		c->i++;
		return (redir_args(s, c));
	}
	else if (ft_strchr("\"'", s[c->i]))
	{
		c->d = s[c->i];
		while (s[++c->i] && s[c->i] != c->d)
			;
		if (!s[c->i])
			c->err = 1;
		c->i++;
	}
	else
		c->i++;
	return (1);
}

t_list	*get_args_list(char *s)
{
	t_c	c;

	c.args = 0;
	c.d = ' ';
	c.i0 = 0;
	c.i = 0;
	c.err = 0;
	while (s[c.i] && ft_strchr(" 	\n", s[c.i]))
		c.i++;
	while (s[c.i])
	{
		if (!loop(s, &c) && c.err)
		{
			ft_lstclear(&c.args, free);
			return (0);
		}
	}
	end(s, &c);
	return (c.args);
}
