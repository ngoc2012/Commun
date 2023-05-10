/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/10 12:14:55 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static int	pos(char *s, char *big)
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

int	check(char *name, char *s, char **ss)
{
	int	p;
	int	last_p;
	int	i;
	int	len;

	last_p = -1;
	p = -1;
	len = ft_strlen(name);
	i = -1;
	while (ss[++i])
	{
		p = pos(ss[i], name);
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
			&& p + (int) ft_strlen(ss[i - 1]) != len)
		return (0); 
	return (1);
}

int	files(char *path, char *s, char **ss, t_list **args)
{
	DIR *dir;
	struct dirent *entry;

	dir = opendir(path);
	if (!dir) {
		perror("Unable to open directory");
		return (0);
	}
	while ((entry = readdir(dir)))
	{
		if (ft_strncmp(entry->d_name, ".", 2) && ft_strncmp(entry->d_name, "..", 3))
			if (!ss[0] || check(entry->d_name, s, ss))
				ft_lstadd_back(args, ft_lstnew(ft_strdup(entry->d_name)));
	}
	closedir(dir);
	return (1);
}

void	wildcards(char *s, t_list **args, t_m *m)
{
	char	**ss;
	int	found;

	found = 0;
	pwd(m);
	ss = ft_split(s, '*');
	if (files(m->cwd, s, ss, args))
		free(s);
	else
		ft_lstadd_back(args, ft_lstnew(s));
	free_ss(ss);
}
