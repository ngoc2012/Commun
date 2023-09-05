/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/05 11:42:40 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_lines(t_m *m)
{
	char	*com;
	char	*s;

	while (1)
	{
		com = readline("> ");
		if (!ft_strncmp(com, m->s, ft_strlen(m->s) + 1))
			break ;
		s = str_env(com, ft_strlen(com), m);
		m->heredoc = strjoinm(m->heredoc, s, -1, -1);
		free(s);
		m->heredoc = strjoinm(m->heredoc, "\n", ft_strlen(m->heredoc), 1);
	}
}

// Child process
static int	write2heredocf(t_m *m, t_list **cur)
{
	int		heredocf;

	signal_heredoc();
	if (m->s)
		rl_free(m->s);
	m->s = remove_quotes((char *)(*cur)->content,
			ft_strlen((char *)(*cur)->content));
	read_lines(m);
	if (m->n_pipes > 1)
		close_pipe(m->pipefd0);
	if (m->n_pipes > 2)
		close_pipe(m->pipefd1);
	heredocf = open(m->heredocf, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (heredocf == -1)
		exit_error(m, "open", 1);
	write(heredocf, m->heredoc, ft_strlen(m->heredoc));
	close(heredocf);
	exit_error(m, 0, EXIT_SUCCESS);
	return (1);
}

static int	parent_process(t_m *m, int pid, t_list **cur)
{
	m->process_level++;
	m->has_child = 1;
	waitpid(pid, &m->exit_code, 0);
	(*cur) = (*cur)->next;
	m->process_level = 0;
	m->has_child = 0;
	m->fin = open(m->heredocf, O_RDONLY);
	if (m->fin == -1)
		return (0);
	m->fin0 = dup(STDIN_FILENO);
	if (dup2(m->fin, STDIN_FILENO) == -1)
		return_error(m, "dup2", 1, 1);
	close(m->fin);
	free(m->heredoc);
	m->heredoc = 0;
	free(m->heredocf);
	m->heredocf = 0;
	return (1);
}

int	heredoc(t_m *m, t_list **cur)
{
	int	i;
	int	pid;

	(*cur) = (*cur)->next;
	if (!(*cur) || ft_strchr("<>|", ((char *)(*cur)->content)[0]))
		return (return_error(m, "syntaxe error", 2, 0));
	if (m->fin0)
	{
		dup2(m->fin0, STDIN_FILENO);
		close(m->fin0);
	}
	i = 0;
	m->heredocf = ft_itoa(i);
	while (access(m->heredocf, F_OK) != -1 && i < 100)
	{
		free(m->heredocf);
		m->heredocf = ft_itoa(++i);
	}
	pid = fork();
	if (pid == -1)
		return_error(m, "fork", 1, 1);
	else if (!pid)
		return (write2heredocf(m, cur));
	return (parent_process(m, pid, cur));
}
