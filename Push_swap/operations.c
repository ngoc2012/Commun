/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:18:11 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/01/21 15:20:15 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	set_operation(t_stack *st, enum e_ops op)
{
	int	i;
	t_el	j;

	//ft_printf("%s :\n", op);
	if ((op == sa || op == ss) && st->len - st->push >= 2)
	{
		j = st->cur[st->push];
		st->cur[st->push] = st->cur[st->push + 1]; 
		st->cur[st->push + 1] = j;
		if (op == sa)
			return ;
	}
	if ((op == sb || op == ss) && st->push >= 2)
	{
		j = st->cur[st->push - 1];
		st->cur[st->push - 1] = st->cur[st->push - 2]; 
		st->cur[st->push - 2] = j;
		return ;
	}
	if ((op == ra || op == rr) && st->len - st->push >= 2)
	{
		i = st->push;
		while (i < st->len - 1)
		{
			j = st->cur[i];
			st->cur[i] = st->cur[i + 1]; 
			st->cur[i + 1] = j;
			i++;
		}
		if (op == ra)
			return ;
	}
	if ((op == rrb || op == rrr) && st->push >= 2)
	{
		i = 0;
		while (i < st->push - 1)
		{
			j = st->cur[i];
			st->cur[i] = st->cur[i + 1]; 
			st->cur[i + 1] = j;
			i++;
		}
		if (op == rrb)
			return ;
	}
	if ((op == rra || op == rrr) && st->len - st->push >= 2)
	{
		i = st->len - 1;
		while (i > st->push)
		{
			j = st->cur[i];
			st->cur[i] = st->cur[i - 1]; 
			st->cur[i - 1] = j;
			i--;
		}
		return ;
	}
	if ((op == rb || op == rr) && st->push >= 2)
	{
		i = st->push - 1;
		while (i > 0)
		{
			j = st->cur[i];
			st->cur[i] = st->cur[i - 1]; 
			st->cur[i - 1] = j;
			i--;
		}
		return ;
	}
	if (op == pa && st->push > 0)
	{
		st->push--;
		return ;
	}
	if (op == pb && st->push < st->len)
	{
		st->push++;
		return ;
	}
}

char	*get_ops_str(enum e_ops op)
{
	if (op == ss)
		return ("ss");
	if (op == sa)
		return ("sa");
	if (op == ra)
		return ("ra");
	if (op == rra)
		return ("rra");
	if (op == sb)
		return ("sb");
	if (op == rb)
		return ("rb");
	if (op == rrb)
		return ("rrb");
	if (op == rr)
		return ("rr");
	if (op == rrr)
		return ("rrr");
	return (0);
}

enum e_ops	get_ops(char *op)
{
	if (ft_strncmp(op, "ss", 3) == 0)
		return (ss);
	if (ft_strncmp(op, "sa", 3) == 0)
		return (sa);
	if (ft_strncmp(op, "ra", 3) == 0)
		return (ra);
	if (ft_strncmp(op, "rra", 3) == 0)
		return (rra);
	if (ft_strncmp(op, "sb", 3) == 0)
		return (sb);
	if (ft_strncmp(op, "rb", 3) == 0)
		return (rb);
	if (ft_strncmp(op, "rrb", 3) == 0)
		return (rrb);
	if (ft_strncmp(op, "rr", 3) == 0)
		return (rr);
	if (ft_strncmp(op, "rrr", 3) == 0)
		return (rrr);
	return (-1);
}

void	unset_operation(t_stack *st, enum e_ops op)
{
	if (op == ss)
	{
		set_operation(st, sa);
		set_operation(st, sb);
	}
	if (op == sa)
		set_operation(st, sa);
	if (op == ra)
		set_operation(st, rra);
	if (op == rra)
		set_operation(st, ra);
	if (op == sb)
		set_operation(st, sb);
	if (op == rb)
		set_operation(st, rrb);
	if (op == rrb)
		set_operation(st, rb);
	if (op == rr)
		set_operation(st, rrr);
	if (op == rrr)
		set_operation(st, rr);
	st->get_position(st);
}
