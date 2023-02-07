/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/02/07 03:24:19 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_stack(t_stack *st)
{
	free(st->ini);
	free(st->cur);
	free(st);
}

t_stack	*new_stack(int *ini, int len)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (0);
	new->len = len;
	new->push = 0;
	new->ini = ini;
	new->cur = malloc(sizeof(t_el) * len);
	if (!new->cur)
		return (0);
	while (len--)
		new->cur[len].v = ini[len];
	new->free = free_stack;
	return (new);
}

int	error(int *ini)
{
	ft_printf("Error\n");
	free(ini);
	return (0);
}

int	check_arg(char *s, int *ini)
{
	int		i;
	char	*s0;
	char	*s1;

	s0 = s;
	while (*s)
	{
		if (!ft_isdigit(*s) && *s != '-')
			return (error(ini));
		s++;
	}
	i = ft_atoi(s0);
	s1 = ft_itoa(i);
	if ((i == 0 && ft_strncmp(s0, "0", 1) != 0)
		|| (ft_strncmp(s1, s0, ft_strlen(s0)) != 0))
	{
		free(s1);
		return (error(ini));
	}
	free(s1);
	return (1);
}

t_stack	*get_args(int argc, char **argv)
{
	int			i;
	int			*ini;
	t_stack		*st;

	ini = malloc(sizeof(int) * (argc - 1));
	if (!ini)
		return (0);
	i = 0;
	while (++i < argc)
	{
		if (!check_arg(argv[i], ini))
			return (0);
		ini[i - 1] = ft_atoi(argv[i]);
	}
	st = new_stack(ini, argc - 1);
	if (!st)
		return (0);
	if (!get_abs_position(st))
	{
		error(ini);
		return (0);
	}
	return (st);
}
