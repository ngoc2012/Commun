/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/04 18:52:29 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	isenv(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*get_env_name(char *name, char **env)
{
	int	len;

	if (!name)
		return (0);
	if (!(*name))
		return (0);
	while (*env)
	{
		len = 0;
		while ((*env)[len] != '=')
			len++;
		if (!ft_strncmp(*env, name, len))
			if (!isenv(name[len]))
				return (&(*env)[len + 1]);
		env++;
	}
	return (0);
}

char	*str_env(char *s, int len, t_m *m, char del)
{
	int		i0;
	int		i;
	char	*s0;
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
			s0 = get_env_name(&s[++i], m->env);
			o = strjoinm(o, s0, ft_strlen(o), ft_strlen(s0));
			while (s[i] && i < len && isenv(s[i]))
				i++;
			i0 = i;
		}
		else
			i++;
	}
	//printf("|%s, %d, %d|\n", o, i, i0);
	o = strjoinm(o, &s[i0], ft_strlen(o), i - i0);
	return (o);
}
