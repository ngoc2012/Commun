/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:32:52 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/03 23:03:39 by ngoc             ###   ########.fr       */
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

int	n_args(char *s, char *d)
{
	int	i;
	int	n;

	n = 0;
	while (*s && *s == ' ')
		s++;
	*d = ' ';
	i = -1;
	while (s[++i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			*d = s[i];
			while (s[++i] && s[i] != *d)
				;
			if (s[i] == *d)
				*d = ' ';
			else
				break ;
		}
		else if (s[i] == ' ')
			n++;
	}
	if (i > 0)
		n++;
	return (n);
}

void	split_args(char *s, char *d)
{
	printf("%d", n_args(s, d));
}

//int	main(int argc, char **argv, char **env)
int	main(int argc, char **argv)
{
	//t_m	m;

	if (argc > 1)
		return (1);
	(void)argv;
	// Clears the terminal screen
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	printf("\033[2J\033[1;1H");
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	//m.exit_code = 0;
	//m.env = env;
	char	*com;
	char	*s;
	char	d;
	//int	n_a;
	while (1) {
		com = readline("minishell$ ");
		s = 0;
		s = strjoinm(s, com, 0, ft_strlen(com));
		n_args(com, &d);
		while (d != ' ')
		{
			s = strjoinm(s, "\n", ft_strlen(s), 1);
			com = readline("> ");
			s = strjoinm(s, com, ft_strlen(s), ft_strlen(com));
			n_args(s, &d);
		}
		printf("|%s, ", s);
		printf("%d, ", n_args(s, &d));
		printf("%c|", d);
		if (!ft_strncmp(s, "exit", 5)) {
			break;
		}
		//char	**ss;
		//ss = ft_split(com, ' ');
		//if (!ft_strncmp(ss[0], "exit", 5))
		//{
		//	free_ss(ss);
		//	exit(EXIT_SUCCESS);
		//}
		//if (!ft_strncmp(ss[0], "echo", 5))
		//	echo(&m, com);
		//if (!ft_strncmp(ss[0], "pwd", 4))
		//{
		//	pwd(&m);
		//	ft_putstr_fd(m.cwd, 1);
		//	write(1, "\n", 1);
		//}
		//if (!ft_strncmp(ss[0], "cd", 3))
		//	cd(&m, ss[1]);
		//free_ss(ss);
		add_history(s);
		rl_free(s);
		rl_on_new_line();
		//free(s);
	}
	//HISTORY_STATE* hist = history_get_history_state();
	//HIST_ENTRY** hist_list = history_list();
	//int i;
	//for (i = 0; i < hist->length; i++) {
	//	printf("%d: %s\n", i + 1, hist_list[i]->line);
	//}
	return (0);
}
