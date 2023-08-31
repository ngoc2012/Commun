/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/31 14:42:31 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	start(t_m *m, t_list **cur, char **s0)
{
	int		append;

	append = 0;
	if (!ft_strncmp(">>", (char *)(*cur)->content, 3))
		append = 1;
	(*cur) = (*cur)->next;
	if (!(*cur))
		return (-1);
	*s0 = (char *)(*cur)->content;
	if (!(*cur) || ft_strchr("<>", (*s0)[0])
		|| !ft_strncmp("&", *s0, 2) || m->n_wildcards > 1)
		return (-1);
	(*cur) = (*cur)->next;
	*s0 = remove_quotes(*s0, ft_strlen(*s0), m);
	if (m->fout != 1)
	{
		close(m->fout);
		m->fout = 1;
		if (dup2(m->fout0, STDOUT_FILENO) == -1)
			return (redir_error(m, "redir_out/dup2", 1));
		close(m->fout0);
	}
	return (append);
}

int	redir_out(t_m *m, t_list **cur)
{
	char	*s0;
	int		append;

	s0 = 0;
	append = start(m, cur, &s0);
	if (append == -1)
		return (redir_error(m, "syntax_error", 2));
	if (append)
		m->fout = open(s0, O_CREAT | O_WRONLY | O_APPEND, 0664);
	else
		m->fout = open(s0, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (s0)
		free(s0);
	if (m->fout == -1)
		return (redir_error(m, "open", 1));
	m->fout0 = dup(STDOUT_FILENO);
	if (m->fout0 == -1)
		return (redir_error(m, "dup", 1));
	if (dup2(m->fout, STDOUT_FILENO) == -1)
		return (redir_error(m, "redir_out/dup2", 1));
	return (1);
}
