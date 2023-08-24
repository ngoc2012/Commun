/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/24 01:41:03 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_process_level;

// Child process
static void	write2heredocf(t_m *m, t_list **args)
{
	char	*s0;

	s0 = remove_quotes((char *)(*args)->content, ft_strlen((char *)(*args)->content), m);
	while (1)
	{
		char	*com;
		com = readline("> ");
		if (!ft_strncmp(com, s0, ft_strlen(s0) + 1))
			break ;
		m->heredoc = strjoinm(m->heredoc, com, ft_strlen(m->heredoc), ft_strlen(com));
		m->heredoc = strjoinm(m->heredoc, "\n", ft_strlen(m->heredoc), 1);
	}
	if (s0)
		free(s0);
	int heredocf;
	heredocf = open(m->heredocf, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	write(heredocf, m->heredoc, ft_strlen(m->heredoc));
	//free(m->heredoc);
	//m->heredoc = 0;
	//close(heredocf);
	free_m(m);
	exit(EXIT_SUCCESS);
}

static void	parent_process(t_m *m, t_list **args, int pid)
{
	g_process_level++;
	m->has_child = 1;
	waitpid(pid, &m->exit_code, 0);
	g_process_level = 0;
	m->has_child = 0;
	m->fin = open(m->heredocf, O_RDONLY);
	if (m->fin == -1)
		exit_error(m, "open", 1);
	m->fin0 = dup(STDIN_FILENO);
	if (dup2(m->fin, STDIN_FILENO) == -1)
		exit_error(m, "dup2", 1);
	close(m->fin);
	free((*args)->content);
	(*args)->content = 0;
}

int	heredoc(t_m *m, t_list **args)
{
	int	i;
	int	pid;

	(*args) = (*args)->next;
	if (!(*args) || ft_strchr("<>|", ((char *)(*args)->content)[0]))
		return (return_error(m, "syntaxe error", 2, 0));
	if (m->heredoc)
		free(m->heredoc);
	m->heredoc = 0;
	i = 0;
	m->heredocf = ft_itoa(i);
	while (access(m->heredocf, F_OK) != -1 && i < 100)
	{
		free(m->heredocf);
		m->heredocf = ft_itoa(++i);
	}
	pid = fork();
	if (pid == -1)
		exit_error(m, "fork", 1);
	else if (!pid)
		write2heredocf(m, args);
	else
		parent_process(m, args, pid);
	return (1);
}
