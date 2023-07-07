/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:14:50 by ngoc              #+#    #+#             */
/*   Updated: 2023/07/07 06:41:31 by ngoc             ###   ########.fr       */
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
	if ((!*s1  && ft_strchr("=+", *s2)) || (!*s2 && ft_strchr("=+", *s1))
		|| (ft_strchr("=+", *s1) && ft_strchr("=+", *s2)))
		return (0);
	//printf("%c - %c\n", *s1, *s2);
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
	while (lst)
	{

		if (!ft_strdcmp((char *) lst->content, s))
			return ((char *) lst->content);
		lst = lst->next;
	}
	return (0);
}

int	expt(t_m *m, char **args)
{
	int	i;
	int	p;
	int	cat;
	char	*s_e;
	char	*s_e0;

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
				s_e = 0;
				if (cat)
				{
					s_e0 = lst_match(m->envs, args[i]);
					if (s_e0)
					{
						//printf("%s\n", s_e0);
						s_e = strjoinm(s_e, s_e0, ft_strlen(s_e), ft_strlen(s_e0));
					}
					else
					{
						s_e = strjoinm(s_e, args[i], ft_strlen(s_e), p + 1);
						s_e = strjoinm(s_e, "=", ft_strlen(s_e), 1);
					}
					//printf("%d-%s-%s\n", p, s_e, &args[i][p + 2]);
					s_e = strjoinm(s_e, &args[i][p + 2], ft_strlen(s_e), ft_strlen(&args[i][p + 2]));
				}
				else
				{
					s_e = str_env(args[i], ft_strlen(args[i]), m);
				}
				ft_lstremove_if(&m->envs, args[i], ft_strdcmp, free);
				ft_lstadd_back(&m->envs, ft_lstnew(s_e));
			}
		}
		else
			invalid_iden(m, args[i]);
	}
	return (1);
}
