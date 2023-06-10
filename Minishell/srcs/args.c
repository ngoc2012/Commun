/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/06/10 09:18:16 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_none(void *content)
{
}

char	*parse(char *s, int len, t_m *m)
{
	int		i;
	int		i0;
	char	d;
	char	*s0;
	char	*o;

	o = 0;
	d = ' ';
	i = 0;
	while (s[i] && i < len)
	{
		if (ft_strchr("\"'", s[i]))
		{
			d = s[i++];
			i0 = i;
			while (s[i] && i < len && s[i] != d)
				i++;
			if (s[i] == d)
			{
				s0 = ft_strndup(&s[i0], i - i0);
				o = strjoinm(o, s0, ft_strlen(o), ft_strlen(s0));
				free(s0);
			}
			else
				return (0);
			i++;
		}
		else
		{
			d = ' ';
			i0 = i;
			while (s[i] && i < len && !ft_strchr("\"'", s[i]))
				i++;
			s0 = ft_strndup(&s[i0], i - i0);
			o = strjoinm(o, s0, ft_strlen(o), ft_strlen(s0));
			free(s0);
		}
	}
	return (o);
}

t_list	*args_list(char *s, t_m *m)
{
	int		i;
	int		i0;
	char	d;
	char	*a;
	t_list	*args;
	int	wild;

	wild = 0;
	args = 0;
	d = ' ';
	i0 = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '*')
		{
			wild = 1;
			i++;
		}
		else if (ft_strchr("\"'", s[i]))
		{
			d = s[i];
			while (s[++i] && s[i] != d)
				;
			i++;
		}
		else if (s[i] == ' ')
		{
			if (wild)
				wildcards(ft_strndup(&s[i0], i - i0), &args, m);
			else
				ft_lstadd_back(&args, ft_lstnew(parse(&s[i0], i - i0, m)));
			wild = 0;
			while (s[++i] == ' ')
				;
			i0 = i;
		}
		else
			i++;
	}
	while (s[i - 1] == ' ')
		i--;
	if (i > i0)
	{
		if (wild)
			wildcards(ft_strndup(&s[i0], i - i0), &args, m);
		else
			ft_lstadd_back(&args, ft_lstnew(parse(&s[i0], i - i0, m)));
	}
	return (args);
}

char	**split_args(char *s, t_m *m)
{
	char	**ss0;
	char	**ss;
	t_list	*args0;
	t_list	*args;
	char	*s_env;
	char	*s0;

	while (*s && ft_strchr(" \n", *s))
		s++;
	s_env = str_env(s, ft_strlen(s), m);
	args = args_list(s_env, m);
	free(s_env);
	redir(args, m);
	ss = malloc(sizeof(char *) * (ft_lstsize(args) + 1));
	if (!ss)
		return (0);
	args0 = args;
	ss0 = ss;
	while (args)
	{
		if (!ft_strncmp("<<", (char *)args->content, 2))
		{
			//printf("heredoc |%c|\n", ((char *)args->content)[2]);
			if (((char *)args->content)[2] && ft_strchr("<>|", ((char *)args->content)[2]))
			{
				perror("syntaxe");
				free(ss0);
				ft_lstclear(&args0, free);
				return (0);
			}
			if (((char *)args->content)[2])
				s0 = &((char *) args->content)[2];
			else
			{
				if (!args->next)
					exit(EXIT_FAILURE);
				free(args->content);
				args->content = 0;
				args = args->next;
				s0 = (char *) args->content;
			}
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
			printf("%s", m->heredoc);
			free(m->heredoc);
			m->heredoc = 0;
			free(args->content);
			args->content = 0;
			args = args->next;
			int i = 0;
			m->heredocf = ft_itoa(i);
			m->fin = open(m->heredocf, O_CREAT | O_WRONLY | O_TRUNC, 0664);
			while (m->fin == -1)
			{
				free(m->heredocf);
				m->heredocf = ft_atoi(++i);
				m->fin = open(m->heredocf, O_CREAT | O_WRONLY | O_TRUNC, 0664);
			}
			write(m->fin, m->heredoc, ft_strlen(m->heredoc));
			close(m->fin);
			//m->fin = 0;
			//m->fin = open(m->heredocf, O_RDONLY);
			//if (m->fin == -1)
			//{
			//	perror("open");
			//	m->fin = 0;
			//	free(ss0);
			//	ft_lstclear(&args0, free);
			//	return (0);
			//}
			//m->fin0 = dup(STDIN_FILENO);
			//if (dup2(m->fin, STDIN_FILENO) == -1)
			//{
			//	perror("dup2");
			//	free(args->content);
			//	free_ss(m->args);
			//	free_ss(m->coms);
			//	free(m->pipefd);
			//	exit(EXIT_FAILURE);
			//}
			//close(m->fin);
		}
		else if (((char *)args->content)[0] == '>')
		{
			int	append = 0;
			int	i = 1;

			if (((char *)args->content)[1] == '>')
			{
				append = 1;
				i++;
			}
			if (((char *)args->content)[i])
				s0 = &((char *) args->content)[i];
			else
			{
				if (!args->next)
					exit(EXIT_FAILURE);
				free(args->content);
				args->content = 0;
				args = args->next;
				s0 = (char *) args->content;

			}
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
			if (m->fout == -1)
				exit(EXIT_FAILURE);
			m->fout0 = dup(STDOUT_FILENO);
			if (dup2(m->fout, STDOUT_FILENO) == -1)
			{
				perror("dup2");
				free(args->content);
				free_ss(m->args);
				free_ss(m->coms);
				free(m->pipefd);
				exit(EXIT_FAILURE);
			}
			close(m->fout);
			free(args->content);
			args->content = 0;
			args = args->next;
		}
		else if (((char *)args->content)[0] == '<')
		{
			if (((char *)args->content)[1])
				s0 = &((char *) args->content)[1];
			else
			{
				if (!args->next)
					exit(EXIT_FAILURE);
				free(args->content);
				args->content = 0;
				args = args->next;
				s0 = (char *) args->content;

			}
			if (m->fin)
			{
				m->fin = 0;
				dup2(m->fin0, STDIN_FILENO);
				close(m->fin0);
			}
			m->fin = open(s0, O_RDONLY);
			if (m->fin == -1)
			{
				perror("open");
				m->fin = 0;
				free(ss0);
				ft_lstclear(&args0, free);
				return (0);
			}
			m->fin0 = dup(STDIN_FILENO);
			if (dup2(m->fin, STDIN_FILENO) == -1)
			{
				perror("dup2");
				free(args->content);
				free_ss(m->args);
				free_ss(m->coms);
				free(m->pipefd);
				exit(EXIT_FAILURE);
			}
			close(m->fin);
			free(args->content);
			args->content = 0;
			args = args->next;
		}
		else
		{
			*ss = (char *)args->content;
			args = args->next;
			ss++;
		}
	}
	if (m->heredoc)
		write(0, m->heredoc, ft_strlen(m->heredoc));
	ft_lstclear(&args0, free_none);
	*ss = 0;
	return (ss0);
}

