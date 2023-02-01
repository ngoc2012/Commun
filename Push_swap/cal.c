/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/02/01 17:40:00 by minh-ngu         ###   ########.fr       */
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

void	rot_3(t_stack *st, int last)
{
	while (st->len - st->push > 3)
	{
		rot_min_a(st, 0);
		ft_printf("pb\n");
		st->push++;
	}
	calculate_3(st);
	while (st->push != last)
	{
		rot_max_b(st);
		ft_printf("pa\n");
		st->push--;
	}
}

void	calculate_81(t_stack *st)
{
	int	last;

	get_position(st);
	to_right_2(st);
	last = st->push;
	to_right_2(st);
	rot_3(st, last);
	to_left(st, divide_third(st->push / 2), st->push / 2, 0); 
	to_left(st, divide_third(st->push), st->push, 0); 
}

void	calculate_729(t_stack *st)
{
	int	last;
	int	last1;
	int	last2;

	get_position(st);
	to_right_2(st);
	last = st->push;
	to_right_2(st);
	last1 = st->push;
	to_right_2(st);
	rot_3(st, last1);
	to_left(st, divide_third((st->push - last) / 2), (st->push - last) / 2, 1);
	to_left(st, divide_third(st->push - last), st->push - last, 1);
	last = st->push / 2;
	last2 = divide_third(last);
	to_left_1(st, divide_third(last)); 
	to_right(st, 2 * last - last2, divide_third(last2), last2);
	to_right_1(st, divide_third(last2), last2);
	to_left(st, divide_third(last - 2 * last2), last - 2 * last2, 1);
	last = st->push;
	last2 = divide_third(last);
	to_left_1(st, divide_third(st->push)); 
	to_right(st, last - last2, divide_third(last2), last2);
	to_right_1(st, divide_third(last2), last2);
	to_left(st, divide_third(last - 2 * last2), last - 2 * last2, 1);
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
