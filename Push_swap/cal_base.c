/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/02/02 11:30:15 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	calculate_3(t_stack *st)
{
	get_position(st);
	if (st->r_sc_a)
	{
		set_operation(st, sa);
		ft_printf("sa\n");
	}
	rot_min_a(st, 0);
}

void	calculate_9(t_stack *st)
{
	while (st->r_sc_a && st->len - st->push > 3)
	{
		rot_min_a(st, 0);
		ft_printf("pb\n");
		st->push++;
		get_position(st);
	}
	calculate_3(st);
	while (st->push)
	{
		ft_printf("pa\n");
		st->push--;
	}
}

void	calculate_27(t_stack *st)
{
	int	last;

	get_position(st);
	to_right_2(st);
	last = st->push;
	while (st->len - st->push > 3)
	{
		rot_min_a(st, 0);
		ft_printf("pb\n");
		st->push++;
	}
	calculate_3(st);
	while (st->push != last)
	{
		ft_printf("pa\n");
		st->push--;
	}
	while (st->push)
	{
		rot_max_b(st);
		ft_printf("pa\n");
		st->push--;
	}
}

void	calculate(t_stack *st)
{
	if (st->len == 1 || (st->len == 2 && st->cur[0].v < st->cur[1].v))
		return ;
	if (st->len == 2 && st->cur[0].v > st->cur[1].v)
	{
		ft_printf("sa\n");
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
