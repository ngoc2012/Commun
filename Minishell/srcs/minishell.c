/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 23:14:52 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/05 11:16:09 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	zeros(t_m *m)
{
	m->args = 0;
	m->args_list = 0;
	m->ss = 0;
	m->argc = 0;
	m->heredoc = 0;
	m->heredocf = 0;
	m->hd_keys = 0;
}

void	init(t_m *m)
{
	zeros(m);
	m->process_level = 0;
	m->has_child = 0;
	m->syntax_error = 0;
	m->n_wildcards = 0;
	m->n_pipes = 1;
	m->exit_code = 0;
	m->s = 0;
	m->infix = 0;
	m->coms = 0;
	m->fin = 0;
	m->fin0 = 0;
	m->fout = 1;
	m->fout0 = 1;
	getcwd(m->cwd, sizeof(m->cwd));
	m->ffn = 0;
	m->ffn = strjoinm(m->ffn, m->cwd, 0, ft_strlen(m->cwd));
	m->ffn = strjoinm(m->ffn, "/minishell", ft_strlen(m->ffn), 10);
}

void	free_m_arg(t_m *m)
{
	if (m->args_list)
		ft_lstclear(&m->args_list, free);
	if (m->ss)
		free_array_str(&m->ss, 0);
	if (m->heredoc)
		free(m->heredoc);
	if (m->heredocf)
		free(m->heredocf);
	zeros(m);
}

void	free_files(t_m *m)
{
	if (m->fin && m->fin != -1)
		close(m->fin);
	if (m->fin0)
	{
		dup2(m->fin0, STDIN_FILENO);
		close(m->fin0);
	}
	if (m->fout > 1)
		close(m->fout);
	if (m->fout0 > 1)
	{
		dup2(m->fout0, STDOUT_FILENO);
		close(m->fout0);
	}
	m->fin = 0;
	m->fin0 = 0;
	m->fout = 1;
	m->fout0 = 1;
}

void	free_m(t_m *m, int free_env)
{
	free_m_arg(m);
	if (m->s)
		rl_free(m->s);
	m->s = 0;
	if (m->infix)
		ft_lstclear(&m->infix, free);
	m->infix = 0;
	if (m->coms)
		free_array_str(&m->coms, 0);
	m->coms = 0;
	free_files(m);
	if (free_env)
	{
		if (m->ffn)
			free(m->ffn);
		m->ffn = 0;
		if (m->env)
			free_array_str(&m->env, 0);
	}
}
