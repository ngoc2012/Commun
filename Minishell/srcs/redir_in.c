/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/25 23:25:50 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_error(t_m *m, char *mess, int exit_code)
{
	perror(mess);
	m->exit_code = exit_code;
	free_files(m);
	free_m_arg(m);
	return (0);
}

int	write_file(t_m *m, t_list *args)
{
	char	*s0;

	s0 = remove_quotes((char *)args->content,
			ft_strlen((char *)args->content), m);
	if (m->fin)
	{
		printf("write_file\n");
		close(m->fin);
		m->fin = 0;
		if (dup2(m->fin0, STDIN_FILENO) == -1)
			return (redir_error(m, "redir_in/dup2", 1));
		close(m->fin0);
	}
	m->fin = open(s0, O_RDONLY);
	if (s0)
		free(s0);
	if (m->fin == -1)
		return (redir_error(m, "redir_in/open", 1));
	return (1);
}

int	redir_in(t_m *m, t_list **args)
{
	(*args) = (*args)->next;
	if (!(*args) || ft_strchr("<>", ((char *)(*args)->content)[0]))
		return (redir_error(m, "syntax_error", 2));
	if (!write_file(m, *args))
		return (0);
	m->fin0 = dup(STDIN_FILENO);
	if (m->fin0 == -1)
		return (redir_error(m, "dup", 1));
	if (dup2(m->fin, STDIN_FILENO) == -1)
		return (redir_error(m, "redir_in/dup2", 1));
	free((*args)->content);
	(*args)->content = 0;
	return (1);
}
