/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:14:50 by ngoc              #+#    #+#             */
/*   Updated: 2023/07/03 20:18:22 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strdcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 == *s2 && *s1 && *s2 && *s1 != '=' && *s2 != '=')
	{
		s1++;
		s2++;
	}
	if ((!*s1 && *s2 == '=') || (!*s2 && *s1 == '='))
		return (0);
	return ((unsigned char) *s1 - (unsigned char) *s2);
}

int	chr_pos(char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (i);
	return (-1);
}

// All character is alpha num or _
int	is_all_env(char *s, int p)
{
	int	i;

	i = -1;
	while (++i < p)
		if (!isenv(s[i]))
			return (0);
	return (1);
}

int	expt(t_m *m, char **args)
{
	int	i;
	int	j;
	int	p;
	char	*s_en;
	int	invalid;

	invalid = 0;
	i = 0;
	while (args[++i])
	{
		p = chr_pos(args[i], '=');
		if (p > 0)
		{
			if (is_all_env(args[i], p))
			{
				if (ft_isnum(args[i][0]))
					invalid = p;
				else
				{
					ft_lstremove_if(&m->envs, args[i], ft_strdcmp, free);
					s_env = str_env(args[i], ft_strlen(args[i]), m);
					ft_lstadd_back(&m->envs, ft_lstnew(s_env));
					//ft_lstiter(m->envs, print_content);
					//printf(";");
				}
			}
			else
				m->exit_code = 1;
		}
		else
			m->exit_code = 1;
	}
	if (invalid)
	{
		m->exit_code = 1;
		return (1);
	}
	m->exit_code = 0;
	return (1);
}
