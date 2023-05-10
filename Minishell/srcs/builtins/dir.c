/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:01:37 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/10 13:09:41 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_m *m)
{
	if (getcwd(m->cwd, sizeof(m->cwd)))
		m->exit_code = 0;
	else
	{
		perror("getcwd() error");
		m->exit_code = 1;
	}
}

char	*get_home()
{
	char	*p;
	char	*u;

	u = getenv("USER");
	if (!u)
		return (0);
	p = 0;
	p = strjoinm(p, HOME, 0, ft_strlen(HOME));
	if (!p)
		return (0);
	p = strjoinm(p, u, ft_strlen(p), ft_strlen(u));
	return (p);
}

void	cd(t_m *m, char *path)
{
	int		i;
	int		m_free;
	char	*s;
	char	*p;

	if (!path)
		p = get_home();
	else if (*path == '~')
	{
		p = get_home();
		p = strjoinm(p, &path[1], ft_strlen(p), ft_strlen(&path[1]));
	}
	//else if (*path == '.' && *(path + 1) == '/')
	else if (!ft_strncmp(path, "./", 2))
	{
		pwd(m);
		p = 0;
		p = strjoinm(p, m->cwd, 0, ft_strlen(m->cwd));
		p = strjoinm(p, &path[1], ft_strlen(p), ft_strlen(&path[1]));
		//printf("|%s|\n", p);
	}
	//else if (*path == '.' && *(path + 1) == '.' && !(*(path + 2)))
	else if (!ft_strncmp(path, "..", 3))
	{
		pwd(m);
		i = ft_strlen(m->cwd);
		if (i > 0)
			while (m->cwd[--i] != '/' && m->cwd[i])
				;
		p = 0;
		p = strjoinm(p, m->cwd, 0, i);
	}
	//else if (*path == '.' && *(path + 1) == '.' && *(path + 2) == '/')
	else if (!ft_strncmp(path, "../", 3))
	{
		pwd(m);
		i = ft_strlen(m->cwd);
		int	j = 1;
		while (m->cwd[--i] != '/' && m->cwd[i])
			;
		//while (path[j * 3] == '.' && path[j * 3 + 1] == '.' && path[j * 3 + 2] == '/')
		while (!ft_strncmp(&path[j * 3], "../", 3))
		{
			j++;
			//printf("|j = %d|\n", j);
			if (i > 0)
				while (m->cwd[--i] != '/' && m->cwd[i])
					;
		}
		//printf("|%d|\n", i);
		p = 0;
		p = strjoinm(p, m->cwd, 0, i);
		p = strjoinm(p, "/", ft_strlen(p), 1);
		p = strjoinm(p, &path[j * 3], ft_strlen(p), ft_strlen(&path[j * 3]));
		//printf("|%s|\n", p);
	}
	else if (*path != '/')
	{
		pwd(m);
		p = 0;
		p = strjoinm(p, m->cwd, 0, ft_strlen(m->cwd));
		p = strjoinm(p, "/", ft_strlen(p), 1);
		p = strjoinm(p, &path[0], ft_strlen(p), ft_strlen(&path[0]));
		//printf("|%s|\n", p);
	}
	else
		p = ft_strdup(path);
	//printf("dir.c:|%s|\n", p);
	if (chdir(p))
	{
		s = 0;
		s = strjoinm(s, "minishell: cd: ", 0, 15);
		s = strjoinm(s, p, ft_strlen(s), ft_strlen(p));
		perror(s);
		free(s);
		m->exit_code = 1;
	}
	else
		m->exit_code = 0;
	free(p);
	//printf("m->exit_code = %d\n", m->exit_code);
}
