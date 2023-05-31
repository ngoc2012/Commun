/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/30 22:21:53 by ngoc             ###   ########.fr       */
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
		if (args->content[0] == '>')
		{
			char	*s0;
			args = args->next;
			if (args->content)
				s0 = args->content[1];
			else
			{
				if (!args->next)
					exit(EXIT_FAILURE);
				else
					s0 = args->next->content;

			}
			//if (m->fout != -1)
			//	close(m->fout);
			m->fout = open(s0, O_CREAT | O_WRONLY | O_TRUNC);
			if (m->fout == -1)
				exit(EXIT_FAILURE);
			dup2(m->fout, STDOUT_FILENO);
			close(m->fout);
		}
		else
		{
			*ss = (char *)args->content;
			args = args->next;
			ss++;
		}
	}
	ft_lstclear(&args0, free_none);
	*ss = 0;
	return (ss0);
}

