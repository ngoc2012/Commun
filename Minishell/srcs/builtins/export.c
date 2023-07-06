/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:14:50 by ngoc              #+#    #+#             */
/*   Updated: 2023/07/06 16:02:49 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strdcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 == *s2 && *s1 && *s2 && !ft_strchr("=+", *s1) && !ft_strchr("=+", *s2))
	{
		s1++;
		s2++;
	}
	if ((!*s1  && ft_strchr("=+", *s2)) || (!*s2 && ft_strchr("=+", *s1)))
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

void	invalid_iden(t_m *m, char *s)
{
	m->exit_code = 1;
	ft_putstr_fd("bash: export: `", 1);
	ft_putstr_fd(s, 1);
	ft_putstr_fd("': not a valid identifier\n", 1);
}

char	*lst_match(t_list *lst, char *s)
{
}

int	expt(t_m *m, char **args)
{
	int	i;
	int	p;
	int	cat;
	char	*s_env;

	cat = 0;
	i = 0;
	while (args[++i])
	{
		p = chr_pos(args[i], '=');
		if (p > 0)
		{
			if (args[i][p - 1] == '+')
			{
				p -= 1;
				cat = 1;
			}
			if (!p)
				invalid_iden(m, args[i]);
			if (ft_isdigit(args[i][0]) || !is_all_env(args[i], p))
				invalid_iden(m, args[i]);
			else
			{
				if (cat)
				{
					s_env = 0;
					s_env = strjoinm(s_env, buffer, ft_strlen(s_env), ret);
				}
				else
				{
					s_env = str_env(args[i], ft_strlen(args[i]), m);
				}
				ft_lstremove_if(&m->envs, args[i], ft_strdcmp, free);
				ft_lstadd_back(&m->envs, ft_lstnew(s_env));
			}
		}
		else
			invalid_iden(m, args[i]);
	}
	return (1);
}
