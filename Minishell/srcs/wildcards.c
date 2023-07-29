/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/07/29 10:16:26 by ngoc             ###   ########.fr       */
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
			&& p + (int) ft_strlen(ss[i - 1]) != len)
		return (0); 
	return (1);
}

int	files(char *path, char *s, char **ss, t_list **args)
{
	DIR *dir;
	struct dirent *entry;
	int	i;
	char	*o;

	dir = opendir(path);
	if (!dir) {
		perror("Unable to open directory");
		return (0);
	}
	i = 0;
	while ((entry = readdir(dir)))
	{
		if (ft_strncmp(entry->d_name, ".", 2) && ft_strncmp(entry->d_name, "..", 3))
			if (!ss[0] || check(entry->d_name, s, ss))
			{
				o = 0;
				o = strjoinm(o, "\'", ft_strlen(o), 1);
				o = strjoinm(o, entry->d_name, ft_strlen(o), ft_strlen(entry->d_name));
				o = strjoinm(o, "\'", ft_strlen(o), 1);
				ft_lstadd_back(args, ft_lstnew(o));
				i++;
			}
	}
	closedir(dir);
	return (i);
}

void	wildcards(char *s, t_list **args, t_m *m)
{
	char	**ss;
	char	*s0;
	int	found;
	int	i;

	if (!s)
		return ;
	found = 0;
	if (!getcwd(m->cwd, sizeof(m->cwd)))
		return ;
	ss = ft_split(s, '*');
	i = -1;
	while (ss[++i])
	{
		s0 = remove_quotes(ss[i], ft_strlen(ss[i]), m);
		free(ss[i]);
		ss[i] = s0;
	}
	if (!files(m->cwd, s, ss, args))
		ft_lstadd_back(args, ft_lstnew(ft_strdup(s)));
	free(s);
	free_ss(ss);
}
