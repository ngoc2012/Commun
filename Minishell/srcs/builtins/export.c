/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:14:50 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/17 08:37:33 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chr_pos(char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (i);
	return (-1);
}

void	expt(t_m *m, char **args)
{
	int	i;
	int	j;
	int	p;
	int	is_env;

	i = 0;
	while (args[++i])
	{
		is_env = 1;
		p = chr_pos(args[i], '=');
		if (p > 0)
		{
			j = -1;
			while (++j < p)
				if (!isenv(args[i][j]))
					is_env = 0;
			if (is_env)
			{
				printf("%s, ", args[i]);
			}
		}
	}
	//free_ss(m->args);
	//free_ss(m->coms);
	//rl_free(m->s);
	//if (m->pipefd)
	//	free(m->pipefd);
	//ft_lstclear(&m->infix, free);
	exit(EXIT_SUCCESS);
}
