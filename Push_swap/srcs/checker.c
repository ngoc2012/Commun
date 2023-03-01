/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/03/01 11:37:42 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	get_input(t_stack *st)
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
			ft_printf("Error\n");
			free(s);
			st->free(st);
			exit(EXIT_FAILURE);
		}
		set_operation(st, o, 0);
		free(s);
		s = get_next_line(0);
	}
}

int	main(int argc, char **argv)
{
	t_stack	*st;

	if (argc <= 2)
		exit(EXIT_SUCCESS);
	st = get_args(argc, argv);
	get_input(st);
	if (st->push == 0 && ascendant(st, st->push, st->len))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	st->free(st);
	exit(EXIT_SUCCESS);
}
