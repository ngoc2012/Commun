/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/27 21:09:17 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_m	*g_m;

static void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	if (sig == SIGINT)
	{
		free_m(g_m);
		exit(130);
	}
	else if (sig == SIGQUIT)
	{
		free_m(g_m);
		exit(130);
	}
}

static void	signal_heredoc(void)
{
	struct sigaction	act;

	act.sa_flags = SA_RESTART | SA_SIGINFO;
	act.sa_sigaction = &signal_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

// Child process
static void	write2heredocf(t_m *m, t_list **args)
{
	char	*com;
	int		heredocf;

	signal_heredoc();
	if (m->s)
		rl_free(m->s);
	m->s = remove_quotes((char *)(*args)->content,
			ft_strlen((char *)(*args)->content), m);
	while (1)
	{
		com = readline("> ");
		if (!ft_strncmp(com, m->s, ft_strlen(m->s) + 1))
			break ;
		m->heredoc = strjoinm(m->heredoc, com,
				ft_strlen(m->heredoc), ft_strlen(com));
		m->heredoc = strjoinm(m->heredoc, "\n", ft_strlen(m->heredoc), 1);
	}
	heredocf = open(m->heredocf, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (heredocf == -1)
		exit_error(m, "open", 1);
	write(heredocf, m->heredoc, ft_strlen(m->heredoc));
	close(heredocf);
	free_m(m);
	exit(EXIT_SUCCESS);
}

static int	parent_process(t_m *m, t_list **args, int pid)
{
	m->process_level++;
	m->has_child = 1;
	waitpid(pid, &m->exit_code, 0);
	m->process_level = 0;
	m->has_child = 0;
	m->fin = open(m->heredocf, O_RDONLY);
	if (m->fin == -1)
		return (0);
	m->fin0 = dup(STDIN_FILENO);
	if (dup2(m->fin, STDIN_FILENO) == -1)
		return_error(m, "dup2", 1, 1);
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
		return_error(m, "fork", 1, 1);
	else if (!pid)
		write2heredocf(m, args);
	else
		return (parent_process(m, args, pid));
	return (1);
}
