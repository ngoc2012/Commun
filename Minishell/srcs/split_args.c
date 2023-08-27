/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/27 21:09:37 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*get_args_list0(char *s, t_m *m)
{
	char	*s_env;
	t_list	*args_list;

	while (*s && ft_strchr(" \n", *s))
		s++;
	s_env = str_env(s, ft_strlen(s), m);
	if (!*s_env)
	{
		m->exit_code = 0;
		free(s_env);
		return (0);
	}
	args_list = get_args_list(s_env, m);
	free(s_env);
	if (!args_list)
		m->exit_code = 2;
	return (args_list);
}

static int	check(t_m *m, t_list *args_list)
{
	if (!ft_strncmp("<<", (char *)args_list->content, 3))
	{
		if (!heredoc(m, &args_list))
			return (0);
	}
	else if (!ft_strncmp(">", (char *)args_list->content, 2)
		|| !ft_strncmp(">>", (char *)args_list->content, 3))
	{
		if (!redir_out(m, &args_list))
			return (0);
	}
	else if (!ft_strncmp("<", (char *)args_list->content, 2))
	{
		if (!redir_in(m, &args_list))
			return (0);
	}
	else
	{
		m->args = astr_addback(m->args,
				remove_quotes((char *)args_list->content,
					ft_strlen((char *)args_list->content), m));
		m->ss = m->args;
		m->argc++;
	}
	return (1);
}

int	split_args(char *s, t_m *m)
{
	t_list	*args_list;

	args_list = get_args_list0(s, m);
	if (!args_list)
		return (0);
	m->args = 0;
	m->argc = 0;
	m->args_list = args_list;
	while (args_list)
	{
		if (args_list->content)
			if (!check(m, args_list))
				return (0);
		args_list = args_list->next;
	}
	if (m->heredoc)
		write(0, m->heredoc, ft_strlen(m->heredoc));
	return (1);
}
