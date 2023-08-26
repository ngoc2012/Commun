/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/26 11:30:02 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_args(char *s, t_m *m, t_c *c)
{
	c->d = s[c->i];
	if (c->i > c->i0)
		ft_lstadd_back(&c->args,
			ft_lstnew(strjoinm(0, &s[c->i0], 0, c->i - c->i0)));
	c->i++;
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
	c->i0 = c->i;
}

static int	quotes(char *s, t_m *m, t_c *c)
{
	c->d = s[c->i];
	while (s[++c->i] && s[c->i] != c->d)
		;
	if (!s[c->i])
	{
		ft_lstclear(&c->args, free);
		return (0);
	}
	c->i++;
	return (1);
}

static void	end(char *s, t_m *m, t_c *c, int *wild)
{
	while (c->i && s[c->i - 1] == ' ')
		c->i--;
	if (c->i > c->i0)
	{
		if (*wild)
			wildcards(ft_strndup(&s[c->i0], c->i - c->i0), &c->args, m);
		else
			ft_lstadd_back(&c->args,
				ft_lstnew(strjoinm(0, &s[c->i0], 0, c->i - c->i0)));
	}
}

static void	wild_space(char *s, t_m *m, t_c *c, int *wild)
{
	if (s[c->i] == '*')
	{
		*wild = 1;
		if (ft_lstlast(c->args) && !ft_strncmp("<<",
				(char *)(ft_lstlast(c->args))->content, 3))
			*wild = 0;
		c->i++;
	}
	else if (ft_strchr(" 	", s[c->i]))
	{
		if (c->i > c->i0)
		{
			if (*wild)
				wildcards(ft_strndup(&s[c->i0], c->i - c->i0), &c->args, m);
			else if (c->i > c->i0)
				ft_lstadd_back(&c->args,
					ft_lstnew(strjoinm(0, &s[c->i0], 0, c->i - c->i0)));
		}
		*wild = 0;
		while (ft_strchr(" 	", s[++c->i]))
			;
		c->i0 = c->i;
	}
}

t_list	*get_args_list(char *s, t_m *m)
{
	t_c		c;
	char	*a;
	int		wild;

	wild = 0;
	c.args = 0;
	c.d = ' ';
	c.i0 = 0;
	c.i = 0;
	while (s[c.i])
	{
		if (s[c.i] == '*' || ft_strchr(" 	", s[c.i]))
			wild_space(s, m, &c, &wild);
		else if (ft_strchr("<>", s[c.i]))
			redir_args(s, m, &c);
		else if (ft_strchr("\"'", s[c.i]))
		{
			if (!quotes(s, m, &c))
				return (0);
		}
		else
			c.i++;
	}
	end(s, m, &c, &wild);
	return (c.args);
}
