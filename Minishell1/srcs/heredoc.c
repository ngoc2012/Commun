/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/18 01:05:00 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_doc(t_m *m, t_list **args, t_list **args0, char *s0)
{
	if (m->heredoc)
	{
		free(m->heredoc);
		m->heredoc = 0;
	}
	while (1)
	{
		char	*com;
		com = readline("> ");
		if (!ft_strncmp(com, s0, ft_strlen(s0) + 1))
			break ;
		m->heredoc = strjoinm(m->heredoc, com, ft_strlen(m->heredoc), ft_strlen(com));
		m->heredoc = strjoinm(m->heredoc, "\n", ft_strlen(m->heredoc), 1);
	}
	if (s0)
		free(s0);
}

int	heredoc(t_m *m, t_list **args, t_list **args0, char **ss0)
{
	char	*s0;

	(*args) = (*args)->next;
	if (!(*args) || ft_strchr("<>|", ((char *)(*args)->content)[0]))
	{
		ft_putstr_fd("minishell: syntaxe\n", 2);
		m->exit_code = 2;
		ft_lstclear(args0, free);
		return (free_array_str(&ss0, 0));
	}
	s0 = remove_quotes((char *)(*args)->content, ft_strlen((char *)(*args)->content), m);
	get_doc(m, args, args0, s0);
	//s0 = (char *) (*args)->content;
	//printf("%s", m->heredoc);
	int i = 0;
	m->heredocf = ft_itoa(i);
	while (access(m->heredocf, F_OK) != -1 && i < 100)
	{
		free(m->heredocf);
		m->heredocf = ft_itoa(++i);
	}
	m->fin = open(m->heredocf, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	write(m->fin, m->heredoc, ft_strlen(m->heredoc));
	free(m->heredoc);
	m->heredoc = 0;
	close(m->fin);
	m->fin = 0;
	m->fin = open(m->heredocf, O_RDONLY);
	if (m->fin == -1)
	{
		perror("open");
		m->exit_code = 1;
		m->fin = 0;
		ft_lstclear(args0, free);
		return (free_array_str(&ss0, 0));
	}
	m->fin0 = dup(STDIN_FILENO);
	if (dup2(m->fin, STDIN_FILENO) == -1)
	{
		perror("dup2");
		m->exit_code = 1;
		close(m->fin);
		ft_lstclear(args0, free);
		return (free_array_str(&ss0, 0));
	}
	close(m->fin);
	free((*args)->content);
	(*args)->content = 0;
	return (1);
}
