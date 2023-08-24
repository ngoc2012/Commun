/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/24 01:38:03 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_file(t_m *m, t_list **args)
{
	char	*s0;

	s0 = remove_quotes((char *)(*args)->content,
			ft_strlen((char *)(*args)->content), m);
	if (m->fin)
	{
		m->fin = 0;
		if (dup2(m->fin0, STDIN_FILENO) == -1)
			exit_error(m, "dup2", 1);
		close(m->fin0);
	}
	m->fin = open(s0, O_RDONLY);
	if (s0)
		free(s0);
	if (m->fin == -1)
		exit_error(m, "open", 1);
}

int	redir_in(t_m *m, t_list **args)
{
	(*args) = (*args)->next;
	if (!(*args) || ft_strchr("<>", ((char *)(*args)->content)[0]))
		return (return_error(m, "syntaxe error", 2, 0));
	write_file(m, args);
	m->fin0 = dup(STDIN_FILENO);
	if (m->fin0 == -1)
		exit_error(m, "dup", 1);
	if (dup2(m->fin, STDIN_FILENO) == -1)
		exit_error(m, "dup2", 1);
	close(m->fin);
	free((*args)->content);
	(*args)->content = 0;
	return (1);
}
