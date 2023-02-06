/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_right.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/02/06 02:00:22 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	divide_third(int n)
{
	int	o;

	o = n / 3;
	if (n - o * 3 == 2)
		return (o + 1);
	else
		return (o);
}

void	to_right(t_stack *st, int max_b, int last, int last1)
{
	int	last2;

	last2 = st->push;
	while (st->push != last2 + last * 2)
	{
		if (st->cur[st->push].a_p < max_b + 2 * last)
		{
			set_operation(st, pb);
			if (st->cur[st->push - 1].a_p < max_b + last
				&& st->cur[st->push - 2].a_p >= max_b + last)
				set_operation(st, rb);
		}
		else
			set_operation(st, ra);
	}
	last2 = st->push;
	while (st->push != last2 + last1 - 2 * last)
	{
		rot_min_a_2(st, max_b + 2 * last, 0);
		set_operation(st, pb);
	}
	last2 = st->push;
	while (st->push != last2 - last1 && rot_max_b(st))
		set_operation(st, pa);
}

void	to_right_1(t_stack *st, int last, int last1)
{
	int	max_b;

	max_b = st->push;
	while (st->push != max_b + last * 2)
	{
		rot_next_a(st, max_b + last * 2);
		set_operation(st, pb);
		if (st->cur[st->push - 1].a_p < max_b + last
			&& st->cur[st->push - 2].a_p >= max_b + last)
			set_operation(st, rb);
	}
	while (st->push != max_b + last1)
	{
		rot_min_a(st, 0);
		set_operation(st, pb);
	}
	while (st->push != max_b)
	{
		rot_max_b(st);
		set_operation(st, pa);
	}
}

void	to_right_2(t_stack *st)
{
	int	last;
	int	last1;

	last1 = divide_third(st->len - st->push);
	last = st->len - st->push - last1 * 2;
	while (st->len - st->push != last)
	{
		if (st->cur[st->push].a_p < st->len - last)
		{
			set_operation(st, pb);
			if (st->push > 1
				&& st->cur[st->push - 1].a_p < st->len - last - last1
				&& (st->cur[st->push - 2].a_p >= st->len - last - last1
					|| st->cur[st->push - 2].a_p < st->len - last - last1 * 2))
				set_operation(st, rb);
		}
		else
			set_operation(st, ra);
	}
}
