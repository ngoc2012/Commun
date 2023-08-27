/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 09:51:49 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/27 12:14:57 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_m	*g_m;

static void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	if (sig == SIGINT && g_m->process_level)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		rl_replace_line("", STDIN_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT && g_m->process_level)
		exit(0);
}

void	read_command(t_m *m)
{
	if (priorities_operators(m->s, m)
		&& infix_priorities_operators(m->infix, m))
		add_history(m->s);
	ft_lstclear(&m->infix, free);
	rl_free(m->s);
}

void	read_from_input(t_m *m)
{
	char	buffer[BUFFER_SIZE + 1];
	int		ret;

	if (!isatty(STDIN_FILENO))
	{
		ret = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		m->s = strjoinm(0, buffer, 0, ret);
		while (ret)
		{
			ret = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			if (ret)
				m->s = strjoinm(m->s, buffer, ft_strlen(m->s), ret);
		}
		read_command(m);
		exit(m->exit_code);
	}
}

// Clears the terminal screen
void	interactive_mode(t_m *m)
{
	struct termios	term;
	char			*com;

	tcgetattr(STDIN_FILENO, &term);
	printf("\033[2J\033[1;1H");
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	while (1)
	{
		com = readline("minishell$ ");
		if (com)
		{
			while (*com && ft_strchr(" \n", *com))
				com++;
			if (*com)
			{
				m->s = strjoinm(0, com, 0, ft_strlen(com));
				read_command(m);
				rl_on_new_line();
			}
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	struct sigaction	act;
	t_m					m;

	g_m = &m;
	act.sa_flags = SA_RESTART | SA_SIGINFO;
	act.sa_sigaction = &signal_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	m.env = astr_copy(env);
	init(&m);
	read_from_input(&m);
	interactive_mode(&m);
	free_m(&m);
	exit(m.exit_code);
	return (0);
}
