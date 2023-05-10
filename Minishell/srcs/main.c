/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:32:52 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/09 18:10:49 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ss(char **ss)
{
	char	**ss0;

	ss0 = ss;
	while (*ss)
		free(*(ss++));
	free(ss0);
}

int	command(char *s, t_m *m)
{
	char	**args;

	args = split_args(s);
	if (!args)
		return (1);
	else if (!ft_strncmp(args[0], "exit", 5)) {
		free_ss(args);
		if (m->s)
			free(m->s);
		exit(EXIT_SUCCESS);
	}
	else if (!ft_strncmp(args[0], "echo", 5))
		echo(m, &args[1]);
	else if (!ft_strncmp(args[0], "pwd", 4))
	{
		pwd(m);
		ft_putstr_fd(m->cwd, 1);
		write(1, "\n", 1);
	}
	else if (!ft_strncmp(args[0], "cd", 3))
		cd(m, args[1]);
	else
		exec(m, s, args);
	//printf("m->exit_code = %d\n", m->exit_code);
	free_ss(args);
	return (1);
}

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
				if ((!m->exit_code && ((char *)p->content)[0] == '&')
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
			//printf("\n|%s, %d, %d, %d|", (char *)p->content, level, blocked, m->exit_code);
			command((char *)p->content, m);
			last_level = level;
		}
		p = p->next;
	}
}

// Syntaxe error -> code 2
// \n\n\n egals ;
int	main(int argc, char **argv, char **env)
{
	t_m	m;

	if (argc > 1)
		return (1);
	(void)argv;
	// Clears the terminal screen
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	printf("\033[2J\033[1;1H");
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	m.exit_code = 0;
	m.syntax_error = 0;
	m.env = env;
	char	*com;
	t_list	*infix;
	m.s = 0;
	while (1) {
		com = readline("minishell$ ");
		while (*com && ft_strchr(" \n", *com))
			com++;
		if (*com)
		{
			m.s = 0;
			m.s = strjoinm(m.s, com, 0, ft_strlen(com));
			infix = split_ops(m.s, &m);
			while (!infix)
			{
				if (m.syntax_error)
					break ;
				m.s = strjoinm(m.s, "\n", ft_strlen(m.s), 1);
				com = readline("> ");
				m.s = strjoinm(m.s, com, ft_strlen(m.s), ft_strlen(com));
				infix = split_ops(m.s, &m);
			}
			//ft_lstiter(infix, print_content);
			eval_com(infix, &m);
			ft_lstclear(&infix, free);
			//if (!m.syntax_error && !command(s, &m))
			//if (!command(s, &m))
			//	break ;
			add_history(m.s);
			rl_free(m.s);
			rl_on_new_line();
		}
	}
	if (m.s)
		free(m.s);
	return (m.exit_code);
}
