/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:20:49 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/02/02 10:59:08 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_position(t_stack *st)
{
	int	i;

	i = -1;
	while (++i < st->len)
	{
		if (i == st->push)
			ft_printf("   -------\n");
		ft_printf("%6d", st->cur[i].v);
		ft_printf("%6d", st->cur[i].r_p_a);
		ft_printf("%6d", st->cur[i].a_p);
		ft_printf("\n");
	}
	if (i == st->push)
		ft_printf("   -------\n");
	ft_printf("%6s", "___");
	ft_printf("%6s", "___");
	ft_printf("%6s", "___");
	ft_printf("\n");
	ft_printf("%6s", "ini");
	ft_printf("%6s", "r_p_a");
	ft_printf("%6s", "a_p");
	ft_printf("\n");
	ft_printf("----------\n");
}

void	print_stack(t_stack *st)
{
	int	i;

	i = -1;
	while (++i < st->len)
	{
		if (i > st->push - 1)
			ft_printf("%5d", st->cur[i].v);
		else if (i > st->len - 1 - st->push)
			ft_printf("%5s", "");
		if (i > st->len - 1 - st->push)
			ft_printf("%5d", st->cur[st->len - 1 - i].v);
		if (i > st->push - 1 || i > st->len - st->push - 1)
			ft_printf("\n");
	}
	ft_printf("%5c", '_');
	ft_printf("%5c", '_');
	ft_printf("\n");
	ft_printf("%5c", 'a');
	ft_printf("%5c", 'b');
	ft_printf("\n");
	ft_printf("----------\n");
}
