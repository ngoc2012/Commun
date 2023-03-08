/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/03/07 19:04:09 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_stack(t_stack *st)
{
	free(st->ini);
	free(st->cur);
	free(st);
}

t_stack	*new_stack(int *ini, int len)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (0);
	new->len = len;
	new->push = 0;
	new->ini = ini;
	new->cur = malloc(sizeof(t_el) * len);
	if (!new->cur)
	{
		free(new);
		return (0);
	}
	while (len--)
		new->cur[len].v = ini[len];
	new->free = free_stack;
	return (new);
}
