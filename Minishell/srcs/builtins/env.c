/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/07/28 12:35:54 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	isenv(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*get_env(char *s, t_m *m)
{
	t_list *cur;

	cur = m->envs;
	while (cur)
	{
		if (!ft_strdcmp(cur->content, s))
			return (&((char *)cur->content)[chr_pos(cur->content, '=') + 1]);
			//return (&((char *)cur->content)[chr_pos(cur->content, '=') + 1]);
		cur = cur->next;
	}
	return (getenv(s));
}

char	*str_env(char *s, int len, t_m *m)
{
	int		i0;
	int		i;
	char	*s0;
	char	*s1;
	char	*o;
	char	d;
	int	in_double_quotes;

	if (len <= 0)
		return (0);
	o = 0;
	i = 0;
	i0 = i;
	in_double_quotes = 0;
	while (s[i] && i < len)
	{
		if (s[i] == '\"')
		{
			if (in_double_quotes)
				in_double_quotes = 0;
			else
				in_double_quotes = 1;
		}
		//else if (s[i] == '\'' && !in_double_quotes)
		if (s[i] == '\'' && !in_double_quotes)
		{
			o = strjoinm(o, &s[i0], ft_strlen(o), i - i0);
			i0 = i;
			d = s[i++];
			while (s[i] && i < len && s[i] != d)
				i++;
			if (s[i] == d)
				o = strjoinm(o, &s[i0], ft_strlen(o), i - i0 + 1);
			else
				return (0);
			i++;
			i0 = i;
		}
		else if (s[i] == '\\' && s[i + 1] && !ft_strchr(" 	\n", s[i + 1]))
		{
			o = strjoinm(o, &s[i0], ft_strlen(o), i - i0);
			i++;
			o = strjoinm(o, &s[i], ft_strlen(o), 1);
			i++;
			i0 = i;
		}
		else if (s[i] == '$' && s[i + 1] == '?')
		{
			o = strjoinm(o, &s[i0], ft_strlen(o), i - i0);
			s0 = ft_itoa(m->exit_code);
			o = strjoinm(o, s0, ft_strlen(o), ft_strlen(s0));
			free(s0);
			i += 2;
			i0 = i;
		}
		else if (s[i] == '$' && isenv(s[i + 1]))
		{
			o = strjoinm(o, &s[i0], ft_strlen(o), i - i0);
			if (ft_isdigit(s[i + 1]))
				i += 2;
			else
			{
				i0 = ++i;
				while (s[i] && i < len && isenv(s[i]))
					i++;
				s0 = ft_strndup(&s[i0], i - i0);
				s1 = get_env(s0, m);
				o = strjoinm(o, s1, ft_strlen(o), ft_strlen(s1));
				free(s0);
			}
			i0 = i;
		}
		else
			i++;
	}
	o = strjoinm(o, &s[i0], ft_strlen(o), i - i0);
	return (o);
}
