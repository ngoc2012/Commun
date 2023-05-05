/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:32:52 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/05 13:58:33 by ngoc             ###   ########.fr       */
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

int	n_args(char *s)
{
	int		i;
	int		i0;
	int		n;
	char	d;

	n = 0;
	while (*s && *s == ' ')
		s++;
	d = ' ';
	i0 = 0;
	i = 0;
	while (s[i])
	{
		if (ft_strchr("\"'", s[i]))
		{
			d = s[i];
			while (s[++i] && s[i] != d)
				;
			if (s[i] == d)
				d = ' ';
			else
				return (-1);
			i++;
		}
		else if (s[i] == ' ')
		{
			n++;
			while (s[++i] && s[i] == ' ')
				;
			i0 = i;
		}
		else
			i++;
	}
	if (i > i0)
		n++;
	return (n);
}


char	**split_args(char *s)
{
	int		i;
	int		i0;
	int		n_a;
	char	d;
	char	**ss;
	char	**ss0;

	n_a = n_args(s);
	if (!n_a)
		return (0);
	ss = malloc(sizeof(char *) * (n_a + 1));
	ss0 = ss;
	while (*s && ft_strchr(" \n", *s))
		s++;
	d = ' ';
	i0 = 0;
	i = 0;
	while (s[i])
	{
		if (ft_strchr("\"'", s[i]))
		{
			d = s[i];
			while (s[++i] && s[i] != d)
				;
			i++;
		}
		else if (s[i] == ' ')
		{
			*ss = malloc(i - i0 + 1);
			ft_memcpy(*ss, &s[i0], i - i0);
			(*ss)[i - i0] = 0;
			ss++;
			while (s[++i] && s[i] == ' ')
				;
			i0 = i;
		}
		else
			i++;
	}
	if (i > i0)
	{
		*ss = malloc(i - i0 + 1);
		ft_memcpy(*ss, &s[i0], i - i0);
		(*ss)[i - i0] = 0;
		ss++;
	}
	*ss = 0;
	return (ss0);
}

int	command(char *s, t_m *m)
{
	char	**args;

	args = split_args(s);
	if (!args)
		return (0);
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
	m.env = env;
	char	*com;
	char	*s;
	s = 0;
	t_list *ops;
	while (1) {
		com = readline("minishell$ ");
		if (*com)
		{
			s = 0;
			s = strjoinm(s, com, 0, ft_strlen(com));
			while (n_args(s) == -1)
			{
				s = strjoinm(s, "\n", ft_strlen(s), 1);
				com = readline("> ");
				s = strjoinm(s, com, ft_strlen(s), ft_strlen(com));
			}
			split_ops(com, ops);
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
