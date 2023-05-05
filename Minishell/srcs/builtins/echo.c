/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/04 22:19:22 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

void	files(char *path)
{
	DIR *dir;
	struct dirent *entry;

	dir = opendir(path);
	if (!dir) {
		perror("Unable to open directory");
		return ;
	}

	while ((entry = readdir(dir))) {
		//if (entry->d_type == DT_REG) {
			printf("%s\n", entry->d_name);
		//}
	}

	closedir(dir);
}

void	echo(t_m *m, char **args)
{
	char	*s;

	if (!args)
		write(1, "\n\n", 2);
	while (*args)
	{
		//pwd(m);
		s = parse(*args, m);
		ft_putstr_fd(s, 1);
		free(s);
		args++;
		if (*args)
			write(1, " ", 1);
	}
	if (!ft_strncmp(args[0], "-n", 3))
		write(1, "\n", 1);
}
