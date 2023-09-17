/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 21:34:57 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/17 22:14:19 by ngoc             ###   ########.fr       */
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

void	get_prompt(t_m *m, char *prompt)
{
	char	*s;

	ft_strlcpy(prompt, COLOR_BOLD_GREEN, PATH_MAX);
	ft_strlcat(prompt, "minishell:", PATH_MAX);
	ft_strlcat(prompt, COLOR_BOLD_CYAN, PATH_MAX);
	s = short_link(m->cwd, m);
	if (s)
	{
		ft_strlcat(prompt, "~", PATH_MAX);
		ft_strlcat(prompt, s, PATH_MAX);
	}
	else
		ft_strlcat(prompt, m->cwd, PATH_MAX);
	ft_strlcat(prompt, COLOR_OFF, PATH_MAX);
	ft_strlcat(prompt, "$ ", PATH_MAX);
}
