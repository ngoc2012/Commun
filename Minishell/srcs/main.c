/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:32:52 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/07 17:39:52 by ngoc             ###   ########.fr       */
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
	if (!ft_strncmp(args[0], "exit", 5)) {
		free_ss(args);
		return (0);
	}
	if (!ft_strncmp(args[0], "echo", 5))
		echo(m, &args[1]);
	if (!ft_strncmp(args[0], "pwd", 4))
	{
		pwd(m);
		ft_putstr_fd(m->cwd, 1);
		write(1, "\n", 1);
	}
	if (!ft_strncmp(args[0], "cd", 3))
		cd(m, args[1]);
	free_ss(args);
	return (1);
}
/*
typedef struct	s_c
{
	t_m	*m;
	char	*s;
}	t_c;
*/

void	eval_com(t_list *postfix, t_m *m)
{
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
	char	*s;
	t_list	*postfix;
	s = 0;
	while (1) {
		com = readline("minishell$ ");
		while (*com && ft_strchr(" \n", *com))
			com++;
		if (*com)
		{
			s = 0;
			s = strjoinm(s, com, 0, ft_strlen(com));
			postfix = split_ops(s, &m);
			while (!postfix)
			{
				if (m.syntax_error)
					break ;
				s = strjoinm(s, "\n", ft_strlen(s), 1);
				com = readline("> ");
				s = strjoinm(s, com, ft_strlen(s), ft_strlen(com));
				postfix = split_ops(s, &m);
			}
			printf("\nPostfix:");
			ft_lstiter(postfix, print_content);
			eval_com(postfix, &m);
			ft_lstclear(&postfix, free);
			//if (!m.syntax_error && !command(s, &m))
			if (!command(s, &m))
				break ;
			add_history(s);
			rl_free(s);
			rl_on_new_line();
		}
	}
	if (s)
		free(s);
	return (m.exit_code);
}
