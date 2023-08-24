/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:14:50 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/07 17:51:49 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expt_all(t_m *m, int fd)
{
	char	**env;
	char	*s;
	char	*s0;

	env = m->env;
	while (*env)
	{
		s = strjoinm(0, *env, 0, chr_pos(*env, '='));
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(s, fd);
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(getenv(s), fd);
		ft_putstr_fd("\"\n", fd);
		free(s);
		env++;
	}
	m->exit_code = 0;
	return (1);
}
