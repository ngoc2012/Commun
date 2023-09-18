/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/18 11:35:35 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

static int	read_lines(char *fn, char *end)
{
	int		heredocf;
	char	*com;
	char	*s;

	while (1)
	{
		com = readline("> ");
		if (!com)
			return (2);
		if (!ft_strncmp(com, end, ft_strlen(end) + 1))
			break ;
		heredocf = open(fn, O_CREAT | O_WRONLY | O_APPEND, 0664);
		s = strjoinm(0, com, 0, -1);
		s = strjoinm(s, "\n", ft_strlen(s), 1);
		write(heredocf, s, ft_strlen(s));
		free(s);
		close(heredocf);
	}
	return (0);
}

// Child process
static int	write2heredocf(t_m *m, t_list *cur)
{
	char	end[4096];
	char	*s0;
	char	*s;
	int		heredocf;

	signal_heredoc();
	s0 = remove_dollar((char *)cur->content);
	s = remove_quotes(s0, ft_strlen(s0), m);
	free(s0);
	ft_strlcpy(end, s, ft_strlen(s) + 1);
	free(s);
	if (m->n_pipes > 1)
		close_pipe(m->pipefd0);
	if (m->n_pipes > 2)
		close_pipe(m->pipefd1);
	free_m(m, 1);
	heredocf = open(m->heredocf, O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (heredocf == -1)
	{
		perror("open");
		exit(1);
	}
	write(heredocf, "", 0);
	close(heredocf);
	exit(read_lines(m->heredocf, end));
}

static int	parent_process(t_m *m, t_list *cur)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		return_error(m, "fork", 1, 1);
	else if (!pid)
		write2heredocf(m, cur);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &g_exit_code, 0);
		signal(SIGINT, main_signal_handler);
		convert_exit_code();
		if (g_exit_code)
		{
			if (g_exit_code == 2)
				g_exit_code = 0;
			return (free_heredoc(m));
		}
	}
	return (1);
}

int	check_heredoc(t_m *m, t_list *cur, t_list **here)
{
	*here = 0;
	while (cur)
	{
		if (!ft_strncmp("<<", (char *)cur->content, 3))
		{
			cur = cur->next;
			*here = cur;
			free_heredoc(m);
			fn_heredoc(m);
			if (!parent_process(m, cur) && g_exit_code)
				return (0);
			else if (!convert_heredoc(m))
				return (0);
		}
		if (cur)
			cur = cur->next;
	}
	return (1);
}

int	heredoc(t_m *m)
{
	if (m->fin)
	{
		close(m->fin);
		m->fin = 0;
		if (dup2(m->fin0, STDIN_FILENO) == -1)
			return (redir_error("dup2", 1, 1));
		close(m->fin0);
	}
	m->fin = open(m->heredocf, O_RDONLY);
	if (m->fin == -1)
		return (0);
	m->fin0 = dup(STDIN_FILENO);
	if (dup2(m->fin, STDIN_FILENO) == -1)
		return_error(m, "dup2", 1, 1);
	close(m->fin);
	return (1);
}
