/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 09:51:49 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/16 03:28:46 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_forks;

void	child_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		rl_replace_line("", STDIN_FILENO);
		rl_redisplay();
	}
}

void	main_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		rl_replace_line("", STDIN_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
	}
}

//static void	signal_handler(int sig)
//{
//	if (sig == SIGINT && !g_forks)
//	{
//		ft_putchar_fd('\n', STDIN_FILENO);
//		rl_replace_line("", STDIN_FILENO);
//		rl_on_new_line();
//		rl_redisplay();
//	}
//	else if (sig == SIGINT && g_forks > 0)
//	{
//		ft_putchar_fd('\n', STDIN_FILENO);
//		rl_replace_line("", STDIN_FILENO);
//		rl_redisplay();
//	}
//	else if (sig == SIGQUIT)
//	{
//	}
//}

void	read_command(t_m *m, char *com)
{
	int	i;

	i = -1;
	while (com[++i] && ft_strchr(" 	\n", com[i]))
		;
	if (!com[i])
	{
		free(com);
		return ;
	}
	m->s = strjoinm(0, &com[i], 0, ft_strlen(&com[i]));
	free(com);
	add_history(m->s);
	if (priorities_operators(m->s, m))
		infix_priorities_operators(m->infix, m);
	ft_lstclear(&m->infix, free);
	if (m->s)
		rl_free(m->s);
	m->s = 0;
	rl_on_new_line();
}

// Clears the terminal screen
static void	interactive_mode(t_m *m)
{
	struct sigaction	act;
	char		*com;

	while (1)
	{
		act.sa_flags = SA_RESTART;
		act.sa_handler = main_signal_handler;
		sigemptyset(&act.sa_mask);
		sigaction(SIGINT, &act, NULL);
		signal(SIGQUIT, SIG_IGN);
		com = readline("minishell$ ");
		if (com)
			read_command(m, com);
		else
		{
			write (1, "exit\n", 5);
			exit_error(m, 0, 0);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_m						m;
	struct termios		term;

	(void)argc;
	(void)argv;
	m.env = astr_copy(env);
	init(&m);
	tcgetattr(STDIN_FILENO, &term);
	printf("\033[2J\033[1;1H");
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	interactive_mode(&m);
	exit_error(&m, 0, m.exit_code);
}
