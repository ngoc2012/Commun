/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 21:34:57 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/17 21:50:04 by ngoc             ###   ########.fr       */
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
	ft_strlcpy(prompt, "minishell:", PATH_MAX);
	ft_strlcpy(prompt, COLOR_BOLD_BLUE, PATH_MAX);
	if (short_link(m->cwd, m))
	{
		ft_strlcat(prompt, "~", PATH_MAX);
		ft_strlcat(prompt, short_link(m->cwd, m), PATH_MAX);
	}
	else
		ft_strlcat(prompt, m->cwd, PATH_MAX);
	ft_strlcpy(prompt, COLOR_OFF, PATH_MAX);
	ft_strlcat(prompt, "$ ", PATH_MAX);
}
