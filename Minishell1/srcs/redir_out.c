/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/17 16:01:03 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_error(t_m *m, t_list **args0, char **ss0, int exit_code)
{
	if (exit_code == 1)
		perror("minishell: open");
	if (exit_code == 2)
		ft_putstr_fd("minishell: syntax error\n", 2);
	m->exit_code = exit_code;
	ft_lstclear(args0, free);
	return (free_array_str(&ss0, 0));
}

static int	start(t_m *m, t_list **args, t_list **args0, char **ss0)
{
	char	*s0;
	int		append;

	append = 0;
	if (!ft_strncmp(">>", (char *)(*args)->content, 3))
		append = 1;
	(*args) = (*args)->next;
	if (!(*args))
		return (redir_error(m, args0, ss0, 2));
	s0 = (char *)(*args)->content;
	if (!(*args) || ft_strchr("<>", s0[0])
		|| !ft_strncmp("&", s0, 2) || m->n_wildcards > 1)
		return (redir_error(m, args0, ss0, 2));
	s0 = remove_quotes(s0, ft_strlen(s0), m);
	if (m->fout != 1)
	{
		m->fout = 1;
		dup2(m->fout0, STDOUT_FILENO);
		close(m->fout0);
	}
	if (append)
		m->fout = open(s0, O_CREAT | O_WRONLY | O_APPEND, 0664);
	else
		m->fout = open(s0, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (s0)
		free(s0);
	return (1);
}

int	redir_out(t_m *m, t_list **args, t_list **args0, char **ss0)
{
	if (!start(m, args, args0, ss0))
		return (0);
	if (m->fout == -1)
		return (redir_error(m, args0, ss0, 1));
	m->fout0 = dup(STDOUT_FILENO);
	if (dup2(m->fout, STDOUT_FILENO) == -1)
		return (redir_error(m, args0, ss0, 1));
	close(m->fout);
	free((*args)->content);
	(*args)->content = 0;
	return (1);
}
