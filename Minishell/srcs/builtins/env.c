/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/14 17:12:49 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	isenv(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*str_env(char *s, int len, t_m *m, char del)
{
	int		i0;
	int		i;
	char	*s0;
	char	*s1;
	char	*o;

	if (len <= 0)
		return (0);
	o = 0;
	if (del == '\'')
		return (strjoinm(o, s, 0, len));
	i = 0;
	i0 = i;
	while (i < len)
	{
		if (s[i] == '$' && s[i + 1] == '?')
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
			i0 = ++i;
			while (s[i] && i < len && isenv(s[i]))
				i++;
			s0 = ft_strndup(&s[i0], i - i0);
			s1 = getenv(s0);
			o = strjoinm(o, s1, ft_strlen(o), ft_strlen(s1));
			free(s0);
			i0 = i;
		}
		else
			i++;
	}
	o = strjoinm(o, &s[i0], ft_strlen(o), i - i0);
	return (o);
}
