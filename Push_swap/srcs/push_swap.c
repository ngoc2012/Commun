/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/03/01 11:51:52 by minh-ngu         ###   ########.fr       */
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
	{
		free(new);
		return (0);
	}
	while (len--)
		new->cur[len].v = ini[len];
	new->free = free_stack;
	return (new);
}

void	arg_error(int *ini)
{
	ft_printf("Error\n");
	free(ini);
	exit(EXIT_FAILURE);
}

int	get_arg(char *s, int *ini)
{
	int		i;
	char	*s0;
	char	*s1;

	s0 = s;
	while (*s)
	{
		if (!ft_isdigit(*s) && *s != '-')
			arg_error(ini);
		s++;
	}
	i = ft_atoi(s0);
	s1 = ft_itoa(i);
	if ((i == 0 && s0[0] == 0)
		|| (i < 0 && ft_strncmp(s1, s0, ft_strlen(s0)) != 0))
	{
		free(s1);
		arg_error(ini);
	}
	free(s1);
	return (ft_atoi(s0));
}

t_stack	*get_args(int argc, char **argv)
{
	int			i;
	int			*ini;
	t_stack		*st;

	ini = malloc(sizeof(int) * (argc - 1));
	if (!ini)
		exit(EXIT_FAILURE);
	i = 0;
	while (++i < argc)
		ini[i - 1] = get_arg(argv[i], ini);
	st = new_stack(ini, argc - 1);
	if (!st)
		return (0);
	if (!get_abs_position(st))
	{
		st->free(st);
		ft_printf("Error\n");
		exit(EXIT_FAILURE);
	}
	return (st);
}
