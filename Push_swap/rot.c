/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/02/01 16:54:44 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rot_next_a(t_stack *st, int max_a_p)
{
	int	i;
	int	d_ra;
	int	d_rra;

	if (st->len - st->push < 2)
		return ;
	d_ra = st->len;
	d_rra = st->len;
	i = st->push - 1;
	while (++i < st->len)
	{
		if (st->cur[i].a_p < max_a_p && d_ra > i - st->push)
			d_ra = i - st->push;
		if (st->cur[i].a_p < max_a_p && d_rra > st->len - st->push - i)
			d_rra = st->len - i;
	}
	if (d_ra <= d_rra)
	{
		while (d_ra--)
		{
			ft_printf("ra\n");
			set_operation(st, ra);
		}
	}
	else
	{
		while (d_rra--)
		{
			ft_printf("rra\n");
			set_operation(st, rra);
		}
	}
}

void	rot_next_b(t_stack *st, int min_a_p)
{
	int	i;
	int	d_rb;
	int	d_rrb;

	if (st->push < 2)
		return ;
	d_rb = st->len;
	d_rrb = st->len;
	i = -1;
	while (++i < st->push)
	{
		if (st->cur[i].a_p >= min_a_p && d_rb > st->push - 1 - i)
			d_rb = st->push - 1 - i;
		if (st->cur[i].a_p >= min_a_p && d_rrb > i + 1)
			d_rrb = i + 1;
	}
	if (d_rb <= d_rrb)
	{
		while (d_rb--)
		{
			ft_printf("rb\n");
			set_operation(st, rb);
		}
	}
	else
	{
		while (d_rrb--)
		{
			ft_printf("rrb\n");
			set_operation(st, rrb);
		}
	}
}

int	rot_min_a(t_stack *st, int right)
{
	int	min_a_p;
	int	i_min;
	int	i;
	int	d_ra;
	int	d_rra;

	if (st->len - st->push < 2)
		return (right);
	i_min = st->push;
	min_a_p = st->cur[i_min].a_p;
	i = st->push;
	while (++i < st->len)
	{
		if (st->cur[i].a_p < min_a_p)
		{
			i_min = i;
			min_a_p = st->cur[i].a_p;
		}
	}
	d_ra = i_min - st->push;
	d_rra = st->len - st->push - d_ra;
	if (d_ra <= d_rra)
	{
		while (d_ra--)
		{
			ft_printf("ra\n");
			set_operation(st, ra);
		}
	}
	else
	{
		while (d_rra--)
		{
			if (right > 0)
			{
				ft_printf("rrr\n");
				set_operation(st, rrr);
				right--;
			}
			else
			{
				ft_printf("rra\n");
				set_operation(st, rra);
			}
		}
	}
	return (right);
}

int	rot_min_a_2(t_stack *st, int min_v, int right)
{
	int	min_a_p;
	int	i_min;
	int	i;
	int	d_ra;
	int	d_rra;

	if (st->len - st->push < 2)
		return (right);
	i_min = st->push;
	min_a_p = st->cur[i_min].a_p;
	i = st->push;
	while (++i < st->len)
	{
		if (st->cur[i].a_p < min_a_p && st->cur[i].a_p >= min_v)
		{
			i_min = i;
			min_a_p = st->cur[i].a_p;
		}
	}
	d_ra = i_min - st->push;
	d_rra = st->len - st->push - d_ra;
	if (d_ra <= d_rra)
	{
		while (d_ra--)
		{
			ft_printf("ra\n");
			set_operation(st, ra);
		}
	}
	else
	{
		while (d_rra--)
		{
			if (right > 0)
			{
				ft_printf("rrr\n");
				set_operation(st, rrr);
				right--;
			}
			else
			{
				ft_printf("rra\n");
				set_operation(st, rra);
			}
		}
	}
	return (right);
}

void	rot_max_b(t_stack *st)
{
	int	max_b;
	int	i_max;
	int	i;
	int	d_rb;
	int	d_rrb;

	if (st->push < 2)
		return ;
	i_max = 0;
	max_b = st->cur[i_max].a_p;
	i = 0;
	while (++i < st->push)
	{
		if (st->cur[i].a_p > max_b)
		{
			i_max = i;
			max_b = st->cur[i].a_p;
		}
	}
	d_rb = st->push - 1 - i_max;
	d_rrb = i_max + 1;
	if (d_rb <= d_rrb)
	{
		while (d_rb--)
		{
			ft_printf("rb\n");
			set_operation(st, rb);
		}
	}
	else
	{
		while (d_rrb--)
		{
			ft_printf("rrb\n");
			set_operation(st, rrb);
		}
	}
}
