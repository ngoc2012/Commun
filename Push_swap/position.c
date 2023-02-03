/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:21:22 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/02/02 10:58:09 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	get_abs_position(t_stack *st)
{
	int	i;
	int	j;

	i = -1;
	while (++i < st->len)
	{
		st->cur[i].a_p = 0;
		j = -1;
		while (++j < st->len)
			if (j != i && st->cur[j].v < st->cur[i].v)
				st->cur[i].a_p++;
	}
}

int	get_i_min_a(t_stack *st)
{
	int	i;
	int	i_min;
	int	min;

	i_min = st->push;
	min = st->cur[st->push].v;
	i = st->push;
	while (++i < st->len)
	{
		if (st->cur[i].v < min)
		{
			min = st->cur[i].v;
			i_min = i;
		}
	}
	return (i_min);
}

void	get_r_p_a(t_stack *st)
{
	int	i;
	int	j;
	int	i_min_a;

	i_min_a = get_i_min_a(st);
	i = i_min_a - 1;
	while (++i < st->len)
	{
		j = i_min_a - 1;
		while (++j < i)
			if (st->cur[j].v > st->cur[i].v)
				st->cur[i].r_p_a++;
	}
	i = st->push - 1;
	while (++i < i_min_a)
	{
		j = i_min_a - 1;
		while (++j < st->len)
			if (st->cur[j].v > st->cur[i].v)
				st->cur[i].r_p_a++;
		j = st->push - 1;
		while (++j < i)
			if (st->cur[j].v > st->cur[i].v)
				st->cur[i].r_p_a++;
	}
}

void	get_position(t_stack *st)
{
	int	i;

	i = -1;
	while (++i < st->len)
		st->cur[i].r_p_a = 0;
	get_r_p_a(st);
	st->r_sc_a = 0;
	i = st->push - 1;
	while (++i < st->len)
	{
		if (st->cur[i].r_p_a >= 0)
			st->r_sc_a += st->cur[i].r_p_a;
		else
			st->r_sc_a -= st->cur[i].r_p_a;
	}
}
