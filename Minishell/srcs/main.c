/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 09:51:49 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/14 11:56:55 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_forks;

static void	signal_handler(int sig)
{
	if (sig == SIGINT && !g_forks)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		rl_replace_line("", STDIN_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGINT && g_forks > 0)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		rl_replace_line("", STDIN_FILENO);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
	}
}

void	read_command(t_m *m, char *com)
{
	m->s = strjoinm(0, com, 0, ft_strlen(com));
	add_history(m->s);
	if (priorities_operators(m->s, m))
		infix_priorities_operators(m->infix, m);
	ft_lstclear(&m->infix, free);
	rl_free(m->s);
	m->s = 0;
	rl_on_new_line();
}

void	set_signal(void)
{
	struct sigaction	act;

	act.sa_flags = SA_RESTART;
	act.sa_handler = signal_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
}

// Clears the terminal screen
static void	interactive_mode(t_m *m, char *com)
{
	struct termios		term;

	tcgetattr(STDIN_FILENO, &term);
	printf("\033[2J\033[1;1H");
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	while (1)
	{
		set_signal();
		com = readline("minishell$ ");
		if (com)
		{
			while (*com && ft_strchr(" \n", *com))
				com++;
			if (*com)
				read_command(m, com);
		}
		if (!com)
		{
			write (1, "exit\n", 5);
			exit_error(m, 0, 0);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_m						m;
	char					*com;

	(void)argc;
	(void)argv;
	m.env = astr_copy(env);
	init(&m);
	com = 0;
	interactive_mode(&m, com);
	exit_error(&m, 0, m.exit_code);
}
