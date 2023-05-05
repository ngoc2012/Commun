/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:45:00 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/04 15:29:45 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ECHO_DEL 2

typedef struct	s_echo
{
	char	*s;
	char	*o;
	char	*del;
	int		pos[ECHO_DEL];
	int		space;
	int		len_o;
	t_m	*m;
}	t_echo;

static void	print(char *s, int len, t_echo *e, char del)
{
	char	*s0 = str_env(s, len, e->m, del);
	if (s0)
	{
		ft_putstr_fd(s0, 1);
		free(s0);
	}
}

//static void	print(char *s, int len, t_echo *e, int type)
//{
//	int		i;
//	char	*s0;
//
//	if (len <= 0)
//		return ;
//	i = -1;
//	while (++i < len)
//	{
//		if (type != 0 && (!(s[i] == '$' && i == len - 1)))
//		{
//			if (s[i] == '$' && s[i + 1] == '?')
//			{
//				ft_putnbr_fd(e->m->exit_code, 1);
//				i += 2;
//			}
//			else if (s[i] == '$' && s[i + 1] != ' ')
//			{
//				s0 = get_env_name(&s[i + 1], e->m->env);
//				ft_putstr_fd(s0, 1);
//				i++;
//				while (s[i] && s[i] != ' ' && s[i] != '"' && s[i] != '\n')
//					i++;
//			}
//		}
//		if (i < len)
//			write(1, &s[i], 1);
//	}
//}

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
		print(&e->s[e->space], i - e->space, e, ' ');
	e->space = i;
}

// print delimiter
static int	print_del(t_echo *e, int i, int j, int pos_min)
{
	int	k;

	if (pos_min == e->pos[j])
	{
		print(&e->s[e->pos[j] + 1], i - e->pos[j] - 1, e, e->del[j]);
		e->space = i + 1;
		k = -1;
		while (++k < ECHO_DEL)
			e->pos[k] = -1;
		if (e->s[i + 1] == ' ')
		{
			write(1, " ", 1);
			while (e->s[++i] == ' ')
				e->space = i + 1;
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
				if (i > e->space)
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

// check if we need more line
static int	check_end(t_echo *e, int *i)
{
	int	j;
	int	k;
	int	pos_min;

	while (e->s[*i])
	{
		j = -1;
		while (++j < ECHO_DEL)
			if (e->s[*i] == e->del[j])
			{
				if (e->pos[j] == -1)
					e->pos[j] = *i;
				else
				{
					pos_min = e->pos[j];
					k = -1;
					while (++k < ECHO_DEL)
						if (e->pos[k] != -1 && e->pos[k] < pos_min)
							pos_min = e->pos[k];
					if (pos_min == e->pos[j])
					{
						k = -1;
						while (++k < ECHO_DEL)
							e->pos[k] = -1;
						break ;
					}
				}
			}
		(*i)++;
	}
	j = -1;
	while (++j < ECHO_DEL)
		if (e->pos[j] != -1)
			return (0);
	return (1);
}

void	echo(t_m *m, char **args)
{
	int		i;
	int		nl;
	char	*s;
	t_echo	e;

	nl = 1;
	e.m = m;
	e.s = 0;
	e.len_o = 0;
	e.del = "'\"";
	s = ft_strnstr(command, "echo", ft_strlen(command)) + 4;
	while (*s == ' ')
		s++;
	if (*s == '-')
		if (*(s + 1) == 'n')
		{
			nl = 0;
			s += 2;
			while (*s == ' ')
				s++;
		}
	if (*s != 0)
	{
		e.s = strjoinm(e.s, s, 0, ft_strlen(s));
		i = -1;
		while (++i < ECHO_DEL)
			e.pos[i] = -1;
		i = 0;
		while (!check_end(&e, &i))
		{
			s = readline("> ");
			e.s = strjoinm(e.s, "\n", i++, 1);
			e.s = strjoinm(e.s, s, i, ft_strlen(s));
		}
		i = -1;
		while (++i < ECHO_DEL)
			e.pos[i] = -1;
		e.space = 0;
		i = -1;
		while (e.s[++i])
		{
			if (e.s[i] == ' ' && e.space < i)
			{
				print_space(&e, i);
				while (e.s[++i] == ' ')
					e.space = i;
			}
			check_del(&e, i);
		}
		if (i > e.space)
			print_space(&e, i);
		m->exit_code = 0;
		free(e.s);
	}
	if (nl)
		write(1, "\n", 1);
}
