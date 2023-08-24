/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/18 00:59:20 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_in(t_m *m, t_list **args, t_list **args0, char **ss0)
{
	char	*s0;

	(*args) = (*args)->next;
	if (!(*args) || ft_strchr("<>", ((char *)(*args)->content)[0]))
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		m->exit_code = 2;
		ft_lstclear(args0, free);
		return (free_array_str(&ss0, 0));
	}
	//s0 = (char *) (*args)->content;
	s0 = remove_quotes((char *)(*args)->content, ft_strlen((char *)(*args)->content), m);
	//printf("|%s|\n", s0);
	if (m->fin)
	{
		m->fin = 0;
		dup2(m->fin0, STDIN_FILENO);
		close(m->fin0);
	}
	m->fin = open(s0, O_RDONLY);
	if (m->fin == -1)
	{
		if (s0)
			perror(s0);
		else
			perror("minishell: open");
		m->exit_code = 1;
		m->fin = 0;
		ft_lstclear(args0, free);
		if (s0)
			free(s0);
		return (free_array_str(&ss0, 0));
	}
	if (s0)
		free(s0);
	m->fin0 = dup(STDIN_FILENO);
	if (dup2(m->fin, STDIN_FILENO) == -1)
	{
		perror("dup2");
		m->exit_code = 1;
		close(m->fin);
		free_array_str(&ss0, 0);
		ft_lstclear(args0, free);
	}
	close(m->fin);
	free((*args)->content);
	(*args)->content = 0;
	return (1);
}
