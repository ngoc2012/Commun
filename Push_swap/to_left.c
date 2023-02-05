/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_left.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/02/05 07:35:29 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	to_left(t_stack *st, int last, int last1, int set_rrr)
{
	int	max_b;
	int	right;

	max_b = st->push;
	while (st->push != max_b - last * 2)
	{
		rot_next_b(st, max_b - last * 2);
		ft_printf("pa\n");
		st->push--;
		if (st->cur[st->push].a_p < max_b - last && st->cur[st->push + 1].a_p >= max_b - last)
		{
			ft_printf("ra\n");
			set_operation(st, ra);
		}
	}
	right = 0;
	while (right < st->len && st->cur[right].a_p >= max_b - last1)
		right++;
	while (st->push != max_b && !relative_ascendant(st, st->push, st->len))
	{
		if (set_rrr)
			right = rot_min_a(st, right);
		else
			rot_min_a(st, 0);
		ft_printf("pb\n");
		st->push++;
	}
	while (st->cur[st->len - 1].a_p < st->cur[st->push].a_p)
	{
		ft_printf("rra\n");
		set_operation(st, rra);
	}
	while (st->push != max_b - last1)
	{
		rot_max_b(st);
		ft_printf("pa\n");
		st->push--;
	}
}

void	to_left_1(t_stack *st, int last)
{
	int	max_b;

	max_b = st->push;
	while (st->push != max_b - last * 2)
	{
		if (st->cur[st->push - 1].a_p >= max_b - 2 * last)
		{
			ft_printf("pa\n");
			st->push--;
			if (st->cur[st->push].a_p < max_b - last && st->cur[st->push + 1].a_p >= max_b - last)
			{
				ft_printf("ra\n");
				set_operation(st, ra);
			}
		}
		else
		{
			ft_printf("rb\n");
			set_operation(st, rb);
		}
	}
}
