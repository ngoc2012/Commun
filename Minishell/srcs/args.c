/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/07 17:34:08 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_args(char *s)
{
	int		i;
	int		i0;
	int		n;
	char	d;

	n = 0;
	while (*s && *s == ' ')
		s++;
	d = ' ';
	i0 = 0;
	i = 0;
	while (s[i])
	{
		if (ft_strchr("\"'", s[i]))
		{
			d = s[i];
			while (s[++i] && s[i] != d)
				;
			if (s[i] == d)
				d = ' ';
			else
				return (-1);
			i++;
		}
		else if (s[i] == ' ')
		{
			n++;
			while (s[++i] && s[i] == ' ')
				;
			i0 = i;
		}
		else
			i++;
	}
	if (i > i0)
		n++;
	return (n);
}


char	**split_args(char *s)
{
	int		i;
	int		i0;
	int		n_a;
	char	d;
	char	**ss;
	char	**ss0;

	n_a = n_args(s);
	if (!n_a)
		return (0);
	ss = malloc(sizeof(char *) * (n_a + 1));
	ss0 = ss;
	while (*s && ft_strchr(" \n", *s))
		s++;
	d = ' ';
	i0 = 0;
	i = 0;
	while (s[i])
	{
		if (ft_strchr("\"'", s[i]))
		{
			d = s[i];
			while (s[++i] && s[i] != d)
				;
			i++;
		}
		else if (s[i] == ' ')
		{
			*ss = malloc(i - i0 + 1);
			ft_memcpy(*ss, &s[i0], i - i0);
			(*ss)[i - i0] = 0;
			ss++;
			while (s[++i] && s[i] == ' ')
				;
			i0 = i;
		}
		else
			i++;
	}
	if (i > i0)
	{
		*ss = malloc(i - i0 + 1);
		ft_memcpy(*ss, &s[i0], i - i0);
		(*ss)[i - i0] = 0;
		ss++;
	}
	*ss = 0;
	return (ss0);
}

char	*parse(char *s, t_m *m)
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
	while (s[i])
	{
		if (ft_strchr("\"'", s[i]))
		{
			d = s[i++];
			i0 = i;
			while (s[i] && s[i] != d)
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
			while (s[i] && s[i] != '"' && s[i] != '\'')
			//{
			//	if (ft_strchr(sp, s[i]))
			//		return (0);
				i++;
			//}
			s0 = str_env(&s[i0], i - i0, m, d);
			o = strjoinm(o, s0, ft_strlen(o), ft_strlen(s0));
			free(s0);
		}
	}
	return (o);
}
