/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/26 13:15:08 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

static char	*get_first_arg(t_m *m, char *s)
{
	t_list	*args_list;
	char	*s_env;
	char	*s0;

	s0 = 0;
	s_env = str_env(s, ft_strlen(s), m, 0);
	args_list = get_args_list_wild(s_env, m);
	free(s_env);
	if (!args_list || ft_lstsize(args_list) > 1)
	{
		ft_lstclear(&args_list, free);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		g_exit_code = 1;
		return (0);
	}
	s0 = (char *) args_list->content;
	s0 = remove_quotes(s0, ft_strlen(s0), m);
	ft_lstclear(&args_list, free);
	return (s0);
}

static void	add_arg(t_m *m, t_list **cur)
{
	char	*s_env;
	t_list	*args_list;
	t_list	*al;

	s_env = str_env((char *)(*cur)->content,
			ft_strlen((char *)(*cur)->content), m, !m->argc);
	args_list = get_args_list_wild(s_env, m);
	free(s_env);
	al = args_list;
	while (al)
	{
		m->args = astr_addback(m->args,
				remove_quotes((char *)al->content,
					ft_strlen((char *)al->content), m));
		m->argc++;
		al = al->next;
	}
	ft_lstclear(&args_list, free);
	m->ss = m->args;
	*cur = (*cur)->next;
}

static int	check_out(t_m *m, t_list **cur)
{
	char	*cur0;
	char	*cur1;

	cur0 = (char *)(*cur)->content;
	*cur = (*cur)->next;
	cur1 = (char *)(*cur)->content;
	if (*cur)
		*cur = (*cur)->next;
	if (!m->syntaxe_error)
		return (redir_out(m, get_first_arg(m, cur1),
				!ft_strncmp(">>", cur0, 3)));
	return (1);
}

static int	check_in(t_m *m, t_list **cur)
{
	char	*cur1;

	if (!ft_strncmp("<", (char *)(*cur)->content, 2))
	{
		*cur = (*cur)->next;
		cur1 = (char *)(*cur)->content;
		if (*cur)
			*cur = (*cur)->next;
		if (!m->syntaxe_error)
			return (redir_in(m, get_first_arg(m, cur1)));
	}
	else if (!ft_strncmp(">", (char *)(*cur)->content, 2)
		|| !ft_strncmp(">>", (char *)(*cur)->content, 3))
		return (check_out(m, cur));
	else if (!m->syntaxe_error)
		add_arg(m, cur);
	else
		*cur = (*cur)->next;
	return (1);
}

int	split_args(char *s, t_m *m)
{
	t_list	*cur;
	t_list	*here;

	cur = get_args_list(s);
	if (!cur)
		return (0);
	m->args_list = cur;
	if (!check_heredoc(m, cur, &here))
		return (0);
	while (cur)
	{
		if (!ft_strncmp("<<", (char *)(cur)->content, 3))
		{
			cur = cur->next;
			if (here && cur == here)
				if (!heredoc(m))
					return (0);
			cur = cur->next;
		}
		else if (!check_in(m, &cur))
			return (0);
	}
	printf("split_args m->fin = %d\n", m->fin);
	printf("split_args m->fout = %d\n", m->fout);
	return (1);
}
