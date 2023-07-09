/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/07/08 18:11:49 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Get number of strings at the out put, must be 0 if all match
static int	get_n_strs(const char *str, char charset)
{
	int		i;
	int		n_strs;
	char	d;

	i = 0;
	n_strs = 0;
	while (str[i])
	{
		while (str[i] && str[i] == charset)
			i++;
		if (str[i])
			n_strs++;
		while (str[i] && !(str[i] == charset))
		{
			if (ft_strchr("\"\'", str[i]))
			{
				d = str[i];
				//printf("%c %d", d, i);
				i++;
				while (str[i] != d)
					i++;
				//printf(" %d\n", i);
			}
			i++;
		}
	}
	return (n_strs);
}

// Get chunks (begin and end) of string to output
static int	get_strs(const char *str, char charset, char **out)
{
	int		i;
	int		start;
	int		j;
	char	d;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == charset)
			i++;
		start = i;
		while (str[i] && !(str[i] == charset))
		{
			if (ft_strchr("\"\'", str[i]))
			{
				d = str[i];
				//printf("%c\n", d);
				i++;
				while (str[i] != d)
					i++;
			}
			i++;
		}
		if (i > start)
		{
			out[j] = malloc(sizeof(char) * (i - start + 1));
			if (!out[j])
				return (0);
			ft_strlcpy(out[j], &(str[start]), i - start + 1);
			j++;
		}
	}
	return (1);
}

char	**ft_split2(const char *str, char charset)
{
	int		n_strs;
	char	**out;
	char	**out0;

	n_strs = get_n_strs(str, charset);
	//printf("%d\n", n_strs);
	out = malloc(sizeof(char *) * (n_strs + 1));
	if (!out)
		return (0);
	//printf("%d\n", n_strs);
	if (n_strs > 0)
	{
		if (!get_strs(str, charset, out))
		{
			out0 = out;
			while (*out)
				free(*(out++));
			free(out0);
			return (0);
		}
	}
	out[n_strs] = 0;
	return (out);
}
/*
Execute a command with or without pipe.
A command is a string between between || ; and &&.
*/
int	pipes(char *s, t_m *m)
{
	int		i;
	int		j;
	int		n;
	pid_t	pid;

	//printf("s = %s\n", s);
	m->coms = ft_split2(s, '|');
	if (!m->coms)
		return (0);
	n = -1;
	while (m->coms[++n])
		;
	if (n > 1)
		pipe(m->pipefd0);
	if (n > 2)
		pipe(m->pipefd1);
	i = -1;
	while (++i < n)
	{
		//printf("i = %d\n", i);
		m->args = split_args(m->coms[i], m);
		if (!m->args || !(*m->args))
		{
			free_ss(m->args);
			break ;
		}
		if (!builtins(m, i, n))
			process(m, i, n);
		free_ss(m->args);
	}
	free_ss(m->coms);
	if (m->fout != 1 && m->fout)
	{
		m->fout = 1;
		dup2(m->fout0, STDOUT_FILENO);
		close(m->fout0);
	}
	if (m->heredocf)
	{
		unlink(m->heredocf);
		free(m->heredocf);
		m->heredocf = 0;
	}
	if (m->fin)
	{
		m->fin = 0;
		dup2(m->fin0, STDIN_FILENO);
		close(m->fin0);
	}
	return (1);
}

