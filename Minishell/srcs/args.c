/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/07/29 15:27:53 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_none(void *content)
{
}

char	*remove_quotes(char *s, int len, t_m *m)
{
	int		i;
	int		i0;
	char	d;
	char	*o;

	o = 0;
	d = ' ';
	i = 0;
	i0 = i;
	//printf("before remove quotes|%s|\n", s);
	while (s[i] && i < len)
	{
		if (ft_strchr("\"'", s[i]))
		{
			if (i > i0)
				o = strjoinm(o, &s[i0], ft_strlen(o), i - i0);
			d = s[i++];
			i0 = i;
			while (s[i] && i < len && s[i] != d)
				i++;
			if (s[i] == d)
			{
				if (i > i0)
					o = strjoinm(o, &s[i0], ft_strlen(o), i - i0);
			}
			else
				return (0);
			i++;
			i0 = i;
		}
		else
		{
			while (s[i] && i < len && !ft_strchr("\"'", s[i]))
				i++;
			if (i > i0)
				o = strjoinm(o, &s[i0], ft_strlen(o), i - i0);
			i0 = i;
		}
	}
	return (o);
}

// Ignore space in "" and ''
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
		else if (ft_strchr("<>", s[i]))
		{
			d = s[i];
			if (i > i0)
				ft_lstadd_back(&args, ft_lstnew(strjoinm(0, &s[i0], 0, i - i0)));
			i++;
			if (s[i] == d)
			{
				if (d == '>')
					ft_lstadd_back(&args, ft_lstnew(ft_strdup(">>")));
				else
					ft_lstadd_back(&args, ft_lstnew(ft_strdup("<<")));
				i++;
			}
			else
			{
				if (d == '>')
					ft_lstadd_back(&args, ft_lstnew(ft_strdup(">")));
				else
					ft_lstadd_back(&args, ft_lstnew(ft_strdup("<")));
			}
			i0 = i;
		}
		else if (ft_strchr("\"'", s[i]))
		{
			d = s[i];
			while (s[++i] && s[i] != d)
				;
			i++;
		}
		else if (ft_strchr(" 	", s[i]))
		//else if (s[i] == ' ')
		{
			if (i > i0)
			{
				if (wild)
					wildcards(ft_strndup(&s[i0], i - i0), &args, m);
				else if (i > i0)
					ft_lstadd_back(&args, ft_lstnew(strjoinm(0, &s[i0], 0, i - i0)));
			}
			wild = 0;
			while (ft_strchr(" 	", s[++i]))
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
			ft_lstadd_back(&args, ft_lstnew(strjoinm(0, &s[i0], 0, i - i0)));
			//ft_lstadd_back(&args, ft_lstnew(remove_quotes(&s[i0], i - i0, m)));
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
	//printf("before str_env = |%s|\n", s);
	s_env = str_env(s, ft_strlen(s), m);
	//printf("s_env = |%s|\n", s_env);
	args = args_list(s_env, m);
	free(s_env);
	ss = malloc(sizeof(char *) * (ft_lstsize(args) + 1));
	if (!ss)
		return (0);
	*ss = 0;
	args0 = args;
	ss0 = ss;
	while (args)
	{
		//printf("arg = |%s|\n", (char *)args->content);
		if (!args->content)
		{
			*ss = ft_strdup("");
			ss++;
		}
		else if (!ft_strncmp("<<", (char *)args->content, 3))
		{
			args = args->next;
			//printf("heredoc |%c|\n", ((char *)args->content)[2]);
			if (!args || ft_strchr("<>|", ((char *)args->content)[0]))
			{
				ft_putstr_fd("minishell: syntaxe\n", 2);
				m->exit_code = 2;
				free_ss(ss0);
				ft_lstclear(&args0, free);
				return (0);
			}
			s0 = remove_quotes((char *)args->content, ft_strlen((char *)args->content), m);
			//s0 = (char *) args->content;
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
				free_ss(ss0);
				ft_lstclear(&args0, free);
				return (0);
			}
			m->fin0 = dup(STDIN_FILENO);
			if (dup2(m->fin, STDIN_FILENO) == -1)
			{
				perror("dup2");
				m->exit_code = 1;
				close(m->fin);
				free_ss(ss0);
				ft_lstclear(&args0, free);
				return (0);
			}
			close(m->fin);
			free(args->content);
			args->content = 0;
		}
		//else if (((char *)args->content)[0] == '>')
		else if (!ft_strncmp(">", (char *)args->content, 2) || !ft_strncmp(">>", (char *)args->content, 3))
		{
			int	append = 0;
			if (!ft_strncmp(">>", (char *)args->content, 3))
				append = 1;
			args = args->next;
			if (!args || ft_strchr("<>", ((char *)args->content)[0]))
			{
				ft_putstr_fd("minishell: syntax error\n", 2);
				m->exit_code = 2;
				free_ss(ss0);
				ft_lstclear(&args0, free);
				return (0);
			}
			//s0 = (char *) args->content;
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
			{
				perror("minishell: open");
				m->exit_code = 1;
				free_ss(ss0);
				ft_lstclear(&args0, free);
				return (0);
			}
			m->fout0 = dup(STDOUT_FILENO);
			if (dup2(m->fout, STDOUT_FILENO) == -1)
			{
				perror("dup2");
				m->exit_code = 1;
				close(m->fin);
				free_ss(ss0);
				ft_lstclear(&args0, free);
				return (0);
			}
			close(m->fout);
			free(args->content);
			args->content = 0;
		}
		//else if (((char *)args->content)[0] == '<')
		else if (!ft_strncmp("<", (char *)args->content, 2))
		{
			args = args->next;
			if (!args || ft_strchr("<>", ((char *)args->content)[0]))
			{
				ft_putstr_fd("minishell: syntax error\n", 2);
				m->exit_code = 2;
				free_ss(ss0);
				ft_lstclear(&args0, free);
				return (0);
			}
			//s0 = (char *) args->content;
			s0 = remove_quotes((char *)args->content, ft_strlen((char *)args->content), m);
			//printf("|%s|\n", s0);
			if (m->fin)
			{
				m->fin = 0;
				dup2(m->fin0, STDIN_FILENO);
				close(m->fin0);
			}
			m->fin = open(s0, O_RDONLY);
			if (s0)
				free(s0);
			if (m->fin == -1)
			{
				perror("open");
				m->exit_code = 1;
				m->fin = 0;
				free_ss(ss0);
				ft_lstclear(&args0, free);
				return (0);
			}
			m->fin0 = dup(STDIN_FILENO);
			if (dup2(m->fin, STDIN_FILENO) == -1)
			{
				perror("dup2");
				m->exit_code = 1;
				close(m->fin);
				free_ss(ss0);
				ft_lstclear(&args0, free);
			}
			close(m->fin);
			free(args->content);
			args->content = 0;
		}
		else
		{
			*ss = remove_quotes((char *)args->content, ft_strlen((char *)args->content), m);
			//free(args->content);
			//printf("%s,", *ss);
			ss++;
			*ss = 0;
		}
		args = args->next;
	}
	if (m->heredoc)
		write(0, m->heredoc, ft_strlen(m->heredoc));
	//ft_lstclear(&args0, free_none);
	ft_lstclear(&args0, free);
	*ss = 0;
	return (ss0);
}

