/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:01:37 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/08 16:41:07 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home(void)
{
	char	*p;
	char	*u;

	u = getenv("HOME");
	if (!u)
		return ("/");
	return (u);
}

int	get_path(t_m *m, char *path)
{
	if (chdir(path))
	{
		free(path);
		perror("minishell: cd");
		m->exit_code = 1;
		return (0);
	}
	free(path);
	getcwd(m->cwd, sizeof(m->cwd));
	m->exit_code = 0;
	return (1);
}

int	cd(t_m *m, char *path)
{
	int		i;
	int		m_free;
	char	*s;
	char	*p;
	DIR		*d;

	if (!ft_strncmp(path, ".", 2))
	{
		d = opendir(m->cwd);
		if (d)
			closedir(d);
		else
		{
			ft_putstr_fd("cd: error retrieving current directory\n", 2);
			ft_strlcat(m->cwd, "/.", ft_strlen(m->cwd) + 3);
			m->exit_code = 0;
			return (0);
		}
	}
	return (get_path(m, abs_path(m, path)));
}
