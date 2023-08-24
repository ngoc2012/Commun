/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/17 15:59:37 by ngoc             ###   ########.fr       */
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

static int	ft_strcmp_val(char *s1, char *s2)
{
	int	i1;
	int	i2;

	if (!s1 || !s2)
		return (0);
	if (*s1 == '\\')
		s1++;
	if (*s2 == '\\')
		s2++;
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
		if (*s1 == '\\')
			s1++;
		if (*s2 == '\\')
			s2++;
	}
	i1 = *s1;
	if (*s1 < 0)
		i1 = *s1 + 256;
	i2 = *s2;
	if (*s2 < 0)
		i2 = *s2 + 256;
	if (i1 <= i2)
		return (1);
	return (0);
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

int	files(t_m *m, char *s, char **ss, t_list **args)
{
	DIR *dir;
	struct dirent *entry;
	int	i;
	char	*o;
	char	*s0;
	t_list	*new;
	char	*path;

	path = m->cwd;
	dir = opendir(path);
	if (!dir) {
		perror("Unable to open directory");
		return (0);
	}
	new = 0;
	i = 0;
	while ((entry = readdir(dir)))
	{
		if (ft_strncmp(entry->d_name, ".", 2) && ft_strncmp(entry->d_name, "..", 3))
			if (!ss[0] || check(entry->d_name, s, ss))
			{
				//printf("before entry | %s |\n", entry->d_name);
				o = strjoinm(0, "\'", 0, 1);
				s0 = entry->d_name;
				while (*s0)
				{
					if (*s0 == '\'')
						o = strjoinm(o, "\\", ft_strlen(o), 1);
					o = strjoinm(o, s0++, ft_strlen(o), 1);
				}
				//o = strjoinm(o, entry->d_name, ft_strlen(o), ft_strlen(entry->d_name));
				o = strjoinm(o, "\'", ft_strlen(o), 1);
				//printf(" after entry |%s|\n", o);
				ft_lstadd_back2(&new, ft_lstnew(o), ft_strcmp_val);
				i++;
			}
	}
	m->n_wildcards = i;
	ft_lstadd_back(args, new);
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
	if (!files(m, s, ss, args))
		ft_lstadd_back(args, ft_lstnew(ft_strdup(s)));
	free(s);
	free_array_str(&ss, 1);
}
