/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/02/01 11:40:39 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
sa (swap a) : Intervertit les 2 premiers éléments au sommet de la pile a.
	Ne fait rien s’il n’y en a qu’un ou aucun.
sb (swap b ) : Intervertit les 2 premiers éléments au sommet de la pile b.
	Ne fait rien s’il n’y en a qu’un ou aucun.
ss : sa et sb en même temps.
pa (push a) : Prend le premier élément au sommet de b et le met sur a.
	Ne fait rien si b est vide.
pb (push b) : Prend le premier élément au sommet de a et le met sur b.
	Ne fait rien si a est vide.
ra (rotate a) : Décale d’une position vers le haut tous les élements de la pile a.
	Le premier élément devient le dernier.
rb (rotate b) : Décale d’une position vers le haut tous les élements de la pile b.
	Le premier élément devient le dernier.
rr : ra et rb en même temps.
rra (reverse rotate a) : Décale d’une position vers le bas tous les élements de
	la pile a. Le dernier élément devient le premier.
rrb (reverse rotate b) : Décale d’une position vers le bas tous les élements de
	la pile b. Le dernier élément devient le premier.
rrr : rra et rrb en même temps.

1 - Check a best move till no better move found

2 - Push a half of number to stack b while using insertion sort:
2.1 - Push 1st one, check best move on stack a
2.2 - Push 2nd one, check best move on stack a, if new one is smaller -> swap b
2.2 - Push 3rd one, check best move on stack a:
	(not optimize) If new one is smaller than [0] -> rb
	If new one is smoller than [1] and bigger than [0] -> sb

2.3 - Push 4th one, check best move on stack a,
	rb until bigger one then sb (or smallest one in case the new one is smallest) (1 more move, must find the best distance)
	or rrb until smaller one on top (or biggest one in case the new one is smallest)
Check best move on stack a until score a == 0
3 - Repush on stack a:
	- Rotate rb and rrb untill biggest one on top,
	- Push 
*/

void	free_stack(t_stack *st)
{
	free(st->ini);
	free(st->cur);
	free(st);
}

