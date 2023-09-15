/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:01:37 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/15 15:56:40 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*relative_path0(t_m *m, char *path)
{
	char	*p;

	if (!path)
	{
		if (!get_home(m))
			return (0);
		return (strjoinm(0, get_home(m), 0, ft_strlen(get_home())));
	}
}
char	*get_home(t_m *m)
{
	char	*u;

	u = get_env("HOME", m);
	return (u);
}

static void	update_pwd(t_m *m, char *var, char *path)
{
	char	*s_e;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (m->env[++i])
		if (!ft_strdcmp(m->env[i], var))
			j = i;
	if (j != -1)
	{
		s_e = m->env[j];
		m->env[j] = strjoinm(0, var, 0, -1);
		m->env[j] = strjoinm(m->env[j], "=", -1, 1);
		m->env[j] = strjoinm(m->env[j], path, -1, -1);
		free(s_e);
	}
	else
	{
		s_e = strjoinm(0, var, 0, -1);
		s_e = strjoinm(s_e, "=", -1, 1);
		s_e = strjoinm(s_e, path, -1, -1);
		m->env = astr_addback(m->env, s_e);
	}
}

int	get_path(t_m *m, char *path)
{
	if (!path || chdir(path))
	{
		perror(path);
		free(path);
		m->exit_code = 1;
		return (0);
	}
	update_pwd(m, "OLDPWD", m->cwd);
	if (!ft_strncmp(path, "//", 3))
		ft_memcpy(m->cwd, "//", 3);
	else
		getcwd(m->cwd, sizeof(m->cwd));
	update_pwd(m, "PWD", m->cwd);
	m->exit_code = 0;
	free(path);
	return (1);
}

int	cd(t_m *m, char *path)
{
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
