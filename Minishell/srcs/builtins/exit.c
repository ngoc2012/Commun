/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:56:51 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/16 07:20:35 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

static char	*get_sign(char *str, int *sign)
{
	*sign = 1;
	while (ft_strchr(" 	", *str))
		str++;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			*sign = -1;
	return (str);
}

static int	number_2_exit_code(char *str)
{
	int	n;
	int	sign;

	n = 0;
	str = get_sign(str, &sign);
	if (!str)
		return (-1);
	while (*str)
	{
		if (*str >= 48 && *str <= 57)
		{
			n *= 10;
			n += *str - 48;
			while (n > 256)
				n -= 256;
		}
		else
			return (-1);
		str++;
	}
	if (sign == -1)
		return (256 - n);
	else
		return (n);
}

static int	get_big_num(char *str, int *n)
{
	int	i;

	i = 0;
	*n = 0;
	while (*str)
	{
		if (*str >= 48 && *str <= 57)
		{
			*n *= 10;
			*n += *str - 48;
			while (*n >= 256)
			{
				*n -= 256;
				i++;
			}
		}
		else
			return (0);
		str++;
	}
	return (i);
}

static int	is_max_long_long(char *str)
{
	int	i;
	int	n;
	int	sign;

	str = get_sign(str, &sign);
	if (!str)
		return (0);
	i = get_big_num(str, &n);
	if (sign == -1 && i >= 92 && n > 0)
		return (1);
	if (sign == 1 && i >= 92 && n > -1)
		return (1);
	return (0);
}

int	builtin_exit(t_m *m)
{
	if (m->n_pipes == 1)
		ft_putstr_fd("exit\n", 1);
	if (m->argc > 1)
	{
		g_exit_code = number_2_exit_code(m->args[1]);
		if (g_exit_code == -1 || is_max_long_long(m->args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(m->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			g_exit_code = 2;
			if (m->n_pipes == 1)
				exit_error(m, 0, g_exit_code);
		}
	}
	if (m->argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_exit_code = 1;
		return (1);
	}
	if (m->n_pipes == 1)
		exit_error(m, 0, g_exit_code);
	return (1);
}
