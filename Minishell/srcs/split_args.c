/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/24 09:54:36 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*get_args_list(char *s, t_m *m)
{
	char	*s_env;
	t_list	*args;

	while (*s && ft_strchr(" \n", *s))
		s++;
	s_env = str_env(s, ft_strlen(s), m);
	if (!*s_env)
	{
		m->exit_code = 0;
		free(s_env);
		return (0);
	}
	args = args_list(s_env, m);
	free(s_env);
	if (!args)
		m->exit_code = 2;
	return (args);
}

static int	check(t_m *m, t_list *args)
{
	if (!ft_strncmp("<<", (char *)args->content, 3))
	{
		if (!heredoc(m, &args))
			return (0);
	}
	else if (!ft_strncmp(">", (char *)args->content, 2)
		|| !ft_strncmp(">>", (char *)args->content, 3))
	{
		if (!redir_out(m, &args))
			return (0);
	}
	else if (!ft_strncmp("<", (char *)args->content, 2))
	{
		if (!redir_in(m, &args))
			return (0);
	}
	else
	{
		m->args = astr_addback(m->args, remove_quotes((char *)args->content,
					ft_strlen((char *)args->content), m));
		m->argc++;
	}
	return (1);
}

int	split_args(char *s, t_m *m)
{
	t_list	*args;

	args = get_args_list(s, m);
	if (!args)
		return (0);
	m->args = 0;
	m->argc = 0;
	m->argsL = args;
	while (args)
	{
		if (args->content)
			if (!check(m, args))
				return (0);
		args = args->next;
	}
	m->ss = m->args;
	if (m->heredoc)
		write(0, m->heredoc, ft_strlen(m->heredoc));
	return (1);
}
