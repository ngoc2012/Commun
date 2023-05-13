/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:32:52 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/12 00:13:18 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_m(t_m *m)
{
	if (m->s)
		free(m->s);
	if (m->coms)
		free_ss(m->coms);
	if (m->args)
		free_ss(m->args);
	if (m->pipefd)
		free(m->pipefd);
	ft_lstclear(&m->infix, free);
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
	m.s = 0;
	m.coms = 0;
	m.args = 0;
	m.pipefd = 0;
	m.env = env;
	char	*com;
	while (1) {
		com = readline("minishell$ ");
		while (*com && ft_strchr(" \n", *com))
			com++;
		if (*com)
		{
			m.s = 0;
			m.s = strjoinm(m.s, com, 0, ft_strlen(com));
			m.infix = split_ops(m.s, &m);
			while (!m.infix)
			{
				if (m.syntax_error)
					break ;
				m.s = strjoinm(m.s, "\n", ft_strlen(m.s), 1);
				com = readline("> ");
				m.s = strjoinm(m.s, com, ft_strlen(m.s), ft_strlen(com));
				m.infix = split_ops(m.s, &m);
			}
			//ft_lstiter(infix, print_content);
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
	return (m.exit_code);
}
