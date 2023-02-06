/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/02/06 01:56:18 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	set_d_ra(t_stack *st, int d_ra, int d_rra, int right)
{
	if (d_ra <= d_rra)
	{
		while (d_ra--)
			set_operation(st, ra);
		return (right);
	}
	while (d_rra--)
	{
		if (right > 0)
		{
			set_operation(st, rrr);
			right--;
		}
		else
			set_operation(st, rra);
	}
	return (right);
}

int	set_d_rb(t_stack *st, int d_rb, int d_rrb, int left)
{
	if (d_rb <= d_rrb)
	{
		while (d_rb--)
			set_operation(st, rb);
		return (left);
	}
	while (d_rrb--)
	{
		if (left > 0)
		{
			set_operation(st, rrr);
			left--;
		}
		else
			set_operation(st, rrb);
	}
	return (left);
}
