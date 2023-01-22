/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:21:22 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/01/08 11:28:34 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	get_abs_pos_a(t_stack *st)
{
	int	i;
	int	j;

	i = st->push - 1;
	while (++i < st->len)
	{
		st->cur[i].a_p_a = 0;
		j = st->push - 1;
		while (++j < st->len)
			if (j != i && st->cur[j].v < st->cur[i].v)
				st->cur[i].a_p_a++;
	}
}

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

void	get_position(t_stack *st)
{
	int	i_min;
	int	min;
	int	i;
	int	j;
	int	k;

	//ft_printf("st->push = %d\n", st->push);
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
	i = -1;
	while (++i < st->len)
	{
		st->cur[i].p = 0;
		st->cur[i].r_p_a = 0;
		st->cur[i].a_p_a = 0;
	}
	//ft_printf("i_min = %d, min = %d\n", i_min, min);
	k = -1;
	i = i_min - 1;
	while (++i < st->len)
	{
		st->cur[i].p = ++k;
		j = i_min - 1;
		while (++j < i)
			if (st->cur[j].v > st->cur[i].v)
				st->cur[i].r_p_a++;
	}
	i = st->push - 1;
	while (++i < i_min)
	{
		st->cur[i].p = ++k;
		j = i_min - 1;
		while (++j < st->len)
			if (st->cur[j].v > st->cur[i].v)
				st->cur[i].r_p_a++;
		j = st->push - 1;
		while (++j < i)
			if (st->cur[j].v > st->cur[i].v)
				st->cur[i].r_p_a++;
	}
	i = -1;
	while (++i < st->len)
		st->cur[i].p -= st->cur[i].a_p;
	get_abs_pos_a(st);
	//i = st->push - 1;
	//while (++i < st->len)
	//	st->cur[i].r_p_a -= st->cur[i].a_p_a;
	st->score = 0;
	i = -1;
	while (++i < st->len)
	{
		if (st->cur[i].p >= 0)
			st->score += st->cur[i].p;
		else
			st->score -= st->cur[i].p;
	}
	st->r_sc = 0;
	i = -1;
	while (++i < st->len)
	{
		if (st->cur[i].r_p_a >= 0)
			st->r_sc += st->cur[i].r_p_a;
		else
			st->r_sc -= st->cur[i].r_p_a;
	}
	st->score_a = 0;
	i = st->push - 1;
	while (++i < st->len)
	{
		if (st->cur[i].p >= 0)
			st->score_a += st->cur[i].p;
		else
			st->score_a -= st->cur[i].p;
	}
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

int	position(t_stack *st, int i0)
{
	int	i;
	int	pos;

	pos = 0;
	i = i0;
	while (++i < st->len)
		if (st->cur[i].v < st->cur[i0].v)
			pos++;
	return (pos);
}

