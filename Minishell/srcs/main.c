/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:32:52 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/02 09:51:57 by ngoc             ###   ########.fr       */
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
	char *command;
	while (1) {
		command = readline("minishell$ ");
		if (!ft_strncmp(command, "exit", 5)) {
			break;
		}
		char	**ss;
		ss = ft_split(command, ' ');
		if (!ft_strncmp(ss[0], "exit", 5))
		{
			free_ss(ss);
			exit(EXIT_SUCCESS);
		}
		if (!ft_strncmp(ss[0], "echo", 5))
			echo(&m, command);
		if (!ft_strncmp(ss[0], "pwd", 4))
			pwd(&m);
		if (!ft_strncmp(ss[0], "cd", 3))
			cd(&m, ss[1]);
		free_ss(ss);
		add_history(command);
		rl_free(command);
		rl_on_new_line();
	}
	//HISTORY_STATE* hist = history_get_history_state();
	//HIST_ENTRY** hist_list = history_list();
	//int i;
	//for (i = 0; i < hist->length; i++) {
	//	printf("%d: %s\n", i + 1, hist_list[i]->line);
	//}
	return (0);
}
