/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 23:14:52 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/17 15:59:09 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_m *m)
{
	m->exit_code = 0;
	m->syntax_error = 0;
	m->n_wildcards = 0;
	m->s = 0;
	m->coms = 0;
	m->args = 0;
	m->argc = 0;
	m->has_child = 0;
	m->infix = 0;
	m->fout = 1;
	m->fin = 0;
	m->fin0 = 0;
	m->heredoc = 0;
	m->heredocf = 0;
	getcwd(m->cwd, sizeof(m->cwd));
	m->ffn = 0;
	m->ffn = strjoinm(m->ffn, m->cwd, 0, ft_strlen(m->cwd));
	m->ffn = strjoinm(m->ffn, "/minishell", ft_strlen(m->ffn), 10);
}

void	free_m(t_m *m)
{
	if (m->ffn)
		free(m->ffn);
	if (m->s)
		rl_free(m->s);
	if (m->env)
		free_array_str(&m->env, 0);
	if (m->args)
		free_array_str(&m->args, 0);
	if (m->coms)
		free_array_str(&m->coms, 0);
	if (m->heredocf)
		free(m->heredocf);
	if (m->fin0)
		close(m->fin0);
	if (m->infix)
		ft_lstclear(&m->infix, free);
}
