/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 23:14:52 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/24 10:58:11 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	zeros(t_m *m)
{
	m->exit_code = 0;
	m->syntax_error = 0;
	m->n_wildcards = 0;
	m->args = 0;
	m->argsL = 0;
	m->ss = 0;
	m->argc = 0;
	m->has_child = 0;
	m->fout = 1;
	m->fin = 0;
	m->fin0 = 0;
	m->heredoc = 0;
	m->heredocf = 0;
}

void	init(t_m *m)
{
	zeros(m);
	m->s = 0;
	m->infix = 0;
	m->coms = 0;
	getcwd(m->cwd, sizeof(m->cwd));
	m->ffn = 0;
	m->ffn = strjoinm(m->ffn, m->cwd, 0, ft_strlen(m->cwd));
	m->ffn = strjoinm(m->ffn, "/minishell", ft_strlen(m->ffn), 10);
}

void	free_m_arg(t_m *m)
{
	if (m->argsL)
		ft_lstclear(&m->argsL, free);
	if (m->ss)
		free_array_str(&m->ss, 0);
	if (m->heredoc)
		free(m->heredoc);
	if (m->heredocf)
		free(m->heredocf);
	if (m->fin0)
		close(m->fin0);
	zeros(m);
}

void	free_m(t_m *m)
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
	if (m->ffn)
		free(m->ffn);
	if (m->env)
		free_array_str(&m->env, 0);
}
