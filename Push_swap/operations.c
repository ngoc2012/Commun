/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:18:11 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/02/08 06:27:07 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*get_ops_str(enum e_ops op)
{
	if (op == pa)
		return ("pa");
	if (op == pb)
		return ("pb");
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
	if (ft_strncmp(op, "pa", 3) == 0)
		return (pa);
	if (ft_strncmp(op, "pb", 3) == 0)
		return (pb);
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
