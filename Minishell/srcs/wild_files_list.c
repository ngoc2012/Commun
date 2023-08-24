/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_files_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/23 23:18:42 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static int	str_pos(char *s, char *big)
{
	int	i;
	int	len;

	len = ft_strlen(s);
	i = -1;
	while (big[++i])
		if (!ft_strncmp(s, &big[i], len))
			return (i);
	return (-1);
}

static int	check(char *name, char *s, char **ss)
{
	int	p;
	int	last_p;
	int	i;

	last_p = -1;
	p = -1;
	i = -1;
	while (ss[++i])
	{
		p = str_pos(ss[i], name);
		if (p == -1)
			return (0);
		if (p < last_p)
			return (0);
		if (s[0] != '*' && !i && p)
			return (0);
		last_p = p;
	}
	if (ss[i])
		return (0);
	if (i > 0 && s[ft_strlen(s) - 1] != '*'
		&& (size_t) p + ft_strlen(ss[i - 1]) != ft_strlen(name))
		return (0);
	return (1);
}

static void	add_splash(char *s, char **o)
{
	while (*s)
	{
		if (*s == '\'')
			*o = strjoinm(*o, "\\", ft_strlen(*o), 1);
		*o = strjoinm(*o, s++, ft_strlen(*o), 1);
	}
}

static int	files_files(DIR *dir, t_list **new, char *s, char **ss)
{
	struct dirent	*e;
	char			*o;
	int				i;

	i = 0;
	e = readdir(dir);
	while (e)
	{
		if (ft_strncmp(e->d_name, ".", 2) && ft_strncmp(e->d_name, "..", 3)
			&& (!ss[0] || check(e->d_name, s, ss)))
		{
			o = strjoinm(0, "\'", 0, 1);
			add_splash(e->d_name, &o);
			o = strjoinm(o, "\'", ft_strlen(o), 1);
			ft_lstadd_back2(new, ft_lstnew(o), ft_strcmp_val);
			i++;
		}
		e = readdir(dir);
	}
	return (i);
}

int	wild_files_list(t_m *m, char *s, char **ss, t_list **args)
{
	DIR		*dir;
	t_list	*new;
	char	*path;

	path = m->cwd;
	dir = opendir(path);
	if (!dir)
		return (return_error(m, "Unable to open directory", 1, 1));
	new = 0;
	m->n_wildcards = files_files(dir, &new, s, ss);
	ft_lstadd_back(args, new);
	closedir(dir);
	return (m->n_wildcards);
}
