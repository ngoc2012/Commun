/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:52:59 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/05 13:53:23 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
