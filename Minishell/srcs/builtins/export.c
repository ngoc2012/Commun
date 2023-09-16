/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:14:50 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/16 07:31:55 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

static int	invalid_iden(char *s)
{
	g_exit_code = 1;
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static int	match(char **ss, char *s)
{
	int	i;

	i = -1;
	while (ss[++i])
		if (!ft_strdcmp(ss[i], s))
			return (i);
	return (-1);
}

static void	create_var(t_m *m, int i, int p, int cat)
{
	int		j;
	char	*s_e;

	if (ft_isdigit(m->args[i][0]) || !is_all_env(m->args[i], p))
		invalid_iden(m, m->args[i]);
	else
	{
		j = match(m->env, m->args[i]);
		if (j != -1 && cat)
			m->env[j] = strjoinm(m->env[j], &m->args[i][p + 2],
					ft_strlen(m->env[j]), ft_strlen(&m->args[i][p + 2]));
		else
		{
			if (j != -1)
			{
				s_e = m->env[j];
				m->env[j] = ft_strdup(m->args[i]);
				free(s_e);
			}
			else
				m->env = astr_addback(m->env,
						strjoinm(0, m->args[i], 0, ft_strlen(m->args[i])));
		}
		g_exit_code = 0;
	}
}

static int	check_invalid(t_m *m, int i, int p)
{
	if (m->args[i][0] == '-')
	{
		g_exit_code = 1;
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(m->args[i], 2);
		ft_putstr_fd("': invalid option\n", 2);
		return (1);
	}	
	if (!p)
		return (invalid_iden(m, m->args[i]));
	else if (p == -1)
	{
		if (ft_isdigit(m->args[i][0])
				|| !is_all_env(m->args[i], ft_strlen(m->args[i])))
			return (invalid_iden(m, m->args[i]));
	}
	return (0);
}

int	expt(t_m *m)
{
	int	i;
	int	p;
	int	cat;

	i = 0;
	while (m->args[++i])
	{
		p = chr_pos(m->args[i], '=');
		if (!check_invalid(m, i, p))
		{
			cat = 0;
			if (p != -1 && m->args[i][p - 1] == '+')
			{
				p -= 1;
				cat = 1;
			}
			create_var(m, i, p, cat);
		}
	}
	return (1);
}
