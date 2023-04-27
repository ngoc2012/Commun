/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/27 00:01:34 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define ECHO_DEL 2

typedef struct	s_echo
{
	char	*s;
	char	*del;
	int	pos[ECHO_DEL];
	int	space;
	t_m	*m;
}	t_echo;

static int	get_env_name(char *name, char **environ)
{
	int	len;

	for (char **env = environ; *env != NULL; env++) {
		len = 0;
		while ((*env)[len] != '=')
			len++;
		if (!ft_strncmp(*env, name, len))
		{
			if (name[len] == ' ' || name[len] == '"')
				ft_putstr_fd(&(*env)[len + 1], 1);
			while (name[len] && name[len] != ' ' && name[len] != '"')
				len++;
			return (len);
		}
	}
	return (0);
}

static void	print(char *s, int len, t_echo *e, int type)
{
	int	i;

	if (len <= 0)
		return ;
	i = -1;
	while (++i < len)
	{
		if (type != 0 && (!(s[i] == '$' && i == len - 1)))
		{
			if (s[i] == '$' && s[i + 1] == '?')
			{
				ft_putnbr_fd(e->m->exit_code, 1);
				i += 2;
			}
			else if (s[i] == '$' && s[i + 1] != ' ')
				i += get_env_name(&s[i + 1], e->m->env) + 1;
		}
		if (i < len)
			write(1, &s[i], 1);
	}
}

static void	print_space(t_echo *e, int i)
{
	int	j;
	int	k;

	j = 1;
	k = -1;
	while (++k < ECHO_DEL)
		if (e->pos[k] != -1)
			j = 0;
	if (j)
		print(&e->s[e->space], i - e->space, e, 2);
	e->space = i;
}

// print delimiter
static int	print_del(t_echo *e, int i, int j, int pos_min)
{
	int	k;

	if (pos_min == e->pos[j])
	{
		//write(1, "y", 1);
		print(&e->s[e->pos[j] + 1], i - e->pos[j] - 1, e, j);
		e->space = i + 1;
		k = -1;
		while (++k < ECHO_DEL)
			e->pos[k] = -1;
		if (e->s[i + 1] == ' ')
		{
			write(1, " ", 1);
			i++;
			e->space = i;
			while (e->s[i + 1] == ' ')
			{
				i++;
				e->space = i;
			}
		}
		return (1);
	}
	return (0);
}

// check delimiter to print
static void	check_del(t_echo *e, int i)
{
	int	j;
	int	k;
	int	pos_min;

	j = -1;
	while (++j < ECHO_DEL)
		if (e->s[i] == e->del[j])
		{
			if (e->pos[j] == -1)
			{
				if (i - 1 > e->space)
					print_space(e, i);
				e->pos[j] = i;
			}
			else
			{
				pos_min = e->pos[j];
				k = -1;
				while (++k < ECHO_DEL)
					if (e->pos[k] != -1 && e->pos[k] < pos_min)
						pos_min = e->pos[k];
				if (print_del(e, i, j, pos_min))
					break ;
			}
		}
}

void	echo(t_m *m, char *command)
{
	int	i;
	t_echo	e;

	e.m = m;
	e.del = "'\"";
	i = -1;
	while (++i < ECHO_DEL)
		e.pos[i] = -1;
	e.space = 0;
	e.s = ft_strnstr(command, "echo", ft_strlen(command)) + 5;
	i = -1;
	while (e.s[++i])
	{
		if (e.s[i] == ' ' && e.space > i)
			print_space(&e, i);
		check_del(&e, i);
	}
	if (i > e.space)
		print_space(&e, i);
	m->exit_code = 0;
	write(1, "\n", 1);
}
