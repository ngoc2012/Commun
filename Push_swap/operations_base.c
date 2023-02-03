/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:18:11 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/02/02 10:18:27 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_stack *st, int i, int j)
{
	t_el	k;

	k = st->cur[i];
	st->cur[i] = st->cur[j];
	st->cur[j] = k;
}

void	set_ra(t_stack *st, enum e_ops op)
{
	int	i;

	if ((op == ra || op == rr) && st->len - st->push >= 2)
	{
		i = st->push - 1;
		while (++i < st->len - 1)
			swap(st, i, i + 1);
		if (op == ra)
			return ;
	}
	if ((op == rra || op == rrr) && st->len - st->push >= 2)
	{
		i = st->len;
		while (--i > st->push)
			swap(st, i, i - 1);
		return ;
	}
}

void	set_rb(t_stack *st, enum e_ops op)
{
	int	i;

	if ((op == rrb || op == rrr) && st->push >= 2)
	{
		i = -1;
		while (++i < st->push - 1)
			swap(st, i, i + 1);
		if (op == rrb)
			return ;
	}
	if ((op == rb || op == rr) && st->push >= 2)
	{
		i = st->push;
		while (--i > 0)
			swap(st, i, i - 1);
		return ;
	}
}

void	set_operation(t_stack *st, enum e_ops op)
{
	if ((op == sa || op == ss) && st->len - st->push >= 2)
	{
		swap(st, st->push, st->push + 1);
		if (op == sa)
			return ;
	}
	if ((op == sb || op == ss) && st->push >= 2)
	{
		swap(st, st->push - 1, st->push - 2);
		return ;
	}
	if (op == pa && st->push > 0)
	{
		st->push--;
		return ;
	}
	if (op == pb && st->push < st->len)
	{
		st->push++;
		return ;
	}
	set_ra(st, op);
	set_rb(st, op);
}
