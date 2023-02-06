/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/02/06 01:44:29 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	calculate_3(t_stack *st)
{
	if (!relative_ascendant(st, st->push, st->len))
		set_operation(st, sa);
	rot_min_a(st, 0);
}

void	calculate_9(t_stack *st)
{
	while (!relative_ascendant(st, st->push, st->len) && st->len - st->push > 3)
	{
		rot_min_a(st, 0);
		set_operation(st, pb);
	}
	calculate_3(st);
	while (st->push)
		set_operation(st, pa);
}

void	calculate_27(t_stack *st)
{
	int	last;

	to_right_2(st);
	last = st->push;
	while (st->len - st->push > 3)
	{
		rot_min_a(st, 0);
		set_operation(st, pb);
	}
	calculate_3(st);
	while (st->push != last)
		set_operation(st, pa);
	while (st->push)
	{
		rot_max_b(st);
		set_operation(st, pa);
	}
}

void	calculate(t_stack *st)
{
	if (st->len == 1 || (st->len == 2 && st->cur[0].v < st->cur[1].v))
		return ;
	if (st->len == 2 && st->cur[0].v > st->cur[1].v)
	{
		set_operation(st, sa);
		return ;
	}
	if (st->len == 3)
		calculate_3(st);
	else if (st->len <= 9)
		calculate_9(st);
	else if (st->len <= 27)
		calculate_27(st);
	else if (st->len <= 81)
		calculate_81(st);
	else
		calculate_729(st);
}
