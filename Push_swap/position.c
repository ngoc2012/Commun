/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:21:22 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/02/05 07:24:56 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_i_min(t_stack *st, int start, int end)
{
	int	i_min;
	int	min;

	i_min = start;
	min = st->cur[start].v;
	while (++start < end)
	{
		if (st->cur[start].v < min)
		{
			min = st->cur[start].v;
			i_min = start;
		}
	}
	return (i_min);
}

int	ascendant(t_stack *st, int start, int end)
{
	while (++start < end)
		if (st->cur[start - 1].v > st->cur[start].v)
			return (0);
	return (1);
}

int	relative_ascendant(t_stack *st, int start, int end)
{
	int	i_min;

	i_min = get_i_min(st, start, end);
	if (ascendant(st, start, i_min) == 0)
		return (0);
	if (ascendant(st, i_min, end) == 0)
		return (0);
	if (i_min != start && st->cur[start].v < st->cur[end - 1].v)
		return (0);
	return (1);
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
