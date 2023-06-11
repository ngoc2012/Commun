/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:32:52 by ngoc              #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Free array of strings
void	free_ss(char **ss)
{
	char	**ss0;

	if (!ss)
		return ;
	ss0 = ss;
	while (*ss)
		free(*(ss++));
	free(ss0);
}

/*
Parse the () in command line to choose the command to execute.
A command is a string between between || ; and &&.
*/
void	eval_com(t_list *p, t_m *m)
{
	t_list	*i;
	t_list	*op;
	int	level;
	int	last_level;
	int	blocked;

	blocked = -1;
	level = 0;
	last_level = 0;
	while (p)
	{
		if (p->content && ((char *)p->content)[0] == '(')
			level++;
		else if (p->content && ((char *)p->content)[0] == ')')
			level--;
		else if (p->content && ft_strchr(";&|", ((char *)p->content)[0]))
		{
			if (!(blocked != -1 && level < blocked))
			{
				if (((char *)p->content)[0] == ';'
					|| (!m->exit_code && ((char *)p->content)[0] == '&')
					|| (m->exit_code && ((char *)p->content)[0] == '|'))
				{
					if (level <= blocked)
						blocked = -1;
				}
				else
					blocked = last_level;
			}
		}
		else if (p->content && !ft_strchr(";&|", ((char *)p->content)[0])
			&& blocked == -1)
		{
			pipes((char *)p->content, m);
			last_level = level;
		}
		p = p->next;
	}
}

t_m	*g_m;

void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(g_m->exit_code);
	}
	else if (sig == SIGQUIT)
		rl_forced_update_display();
}

// Syntaxe error -> code 2
// \n\n\n egals ;
int	main(int argc, char **argv, char **env)
{
	struct sigaction	act;
	t_m	m;

	g_m = &m;

	act.sa_flags = SA_RESTART | SA_SIGINFO;
	act.sa_sigaction = &signal_handler;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);

	m.exit_code = 0;
	m.syntax_error = 0;
	m.s = 0;
	m.coms = 0;
	m.args = 0;
	m.infix = 0;
	m.pipefd = 0;
	m.env = env;
	m.envs = 0;
	m.fout = 1;
	m.fin = 0;
	m.heredoc = 0;
	m.heredocf = 0;
	//if (argc > 1)
	//{
	//	printf("haha\n");
	//	int	i = 0;
	//	if (ft_strncmp("-c", argv[++i], 3))
	//		while (i < argc)
	//		{
	//			split_ops(argv[i], &m);
	//			eval_com(m.infix, &m);
	//			ft_lstclear(&m.infix, free);
	//		}
	//	return (m.exit_code);
	//}
	//printf("hehe\n");

	//m.fin = open(STDOUT_FILENO, O_RDONLY);
	if (!isatty(STDIN_FILENO))
	{
		char	buffer[BUFFER_SIZE + 1];
		int	ret = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		m.s = 0;
		m.s = strjoinm(m.s, buffer, 0, ret);
		while (ret)
		{
			ret = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			if (ret)
				m.s = strjoinm(m.s, buffer, ft_strlen(m.s), ret);
		}
		split_ops(m.s, &m);
		eval_com(m.infix, &m);
		ft_lstclear(&m.infix, free);
		free(m.s);
		return (m.exit_code);
	}
	//close(STDIN_FILENO);

	// Clears the terminal screen
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	printf("\033[2J\033[1;1H");
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	char	*com;
	while (1) {
		com = readline("minishell$ ");
		if (com)
		{
			while (*com && ft_strchr(" \n", *com))
				com++;
			if (*com)
			{
				m.s = 0;
				m.s = strjoinm(m.s, com, 0, ft_strlen(com));
				while (!split_ops(m.s, &m))
				{
					ft_lstclear(&m.infix, free);
					if (m.syntax_error)
						break ;
					m.s = strjoinm(m.s, "\n", ft_strlen(m.s), 1);
					com = readline("> ");
					m.s = strjoinm(m.s, com, ft_strlen(m.s), ft_strlen(com));
				}
				eval_com(m.infix, &m);
				ft_lstclear(&m.infix, free);
				//if (!m.syntax_error && !command(s, &m))
				//if (!command(s, &m))
				//	break ;
				add_history(m.s);
				rl_free(m.s);
				//free_m(&m);
				rl_on_new_line();
			}
		}
	}
	return (m.exit_code);
}
