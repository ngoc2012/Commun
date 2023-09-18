/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:14:50 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/18 14:35:17 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_var(char **env, char *var, int fd)
{
	char	*s;

	ft_putstr_fd("declare -x ", fd);
	if (ft_strchr(var, '='))
	{
		s = strjoinm(0, var, 0, chr_pos(var, '='));
		ft_putstr_fd(s, fd);
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(get_env(s, env), fd);
		ft_putstr_fd("\"\n", fd);
		free(s);
	}
	else
	{
		ft_putstr_fd(var, fd);
		ft_putchar_fd('\n', fd);
	}
}

int	expt_all(t_m *m, int fd)
{
	int	i;
	int	n;

	i = 0;
	while (++i < m->argc)
		printf("%d |%s|\n", i, m->args[i]);
	if (m->argc == 1)
	{
		i = -1;
		while (m->env[++i])
			print_var(m->env, m->env[i], fd);
		return (1);
	}
	else if (m->n_pipes == 1)
		return (expt(m));
	return (1);
}
