/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/02/08 17:23:49 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*st;
	char	*s;
	enum e_ops	o;

	if (argc < 2)
		return (1);
	st = get_args(argc, argv);
	if (!st)
		return (1);
	while ((s = get_next_line(0)))
	{
		if (s[ft_strlen(s) - 1] == '\n')
			s[ft_strlen(s) - 1] = 0;
		o = get_ops(s);
		if (!o)
		{
			free(s);
			st->free(st);
			return (1);
		}
		set_operation(st, o);
		free(s);
	}
	//print_stack(st);
	if (st->push == 0 && relative_ascendant(st, st->push, st->len))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	st->free(st);
	return (0);
}
