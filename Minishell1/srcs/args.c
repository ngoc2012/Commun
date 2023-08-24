/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/08/17 12:56:39 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (ft_lstlast(args) && !ft_strncmp("<<", (char *)(ft_lstlast(args))->content, 3))
				wild = 0;
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
			if (!s[i])
			{
				ft_lstclear(&args, free);
				return (0);
			}
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
	while (i && s[i - 1] == ' ')
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
	if (!*s_env)
	{
		m->exit_code = 0;
		free(s_env);
		return (0);
	}
	//printf("s_env = |%s|\n", s_env);
	args = args_list(s_env, m);
	free(s_env);
	if (!args)
	{
		m->exit_code = 2;
		return (0);
	}
	ss = malloc(sizeof(char *) * (ft_lstsize(args) + 1));
	if (!ss)
		return (0);
	*ss = 0;
	m->argc = 0;
	args0 = args;
	ss0 = ss;
	while (args)
	{
		//printf("arg = |%s|\n", (char *)args->content);
		if (!args->content)
		{
			*ss = ft_strdup("");
			ss++;
			m->argc++;
		}
		else if (!ft_strncmp("<<", (char *)args->content, 3))
		{
			if (!heredoc(m, &args, &args0, ss0))
				return (0);
		}
		//else if (((char *)args->content)[0] == '>')
		else if (!ft_strncmp(">", (char *)args->content, 2) || !ft_strncmp(">>", (char *)args->content, 3))
		{
			if (!redir_out(m, &args, &args0, ss0))
				return (0);
		}
		//else if (((char *)args->content)[0] == '<')
		else if (!ft_strncmp("<", (char *)args->content, 2))
		{
			if (!redir_in(m, &args, &args0, ss0))
				return (0);
		}
		else
		{
			*ss = remove_quotes((char *)args->content, ft_strlen((char *)args->content), m);
			m->argc++;
			//free(args->content);
			//printf("*ss %d %s\n", **ss, *ss);
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

