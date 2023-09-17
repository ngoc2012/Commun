/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/17 08:11:37 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

static void	get_exit_code(int exit_code, int is_last, int *quit)
{
	if (exit_code == 13)
		exit_code = 0;
	if (exit_code == 2 && !*quit)
	{
		*quit = 1;
		ft_putchar_fd('\n', 1);
	}
	if (exit_code == 131 && is_last)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	if (is_last)
	{
		g_exit_code = exit_code;
		convert_exit_code();
	}
}

static int	end_pipe(t_m *m, int last_pid)
{
	int	exit_code;
	int	pid;
	int	quit;

	exit_code = 0;
	quit = 0;
	signal(SIGINT, SIG_IGN);
	while (m->forks)
	{
		pid = wait(&exit_code);
		get_exit_code(exit_code, pid == last_pid, &quit);
		m->forks--;
	}
	signal(SIGINT, main_signal_handler);
	if (m->n_pipes > 1)
		close_pipe(m->pipefd0);
	if (m->n_pipes > 2)
		close_pipe(m->pipefd1);
	free_array_str(&m->coms, 1);
	free_files(m);
	free_m_arg(m);
	free_heredoc(m);
	if (!m->args && g_exit_code == 2)
		return (0);
	return (1);
}

static int	arg_pipe(t_m *m, int i, int *pid)
{
	if (!split_args(m->coms[i], m))
	{
		if (g_exit_code == 2 || g_exit_code == 130)
		{
			if (m->n_pipes > 1)
				close_pipe(m->pipefd0);
			if (m->n_pipes > 2)
				close_pipe(m->pipefd1);
		}
		free_files(m);
		free_m_arg(m);
		free_heredoc(m);
		return (0);
	}
	if (m->args && *m->args)
	{
		if (builtins(m, i))
			*pid = -1;
		else
			*pid = process(m, i);
	}
	free_files(m);
	free_m_arg(m);
	free_heredoc(m);
	return (1);
}

static int	check_syntaxe(char *s, t_m *m)
{
	t_list	*cur;

	cur = get_args_list0(s);
	if (!cur)
		return (0);
	while (cur)
	{
		if ((!ft_strncmp(">", (char *)cur->content, 2)
				|| !ft_strncmp("<", (char *)cur->content, 2)
				|| !ft_strncmp(">>", (char *)cur->content, 3)
				|| !ft_strncmp("<<", (char *)cur->content, 3)) &&
				cur->next &&
		{
			if (cur->next)
			{
				ft_putstr_fd("syntax error near unexpected token ", 2);
				ft_putstr_fd(, 2);
			}
		}
		cur = cur->next;
	}
	return (0);
}

/*
Execute a command with or without pipe.
A command is a string between between || ; and &&.
*/
int	pipes(char *s, t_m *m)
{
	int	i;
	int	pid;

	m->coms = ft_split_quote(s, '|');
	if (!m->coms)
		return (return_error(m, "syntaxe error", 2, 0));
	m->n_pipes = -1;
	while (m->coms[++m->n_pipes])
		if (m->n_pipes && !ft_strlen(m->coms[m->n_pipes]))
			return (return_error(m, "syntaxe error", 2, 0));
	m->syntaxe_error = check_syntaxe(s, m);
	if (m->n_pipes > 1)
		pipe(m->pipefd0);
	if (m->n_pipes > 2)
		pipe(m->pipefd1);
	pid = 0;
	i = -1;
	while (++i < m->n_pipes)
	{
		m->args = 0;
		m->argc = 0;
		if (!arg_pipe(m, i, &pid) && (g_exit_code == 2 || g_exit_code == 130))
			break ;
	}
	return (end_pipe(m, pid));
}
