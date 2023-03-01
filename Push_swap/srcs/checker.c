/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/02/28 18:19:15 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_input(t_stack *st)
{
	enum e_ops	o;
	char		*s;

	s = get_next_line(0);
	while (s)
	{
		if (s[ft_strlen(s) - 1] == '\n')
			s[ft_strlen(s) - 1] = 0;
		else
			ft_printf("\n");
		o = get_ops(s);
		if (!o)
		{
			free(s);
			ft_printf("Error\n");
			return (0);
		}
		set_operation(st, o, 0);
		free(s);
		s = get_next_line(0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_stack	*st;

	if (argc <= 2)
		return (0);
	st = get_args(argc, argv);
	if (!st)
		return (1);
	if (!get_input(st))
	{
		st->free(st);
		return (1);
	}
	if (st->push == 0 && ascendant(st, st->push, st->len))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	st->free(st);
	return (0);
}
