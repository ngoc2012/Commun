/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_left.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/02/25 16:28:08 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rot_next_left(t_stack *st, int max_b, int last1, int set_rrr)
{
	int	right;

	right = 0;
	while (right < st->len && st->cur[right].a_p >= max_b - last1)
		right++;
	while (st->push != max_b && !relative_ascendant(st, st->push, st->len))
	{
		if (set_rrr)
			right = rot_min_a(st, right);
		else
			rot_min_a(st, 0);
		set_operation(st, pb, 1);
	}
	while (st->cur[st->len - 1].a_p < st->cur[st->push].a_p)
		set_operation(st, rra, 1);
	while (st->push != max_b - last1)
	{
		rot_max_b(st);
		set_operation(st, pa, 1);
	}
}

void	to_left(t_stack *st, int last, int last1, int set_rrr)
{
	int	max_b;

	max_b = st->push;
	while (st->push != max_b - last * 2)
	{
		rot_next_b(st, max_b - last * 2);
		set_operation(st, pa, 1);
		if (st->cur[st->push].a_p < max_b - last
			&& st->cur[st->push + 1].a_p >= max_b - last)
			set_operation(st, ra, 1);
	}
	rot_next_left(st, max_b, last1, set_rrr);
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
			if (st->cur[st->push].a_p < max_b - last
				&& st->cur[st->push + 1].a_p >= max_b - last)
				set_operation(st, ra, 1);
		}
		else
			set_operation(st, rb, 1);
	}
}
