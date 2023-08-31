/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/31 16:25:39 by ngoc             ###   ########.fr       */
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
		if (g_m->n_pipes > 1)
			close_pipe(g_m->pipefd0);
		if (g_m->n_pipes > 2)
			close_pipe(g_m->pipefd1);
		free_m(g_m);
		exit(130);
	}
	else if (sig == SIGQUIT)
	{
		if (g_m->n_pipes > 1)
			close_pipe(g_m->pipefd0);
		if (g_m->n_pipes > 2)
			close_pipe(g_m->pipefd1);
		free_m(g_m);
		exit(130);
	}
}

void	signal_heredoc(void)
{
	struct sigaction	act;

	act.sa_flags = SA_RESTART | SA_SIGINFO;
	act.sa_sigaction = &signal_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