void	push_a(t_stack *st)
{
	int	d_ra;
	int	d_rra;
	int	nearest_a_p;
	int	max_a_p;
	int	min_a_p;
	int	i;

	if (SHOW)
		ft_printf("push_a\n");
	if (st->push == 0)
		return ;
	d_ra = 0;
	d_rra = 0;
	if (st->len - st->push > 1)
	{
		max_a_p = st->cur[st->push].a_p;
		min_a_p = st->cur[st->push].a_p;
		i = st->push - 1;
		while (++i < st->len)
		{
			if (st->cur[i].a_p > max_a_p)
				max_a_p = st->cur[i].a_p;
			if (st->cur[i].a_p < min_a_p)
				min_a_p = st->cur[i].a_p;
		}
		if (st->cur[st->push - 1].a_p < min_a_p || st->cur[st->push - 1].a_p > max_a_p)
			nearest_a_p = min_a_p;
		else
		{
			nearest_a_p = max_a_p;
			i = st->push - 1;
			while (++i < st->len)
				if (st->cur[i].a_p < nearest_a_p && st->cur[i].a_p > st->cur[st->push - 1].a_p)
					nearest_a_p = st->cur[i].a_p;
		}
		if (SHOW)
			ft_printf("max = %d, min = %d, nearest = %d, ", max_a_p, min_a_p,  nearest_a_p);
		d_rra++;
		while (st->cur[st->len - d_rra].a_p != nearest_a_p)
			d_rra++;
		d_ra = st->len - st->push - d_rra;
		if (SHOW)
			ft_printf("d_ra = %d, d_rra = %d\n", d_ra, d_rra);
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
	st->push--;
	ft_printf("pa\n");


	if (SHOW == 1)
		print_stack(st);
	if (SHOW == 2)
		print_position(st);
}

void	push_b(t_stack *st)
{
	int	d_rb;
	int	d_rrb;
	int	nearest_a_p;
	int	max_a_p;
	int	min_a_p;
	int	i;

	d_rb = 0;
	d_rrb = 0;
	if (st->push > 1)
	{
		max_a_p = st->cur[0].a_p;
		min_a_p = st->cur[0].a_p;
		i = -1;
		while (++i < st->push)
		{
			if (st->cur[i].a_p > max_a_p)
				max_a_p = st->cur[i].a_p;
			if (st->cur[i].a_p < min_a_p)
				min_a_p = st->cur[i].a_p;
		}
		if (st->cur[st->push].a_p < min_a_p || st->cur[st->push].a_p > max_a_p)
			nearest_a_p = max_a_p;
		else
		{
			nearest_a_p = min_a_p;
			i = -1;
			while (++i < st->push)
				if (st->cur[i].a_p > nearest_a_p && st->cur[i].a_p < st->cur[st->push].a_p)
					nearest_a_p = st->cur[i].a_p;
		}
		if (SHOW)
			ft_printf("max = %d, min = %d, nearest = %d, ", max_a_p, min_a_p,  nearest_a_p);
		while (st->cur[d_rrb].a_p != nearest_a_p)
			d_rrb++;
		d_rrb++;
		d_rb = st->len - st->push - d_rrb;
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
	st->push++;
	ft_printf("pb\n");

	if (st->push == 2 && st->cur[1].v < st->cur[0].v)
	{
		ft_printf("sb\n");
		set_operation(st, sb);
	}
}

void	rot_a(t_stack *st)
{
	int	d_ra;
	int	d_rra;

	if (SHOW)
		ft_printf("rot_a\n");
	if (st->len - st->push < 2)
		return ;
	d_ra = 0;
	d_rra = 0;
	if (st->cur[st->len - 1].v < st->cur[st->push].v)
	{
		while (st->cur[st->push + d_ra].v < st->cur[st->push + 1 + d_ra].v)
			d_ra++;
		d_ra++;
	}
	d_rra = st->len - st->push - d_ra;
	//ft_printf("push = %d, d_ra = %d, d_rra = %d\n", st->push, d_ra, d_rra);
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

void	rot_b(t_stack *st)
{
	int	d_rb;
	int	d_rrb;

	if (SHOW)
		ft_printf("rot_b\n");
	if (st->push < 2)
		return ;
	d_rb = 0;
	d_rrb = 0;
	if (st->cur[st->push - 1].v < st->cur[0].v)
	{
		while (st->cur[st->push - 1 - d_rb].v > st->cur[st->push - 2 - d_rb].v)
			d_rb++;
		d_rb++;
	}
	d_rrb = st->push - d_rb;
	//ft_printf("push = %d, d_rb = %d, d_rrb = %d\n", st->push, d_rb, d_rrb);
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

void	rot_next_a(t_stack *st, int max_a_p)
{
	int	i;
	int	d_ra;
	int	d_rra;

	if (SHOW)
		ft_printf("rot_next_a\n");
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
	//ft_printf("d_ra = %d, d_rra = %d\n", d_ra, d_rra);
	//if (d_ra > 2 && d_rra > 2 && st->len - st->push > 1 && st->push > 1)
	//{
	//	if (st->cur[st->push].v > st->cur[st->push + 1].v && st->cur[st->push - 1].v < st->cur[st->push - 2].v)
	//	{
	//		ft_printf("ss\n");
	//		set_operation(st, ss);
	//	}
	//}
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

	if (SHOW)
		ft_printf("rot_next_b\n");
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
	//if (d_rb > 2 && d_rrb > 2 && st->len - st->push > 1 && st->push > 1)
	//{
	//	if (st->cur[st->push].v > st->cur[st->push + 1].v && st->cur[st->push - 1].v < st->cur[st->push - 2].v)
	//	{
	//		ft_printf("ss\n");
	//		set_operation(st, ss);
	//	}
	//}
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

	if (SHOW)
		ft_printf("rot_min_a\n");
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
	//print_position(st);
	//ft_printf("rot_min_a: i_min = %d, min_a_p = %d, a_p = %d\n", i_min, min_a_p, st->cur[i_min].a_p);
	//ft_printf("rot_min_a: d_ra = %d, d_rra = %d\n", d_ra, d_rra);
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

	if (SHOW)
		ft_printf("rot_min_a\n");
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
	//print_position(st);
	//ft_printf("rot_min_a: i_min = %d, min_a_p = %d, a_p = %d\n", i_min, min_a_p, st->cur[i_min].a_p);
	//ft_printf("rot_min_a: d_ra = %d, d_rra = %d\n", d_ra, d_rra);
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

	if (SHOW)
		ft_printf("rot_max_b\n");
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
	//ft_printf("rot_max_b: d_rb = %d, d_rrb = %d, st->push = %d, st->cur[0].a_p = %d, st->cur[70].a_p = %d, max_b = %d\n", d_rb, d_rrb, st->push, st->cur[0].a_p, st->cur[70].a_p, max_b);
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

int	divide_times(int a)
{
	int	d;

	d = 0;
	while (a > 20)
	{
		a /= 3;
		//ft_printf("a = %d\n", a);
		d++;
	}
	return (d);
}

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
	left = 0;
	while (st->cur[st->len - 1 - left].a_p < max_b)
		left++;
	right = 0;
	while (right < st->len && st->cur[right].a_p >= max_b - last1)
		right++;
	//ft_printf("max_b = %d, left = %d, right = %d\n", max_b, left, right);
	/*
	int	k;
	int	min_l_r;
	if (st->push > last1 - 2 * last)
	{
		min_l_r = left;
		if (right < min_l_r)
			min_l_r = right;
		k = -1;
		while (++k < min_l_r)
		{
			ft_printf("rrr\n");
			set_operation(st, rrr);
		}
		k = -1;
		while (++k < left - min_l_r)
		{
			ft_printf("rra\n");
			set_operation(st, rra);
		}
		k = -1;
		while (++k < right - min_l_r)
		{
			ft_printf("rrb\n");
			set_operation(st, rrb);
		}
	}
	*/
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
	//ft_printf("==== 2 ====\n");
	get_position(st);
	while (st->push != max_b - last * 2)
	{
		rot_max_b(st);
		ft_printf("pa\n");
		st->push--;
		get_position(st);
	}
	//ft_printf("==== 3 ====\n");
	while (st->push != max_b - last1)
	{
		rot_max_b(st);
		ft_printf("pa\n");
		st->push--;
	}
	
}

void	to_left_1(t_stack *st, int last, int last1)
{
	int	max_b;
	int	left, right;

	max_b = st->push;
	//ft_printf("to_left_1: max_b = %d, last = %d, last1 = %d\n", max_b, last, last1);
	while (st->push != max_b - last * 2)
	{
		//rot_next_b(st, max_b - last * 2);
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
	left = 0;
	while (st->cur[st->len - 1 - left].a_p < max_b)
		left++;
	right = 0;
	while (right < st->push && st->cur[right].a_p >= max_b - last1)
		right++;
	//ft_printf("to_left_1: max_b = %d, left = %d, right = %d\n", max_b, left, right);
	/*
	int	k;
	int	min_l_r;
	if (st->push > last1 - 2 * last)
	{
		min_l_r = left;
		if (right < min_l_r)
			min_l_r = right;
		k = -1;
		while (++k < min_l_r)
		{
			ft_printf("rrr\n");
			set_operation(st, rrr);
		}
		k = -1;
		while (++k < left - min_l_r)
		{
			ft_printf("rra\n");
			set_operation(st, rra);
		}
		k = -1;
		while (++k < right - min_l_r)
		{
			ft_printf("rrb\n");
			set_operation(st, rrb);
		}
	}
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
	//ft_printf("==== 2 ====\n");
	get_position(st);
	while (st->push != max_b - last * 2)
	{
		rot_max_b(st);
		ft_printf("pa\n");
		st->push--;
		get_position(st);
	}
	//ft_printf("==== 3 ====\n");
	while (st->push != max_b - last1)
	{
		rot_max_b(st);
		ft_printf("pa\n");
		st->push--;
	}
	*/
	
}

void	to_left_2(t_stack *st, int last, int last1)
{
	int	max_b;
	int	left, right;

	max_b = st->push;
	//ft_printf("to_left_2: max_b = %d, last = %d, last1 = %d\n", max_b, last, last1);
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
	left = 0;
	while (st->cur[st->len - 1 - left].a_p < max_b)
		left++;
	right = 0;
	while (right < st->len && st->cur[right].a_p >= max_b - last1)
		right++;
	//ft_printf("to_left_2: max_b = %d, left = %d, right = %d\n", max_b, left, right);
	//int	k;
	//int	min_l_r;
	//min_l_r = left;
	//if (right < min_l_r)
	//	min_l_r = right;
	//k = -1;
	//while (++k < min_l_r)
	//{
	//	ft_printf("rrr\n");
	//	set_operation(st, rrr);
	//}
	//k = -1;
	//while (++k < left - min_l_r)
	//{
	//	ft_printf("rra\n");
	//	set_operation(st, rra);
	//}
	//k = -1;
	//while (++k < right - min_l_r)
	//{
	//	ft_printf("rrb\n");
	//	set_operation(st, rrb);
	//}
	//get_position(st);
	//while (st->push != max_b && st->r_sc_a != 0)
	//{
	//	rot_min_a(st);
	//	ft_printf("pb\n");
	//	st->push++;
	//	get_position(st);
	//}
	//while (st->cur[st->len - 1].a_p < st->cur[st->push].a_p)
	//{
	//	ft_printf("rra\n");
	//	set_operation(st, rra);
	//}
	////ft_printf("==== 2 ====\n");
	//while (st->push != max_b - last * 2)
	//{
	//	ft_printf("pa\n");
	//	st->push--;
	//}
	////ft_printf("==== 3 ====\n");
	//while (st->push != max_b - last1)
	//{
	//	rot_max_b(st);
	//	ft_printf("pa\n");
	//	st->push--;
	//}
	
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
	int	left, right;

	//ft_printf("to_right: max_b = %d, last = %d, last1 = %d\n", max_b, last, last1);
	last2 = st->push;
	while (st->push != last2 + last * 2)
	{
		//rot_next_a(st, max_b + last * 2);
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
	left = 0;
	while (st->cur[st->len - 1 - left].a_p < max_b + last1)
		left++;
	right = 0;
	while (right < st->len && st->cur[right].a_p >= max_b)
		right++;
	//ft_printf("to_right: max_b = %d, left = %d, right = %d\n", max_b, left, right);
	//get_position(st);
	//while (st->push != max_b && st->r_sc_a != 0)
	//{
	//	if (set_rrr)
	//		right = rot_min_a(st, right);
	//	else
	//		rot_min_a(st, 0);
	//	ft_printf("pb\n");
	//	st->push++;
	//	get_position(st);
	//}
	//while (st->cur[st->len - 1].a_p < st->cur[st->push].a_p)
	//{
	//	ft_printf("rra\n");
	//	set_operation(st, rra);
	//}
	
	//ft_printf("==== 2 ====\n");
	//get_position(st);
	last2 = st->push;
	while (st->push != last2 + last1 - 2 * last)
	{
		rot_min_a_2(st, max_b + 2 * last, 0);
		ft_printf("pb\n");
		st->push++;
		//get_position(st);
	}
	//while (st->push != max_b + 2 * last)
	//{
	//	ft_printf("pa\n");
	//	st->push--;
	//	//get_position(st);
	//}
	//ft_printf("==== 3 ====\n");
	last2 = st->push;
	while (st->push != last2 - last1)
	{
		rot_max_b(st);
		ft_printf("pa\n");
		st->push--;
	}
	//ft_printf("end_to_right\n");
	
}

void	to_right_1(t_stack *st, int last, int last1)
{
	int	max_b;
	int	left, right;

	max_b = st->push;
	//ft_printf("to_right_1: max_b = %d, last = %d, last1 = %d\n", max_b, last, last1);
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
	//ft_printf("to_right_1: max_b = %d, left = %d, right = %d\n", max_b, left, right);
	//get_position(st);
	//while (st->push != max_b && st->r_sc_a != 0)
	//{
	//	if (set_rrr)
	//		right = rot_min_a(st, right);
	//	else
	//		rot_min_a(st, 0);
	//	ft_printf("pb\n");
	//	st->push++;
	//	get_position(st);
	//}
	//while (st->cur[st->len - 1].a_p < st->cur[st->push].a_p)
	//{
	//	ft_printf("rra\n");
	//	set_operation(st, rra);
	//}
	
	//ft_printf("==== 2 ====\n");
	//get_position(st);
	while (st->push != max_b + last1)
	{
		rot_min_a(st, 0);
		ft_printf("pb\n");
		st->push++;
		//get_position(st);
	}
	//while (st->push != max_b + 2 * last)
	//{
	//	ft_printf("pa\n");
	//	st->push--;
	//	//get_position(st);
	//}
	//ft_printf("==== 3 ====\n");
	while (st->push != max_b)
	{
		rot_max_b(st);
		ft_printf("pa\n");
		st->push--;
	}
	//ft_printf("end_to_right\n");
	
}

void	to_right_2(t_stack *st)
{
	int	last;
	int	last1;

	last1 = divide_third(st->len - st->push);
	last = st->len - st->push - last1 * 2;
	//ft_printf("last = %d, last1 = %d\n", last, last1);
	while (st->len - st->push != last)
	{
		if (st->cur[st->push].a_p < st->len - last)
		{
			ft_printf("pb\n");
			st->push++;
			if (st->push > 1 && st->cur[st->push - 1].a_p < st->len - last - last1 && (st->cur[st->push - 2].a_p >= st->len - last - last1 || st->cur[st->push - 2].a_p < st->len - last - last1 * 2))
			{
				//ft_printf("a_p = %d, len - last - last1/2 = %d\n", st->cur[st->push - 1].a_p, st->len - last - last1/2);
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
/*
void	divide_left(t_stack *st, int n)
{
	int	last;
	int	last1;

	last1 = divide_third(st->len - st->push);
	last = st->len - st->push - last1 * 2;
	//ft_printf("last = %d, last1 = %d\n", last, last1);
	while (st->len - st->push != last)
	{
		if (st->cur[st->push].a_p < st->len - last)
		{
			ft_printf("pb\n");
			st->push++;
			if (st->push > 1 && st->cur[st->push - 1].a_p < st->len - last - last1 && (st->cur[st->push - 2].a_p >= st->len - last - last1 || st->cur[st->push - 2].a_p < st->len - last - last1 * 2))
			{
				//ft_printf("a_p = %d, len - last - last1/2 = %d\n", st->cur[st->push - 1].a_p, st->len - last - last1/2);
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
*/
void	calculate_3(t_stack *st)
{
	get_position(st);
	if (st->r_sc_a)
	{
		set_operation(st, sa);
		ft_printf("sa\n");
		if (SCORE)
		{
			ft_printf("r_sc = %d, ", st->r_sc);
			ft_printf("r_sc_a = %d, ", st->r_sc_a);
			ft_printf("score = %d, ", st->score);
			ft_printf("score_a = %d\n", st->score_a);
		}
		if (SHOW == 1)
			print_stack(st);
		if (SHOW == 2)
			print_position(st);
	}
	rot_min_a(st, 0);
}

void	calculate_9(t_stack *st)
{
	get_position(st);
	while (st->r_sc_a && st->len - st->push > 3)
	{
		rot_min_a(st, 0);
		ft_printf("pb\n");
		st->push++;
		get_position(st);
		if (SCORE)
		{
			ft_printf("r_sc = %d, ", st->r_sc);
			ft_printf("r_sc_a = %d, ", st->r_sc_a);
			ft_printf("score = %d, ", st->score);
			ft_printf("score_a = %d\n", st->score_a);
		}
		if (SHOW == 1)
			print_stack(st);
		if (SHOW == 2)
			print_position(st);
	}
	calculate_3(st);
	while (st->push)
	{
		ft_printf("pa\n");
		st->push--;
	}
	if (SCORE)
	{
		ft_printf("r_sc = %d, ", st->r_sc);
		ft_printf("r_sc_a = %d, ", st->r_sc_a);
		ft_printf("score = %d, ", st->score);
		ft_printf("score_a = %d\n", st->score_a);
	}
	if (SHOW == 1)
		print_stack(st);
	if (SHOW == 2)
		print_position(st);
}

void	calculate_27(t_stack *st)
{
	int	last;

	get_position(st);
	to_right_2(st);
	last = st->push;
	while (st->len - st->push > 3)
	{
		rot_min_a(st, 0);
		ft_printf("pb\n");
		st->push++;
	}
	calculate_3(st);
	while (st->push != last)
	{
		ft_printf("pa\n");
		st->push--;
	}
	while (st->push)
	{
		rot_max_b(st);
		ft_printf("pa\n");
		st->push--;
	}
}

void	calculate_81(t_stack *st)
{
	int	last;

	get_position(st);
	to_right_2(st);
	last = st->push;
	to_right_2(st);
	while (st->len - st->push > 3)
	{
		rot_min_a(st, 0);
		ft_printf("pb\n");
		st->push++;
	}
	calculate_3(st);
	while (st->push != last)
	{
		rot_max_b(st);
		ft_printf("pa\n");
		st->push--;
	}
	to_left(st, divide_third(st->push / 2), st->push / 2, 0); 
	to_left(st, divide_third(st->push), st->push, 0); 
}

void	calculate_243(t_stack *st)
{
	int	last;
	int	last1;

	get_position(st);
	to_right_2(st);
	last = st->push;
	to_right_2(st);
	last1 = st->push;
	to_right_2(st);
	while (st->len - st->push > 3)
	{
		rot_min_a(st, 0);
		ft_printf("pb\n");
		st->push++;
	}
	calculate_3(st);
	while (st->push != last1)
	{
		rot_max_b(st);
		ft_printf("pa\n");
		st->push--;
	}
	to_left(st, divide_third((st->push - last) / 2), (st->push - last) / 2, 1);
	to_left(st, divide_third(st->push - last), st->push - last, 1);
	to_left(st, divide_third(st->push / 2), st->push / 2, 1); 
	to_left(st, divide_third(st->push), st->push, 0); 
}

void	calculate_729(t_stack *st)
{
	int	last;
	int	last1;
	int	last2;
	int	last3;

	get_position(st);
	to_right_2(st);
	last = st->push;
	to_right_2(st);
	last1 = st->push;
	to_right_2(st);
	while (st->len - st->push > 3)
	{
		rot_min_a(st, 0);
		ft_printf("pb\n");
		st->push++;
	}
	calculate_3(st);
	while (st->push != last1)
	{
		rot_max_b(st);
		ft_printf("pa\n");
		st->push--;
	}
	to_left(st, divide_third((st->push - last) / 2), (st->push - last) / 2, 1);
	to_left(st, divide_third(st->push - last), st->push - last, 1);
	//ft_printf("1st step push = %d\n", st->push);
	last = st->push / 2;
	to_left_1(st, divide_third(last), last); 
	last2 = divide_third(last);
	last3 = last - 2 * last2;
	//ft_printf("to_right, last = %d, last2 = %d\n", last, last2);
	to_right(st, 2 * last - last2, divide_third(last2), last2);
	to_right_1(st, divide_third(last2), last2);
	//ft_printf("end to_right\n");
	to_left(st, divide_third(last3), last3, 1);
	last = st->push;
	last2 = divide_third(last);
	last3 = last - 2 * last2;
	to_left_1(st, divide_third(st->push), st->push); 
	to_right(st, last - last2, divide_third(last2), last2);
	to_right_1(st, divide_third(last2), last2);
	to_left(st, divide_third(last3), last3, 1);
}

void	calculate(t_stack *st)
{

	if (SCORE)
	{
		ft_printf("r_sc = %d, ", st->r_sc);
		ft_printf("r_sc_a = %d, ", st->r_sc_a);
		ft_printf("score = %d, ", st->score);
		ft_printf("score_a = %d\n", st->score_a);
	}
	if (SHOW == 1)
		print_stack(st);
	if (SHOW == 2)
		print_position(st);
	if (st->len == 1 || (st->len == 2 && st->cur[0].v < st->cur[1].v))
		return ;
	if (st->len == 2 && st->cur[0].v > st->cur[1].v)
	{
		ft_printf("sa\n");
		set_operation(st, sa);
		return ;
	}
	if (st->len == 3)
		calculate_3(st);
	else if (st->len <= 9)
		calculate_9(st);
	else if (st->len <= 27)
		calculate_27(st);
	else if (st->len <= 81)
		calculate_81(st);
	else if (st->len <= 243)
		calculate_243(st);
	else
		calculate_729(st);
	get_position(st);
	if (SCORE)
	{
		ft_printf("r_sc = %d, ", st->r_sc);
		ft_printf("r_sc_a = %d, ", st->r_sc_a);
		ft_printf("score = %d, ", st->score);
		ft_printf("score_a = %d\n", st->score_a);
	}
	if (SHOW == 1)
		print_stack(st);
	if (SHOW == 2)
		print_position(st);
}

t_stack	*new_stack(int *ini, int len)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (0);
	new->len = len;
	new->push = 0;	
	new->score = 0;	
	new->score_a = 0;	
	new->ini = ini;
	new->cur = malloc(sizeof(t_el) * len);
	if (!new->cur)
		return (0);
	while (len--)
		new->cur[len].v = ini[len];
	get_abs_position(new);
	get_position(new);
	new->calculate = calculate;
	new->free = free_stack;
	return (new);
}

int	main(int argc, char **argv)
{
	int		i;
	int		fd;
	int		*ini;
	t_stack		*st;
	char		*s;
	enum e_ops	ops[9] = {sb, rb, rrb, sa, ra, rra, rr, rrr, ss};
	int	scores[9];

	if (argc < 2)
		return (1);
	ini = malloc(sizeof(int) * (argc - 1));
	if (!ini)
		return (0);
	i = 1;
	while (i < argc)
	{
		ini[i - 1] = ft_atoi(argv[i]);
		i++;
	}
	st = new_stack(ini, argc - 1);
	if (!st)
		return (0);
	if (SHOW == 1)
		print_stack(st);
	if (SHOW == 2)
		print_position(st);
	if (!MANUAL)
		st->calculate(st);
	//print_position(st);
	//ft_printf("Score :%d\n", st->score);
	if (MANUAL)
	{
		get_position(st);
		if (SHOW == 1)
			print_stack(st);
		if (SHOW == 2)
			print_position(st);
		fd = open("operations.txt", O_RDONLY);
		while ((s = get_next_line(fd)))
		{
			if (SCORE)
			{
				i = -1;
				while (++i < 9)
				{
					scores[i] = get_score(st, ops[i]);
					ft_printf("%s %d, ", ops[i], scores[i] - st->score);
				}
				ft_printf("\n");
			}
			if (s[ft_strlen(s) - 1] == '\n')
				s[ft_strlen(s) - 1] = 0;
			ft_printf("%s\n", s);
			set_operation(st, get_ops(s));
			get_position(st);
			if (SHOW == 1)
				print_stack(st);
			if (SHOW == 2)
				print_position(st);
			free(s);
		}
	}
	st->free(st);
}
