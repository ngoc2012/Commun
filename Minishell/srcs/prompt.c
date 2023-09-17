/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 21:34:57 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/17 22:04:00 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*short_link(char *cwd, t_m *m)
{
	char	*home;

	home = get_env("HOME", m->env);
	if (!home)
		return (0);
	if (!ft_strncmp(cwd, home, ft_strlen(home)))
		return (&cwd[ft_strlen(home)]);
	return (0);
}

void	get_prompt(t_m *m)
{
	char	*s;

	ft_putstr_fd("minishell:", 1);
	ft_putstr_fd(COLOR_BOLD_BLUE, 1);
	s = short_link(m->cwd, m);
	if (s)
	{
		ft_putchar_fd('~', 1);
		ft_putstr_fd(s, 1);
	}
	else
		ft_putstr_fd(m->cwd, 1);
	ft_putstr_fd(COLOR_OFF, 1);
}
