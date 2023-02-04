/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/02/04 11:13:42 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	to_left(t_stack *st, int last, int last1, int set_rrr)
{
	int	max_b;
	int	left, right;

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
	//left = 0;
	//while (st->cur[st->len - 1 - left].a_p < max_b)
	//	left++;
	//right = 0;
	//while (right < st->len && st->cur[right].a_p >= max_b - last1)
	//	right++;
	get_position(st);
	while (st->push != max_b && st->r_sc_a != 0)
	{
		if (set_rrr)
			right = rot_min_a(st, right);
		else
			rot_min_a(st, 0);
		ft_printf("pb\n");
		st->push++;
		get_position(st);
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

void	to_left_2(t_stack *st, int last, int last1)
{
	int	max_b;
	//int	left, right;

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
	//left = 0;
	//while (st->cur[st->len - 1 - left].a_p < max_b)
	//	left++;
	//right = 0;
	//while (right < st->len && st->cur[right].a_p >= max_b - last1)
	//	right++;
}

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
	//int	left, right;

	last2 = st->push;
	while (st->push != last2 + last * 2)
	{
		if (st->cur[st->push].a_p < max_b + 2 * last)
		{
			ft_printf("pb\n");
			st->push++;
			if (st->cur[st->push - 1].a_p < max_b + last && st->cur[st->push - 2].a_p >= max_b + last)
			{
				ft_printf("rb\n");
				set_operation(st, rb);
			}
		}
		else
		{
			ft_printf("ra\n");
			set_operation(st, ra);
		}
	}
	//left = 0;
	//while (st->cur[st->len - 1 - left].a_p < max_b + last1)
	//	left++;
	//right = 0;
	//while (right < st->len && st->cur[right].a_p >= max_b)
	//	right++;
	last2 = st->push;
	while (st->push != last2 + last1 - 2 * last)
	{
		rot_min_a_2(st, max_b + 2 * last, 0);
		ft_printf("pb\n");
		st->push++;
	}
	last2 = st->push;
	while (st->push != last2 - last1)
	{
		rot_max_b(st);
		ft_printf("pa\n");
		st->push--;
	}
}

void	to_right_1(t_stack *st, int last, int last1)
{
	int	max_b;
	int	left, right;

	max_b = st->push;
	while (st->push != max_b + last * 2)
	{
		rot_next_a(st, max_b + last * 2);
		ft_printf("pb\n");
		st->push++;
		if (st->cur[st->push - 1].a_p < max_b + last && st->cur[st->push - 2].a_p >= max_b + last)
		{
			ft_printf("rb\n");
			set_operation(st, rb);
		}
	}
	left = 0;
	while (st->cur[st->len - 1 - left].a_p < max_b + last1)
		left++;
	right = 0;
	while (right < st->len && st->cur[right].a_p >= max_b)
		right++;
	while (st->push != max_b + last1)
	{
		rot_min_a(st, 0);
		ft_printf("pb\n");
		st->push++;
	}
	while (st->push != max_b)
	{
		rot_max_b(st);
		ft_printf("pa\n");
		st->push--;
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
			ft_printf("pb\n");
			st->push++;
			if (st->push > 1 && st->cur[st->push - 1].a_p < st->len - last - last1 && (st->cur[st->push - 2].a_p >= st->len - last - last1 || st->cur[st->push - 2].a_p < st->len - last - last1 * 2))
			{
				ft_printf("rb\n");
				set_operation(st, rb);
			}
		}
		else
		{
			ft_printf("ra\n");
			set_operation(st, ra);
		}
	}
}
