/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/31 09:54:59 by ngoc             ###   ########.fr       */
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

static int	check(t_m *m, t_list **cur)
{
	if (!ft_strncmp("<<", (char *)(*cur)->content, 3))
		return (heredoc(m, cur));
	else if (!ft_strncmp(">", (char *)(*cur)->content, 2)
		|| !ft_strncmp(">>", (char *)(*cur)->content, 3))
		return (redir_out(m, cur));
	else if (!ft_strncmp("<", (char *)(*cur)->content, 2))
		return (redir_in(m, cur));
	else
	{
		m->args = astr_addback(m->args,
				remove_quotes((char *)(*cur)->content,
					ft_strlen((char *)(*cur)->content), m));
		m->ss = m->args;
		m->argc++;
		*cur = (*cur)->next;
	}
	return (1);
}

int	split_args(char *s, t_m *m)
{
	t_list	*cur;

	cur = get_args_list0(s, m);
	if (!cur)
		return (0);
	m->args = 0;
	m->argc = 0;
	m->args_list = cur;
	while (cur)
		if (!check(m, &cur))
			return (0);
	return (1);
}
