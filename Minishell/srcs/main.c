/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 09:51:49 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/17 21:33:35 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

void	main_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		rl_replace_line("", STDIN_FILENO);
		rl_on_new_line();
		rl_redisplay();
		g_exit_code = 130;
	}
}

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

char	*short_link(char *cwd, t_m *m)
{
	char	*home;

	home = get_env("HOME", m->env);
	if (!home)
		return (0);
	if (!ft_strncmp(cwd, home, ft_strlen(home)))
		return (&cwd[ft_strlen(home)]);
	return (0);
}

// Clears the terminal screen
static void	interactive_mode(t_m *m)
{
	struct sigaction	act;
	char				*com;
	char				prompt[PATH_MAX];

	while (1)
	{
		act.sa_flags = SA_RESTART;
		act.sa_handler = main_signal_handler;
		sigemptyset(&act.sa_mask);
		sigaction(SIGINT, &act, NULL);
		signal(SIGQUIT, SIG_IGN);
		ft_strlcpy(prompt, "minishell:", PATH_MAX);
		if (short_link(m->cwd, m))
		{
			ft_strlcat(prompt, "~", PATH_MAX);
			ft_strlcat(prompt, short_link(m->cwd, m), PATH_MAX);
		}
		else
			ft_strlcat(prompt, m->cwd, PATH_MAX);
		ft_strlcat(prompt, "$ ", PATH_MAX);
		com = readline(prompt);
		if (com)
			read_command(m, com);
		else
		{
			write (1, "exit\n", 5);
			exit_error(m, 0, g_exit_code);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_m					m;
	struct termios		term;

	(void)argc;
	(void)argv;
	m.env = astr_copy(env);
	init(&m);
	tcgetattr(STDIN_FILENO, &term);
	ft_putstr_fd("\033[2J\033[1;1H", 1);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	interactive_mode(&m);
	exit_error(&m, 0, g_exit_code);
}
