/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:01:37 by ngoc              #+#    #+#             */
/*   Updated: 2023/07/28 16:01:41 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home()
{
	char	*p;
	char	*u;

	u = getenv("HOME");
	if (!u)
		return ("/");
	return (u);
}

int	get_path(t_m *m)
{
	if (chdir(m->cwd))
	{
		m->exit_code = 1;
		return (0);
	}
	m->exit_code = 0;
	return (1);
}

int	get_path1(t_m *m)
{
	//printf("getpath1 |%s|\n", m->cwd);
	if (chdir(m->cwd))
	{
		getcwd(m->cwd, sizeof(m->cwd));
		perror("minishell: cd");
		//ft_putstr_fd("No such file or directory\n", 2);
		m->exit_code = 1;
		return (0);
	}
	m->exit_code = 0;
	return (1);
}

int	cd(t_m *m, char *path)
{
	int		i;
	int		m_free;
	char	*s;
	char	*p;

	//printf("path |%s|\n", path);
	if (!path)
		ft_strlcpy(m->cwd, get_home(), ft_strlen(get_home()) + 1);
	else if (*path == '~')
	{
		ft_strlcpy(m->cwd, get_home(), ft_strlen(get_home()) + 1);
		ft_strlcat(m->cwd, &path[1], ft_strlen(m->cwd) + ft_strlen(&path[1]) + 1);
	}
	else if (!ft_strncmp(path, ".", 2))
	{
		DIR *d = opendir(m->cwd);
		if (d)
			closedir(d);
		else
			ft_strlcat(m->cwd, "/.", ft_strlen(m->cwd) + 3);
	}
	else if (!ft_strncmp(path, "./", 3))
	{
		if (m->cwd[ft_strlen(m->cwd) - 1] == '/')
			ft_strlcat(m->cwd, "./", ft_strlen(m->cwd) + 3);
		else
			ft_strlcat(m->cwd, "/./", ft_strlen(m->cwd) + 4);
	}
	else if (!ft_strncmp(path, "./", 2))
		ft_strlcat(m->cwd, &path[1], ft_strlen(m->cwd) + ft_strlen(&path[1]) + 1);
	else if (!ft_strncmp(path, "..", 3))
	{
		getcwd(m->cwd, sizeof(m->cwd));
		i = ft_strlen(m->cwd);
		if (i > 0)
		{
			if (i > 1 && m->cwd[i - 1] == '/')
				i--;
			while (i > 2 && !ft_strncmp(&m->cwd[i - 2], "/.", 2))
				i -= 2;
			while (m->cwd[--i] != '/' && m->cwd[i])
				;
		}
		m->cwd[i] = 0;
	}
	else if (!ft_strncmp(path, "../", 3))
	{
		getcwd(m->cwd, sizeof(m->cwd));
		i = ft_strlen(m->cwd);
		int	j = 1;
		while (m->cwd[--i] != '/' && m->cwd[i])
			;
		while (!ft_strncmp(&path[j * 3], "../", 3))
		{
			j++;
			if (i > 0)
				while (m->cwd[--i] != '/' && m->cwd[i])
					;
		}
		m->cwd[i] = 0;
		ft_strlcat(m->cwd, "/", ft_strlen(m->cwd) + 2);
		ft_strlcat(m->cwd, &path[j * 3], ft_strlen(m->cwd) + ft_strlen(&path[j * 3]) + 1);
	}
	else if (*path != '/')
	{
		getcwd(m->cwd, sizeof(m->cwd));
		ft_strlcat(m->cwd, "/", ft_strlen(m->cwd) + 2);
		ft_strlcat(m->cwd, &path[0], ft_strlen(m->cwd) + ft_strlen(&path[0]) + 1);
	}
	return (get_path1(m));
}
