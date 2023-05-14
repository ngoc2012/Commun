/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/14 17:42:30 by ngoc             ###   ########.fr       */
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
	//const char	*sp;

	//sp = "`\\?[]{}()";
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
				s0 = str_env(&s[i0], i - i0, m, d);
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
			s0 = str_env(&s[i0], i - i0, m, d);
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
				wildcards(parse(&s[i0], i - i0, m), &args, m);
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
	printf("args.c 1:%s\n", s);
	while (s[i - 1] == ' ')
		i--;
	if (i > i0)
	{
		if (wild)
			wildcards(parse(&s[i0], i - i0, m), &args, m);
		else
			ft_lstadd_back(&args, ft_lstnew(parse(&s[i0], i - i0, m)));
	}
	printf("args.c 2:%s\n", s);
	return (args);
}

char	**split_args(char *s, t_m *m)
{
	char	**ss0;
	char	**ss;
	t_list	*args0;
	t_list	*args;

	while (*s && ft_strchr(" \n", *s))
		s++;
	args = args_list(s, m);
	printf("args.c 3:%s\n", s);
	ss = malloc(sizeof(char *) * (ft_lstsize(args) + 1));
	if (!ss)
		return (0);
	args0 = args;
	ss0 = ss;
	while (args)
	{
		*ss = (char *)args->content;
		args = args->next;
		ss++;
	}
	//ft_lstiter(args0, print_content);
	ft_lstclear(&args0, free_none);
	*ss = 0;
	return (ss0);
}

