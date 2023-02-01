/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/01/24 17:05:06 by minh-ngu         ###   ########.fr       */
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

void	rot_min_a(t_stack *st)
{
	int	min_a_p;
	int	i_min;
	int	i;
	int	d_ra;
	int	d_rra;

	if (SHOW)
		ft_printf("rot_min_a\n");
	if (st->len - st->push < 2)
		return ;
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
			ft_printf("rra\n");
			set_operation(st, rra);
		}
	}
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

void	to_left(t_stack *st, int last, int last1)
{
	//int	k;
	int	max_b;
	int	left, right;
	//int	left, right, min_l_r;

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
	//ft_printf("left = %d, right = %d\n", left, right);
	while (st->push != max_b)
	{
		rot_min_a(st);
		ft_printf("pb\n");
		st->push++;
	}
	//ft_printf("==== 2 ====\n");
	while (st->push != max_b - last * 2)
	{
		ft_printf("pa\n");
		st->push--;
	}
	//ft_printf("==== 3 ====\n");
	while (st->push != max_b - last1)
	{
		rot_max_b(st);
		ft_printf("pa\n");
		st->push--;
	}
	/*
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
	while (++k < left)
	{
		ft_printf("pb\n");
		st->push++;
	}
	k = -1;
	while (++k < right - min_l_r)
	{
		ft_printf("rrb\n");
		set_operation(st, rrb);
	}
	*/
}

void	to_right(t_stack *st, int last, int last1)
{
	int	k;
	int	max_b;
	int	left, right, min_l_r;

	max_b = st->push;
	//last = 4;
	while (st->push != max_b + last * 2)
	{
		rot_next_a(st, max_b + last * 2);
		ft_printf("pb\n");
		st->push++;
		if (st->cur[st->push].a_p < max_b + last && st->cur[st->push + 1].a_p >= max_b + last)
		{
			ft_printf("rb\n");
			set_operation(st, rb);
		}
	}
	//last1 = 11;
	left = 0;
	while (st->cur[st->len - 1 - left].a_p < max_b + last1)
		left++;
	right = 0;
	while (st->cur[right].a_p >= max_b)
		right++;
	//ft_printf("left = %d, right = %d\n", left, right);
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
	while (++k < left)
	{
		ft_printf("pb\n");
		st->push++;
	}
	k = -1;
	while (++k < right - min_l_r)
	{
		ft_printf("rrb\n");
		set_operation(st, rrb);
	}
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
	{
		if (st->r_sc_a)
		{
			set_operation(st, sa);
			ft_printf("sa\n");
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
	}
	else if (st->len < 6)
	{
		while (st->r_sc_a && st->push < st->len - 3)
		{
			if (st->cur[st->push].a_p_a != 0 && 
					st->cur[st->push + 1].a_p_a != 0 &&
				st->cur[st->push].a_p_a > st->cur[st->push + 1].a_p_a)
			{
				set_operation(st, sa);
				ft_printf("sa\n");
			}
			else
				push_b(st);
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
		//ft_printf("Step 2\n");
		get_position(st);
		if (st->r_sc_a)
		{
			set_operation(st, sa);
			ft_printf("sa\n");
		}
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
	else
	{
		//int	n;
		int	d;
		//int	is_push_b;
		//int	n0;

		d = divide_times(st->len);
		if (d % 2 == 0)
			d++;
		//ft_printf("d = %d\n", d);
		//int	j;
		int	k;
		int	last;
		int	last1;
		int	min_a;
		
		get_position(st);
		//ft_printf("START push = %d\n", st->push);
		//j = -1;
		//i = 1;
		//is_push_b = 1;
		//n = st->len;
		//while (++j < d)
		//{
			//i *= 3;
			//n0 = n / i;
			//ft_printf("n0 = %d\n", n0);
			min_a = 0;
			last = (st->len - min_a) / 3;
			while (st->len - st->push != last)
			{
				//rot_next_a(st, st->len - last);
				if (st->cur[st->push].a_p < st->len - last)
				{
					ft_printf("pb\n");
					st->push++;
					if (st->push > 1 && st->cur[st->push - 1].a_p < st->len - 2 * last && st->cur[st->push - 2].a_p >= st->len - 2 * last)
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
			//print_position(st);
			min_a = st->push;
			last = (st->len - min_a) / 3;
			while (st->len - st->push != last)
			{
				rot_next_a(st, st->len - last);
				ft_printf("pb\n");
				st->push++;
				if (st->push > 1 && st->cur[st->push - 1].a_p < st->len - 2 * last && st->cur[st->push - 2].a_p >= st->len - 2 * last)
				{
					ft_printf("rb\n");
					set_operation(st, rb);
				}
			}

			last = 4;
			while (st->len - st->push != last - 1)
			{
				rot_next_a(st, st->len - last + 1);
				ft_printf("pb\n");
				st->push++;
				if (st->push > 1 && st->cur[st->push - 1].a_p < st->len - 2 * last && st->cur[st->push - 2].a_p >= st->len - 2 * last)
				{
					ft_printf("rb\n");
					set_operation(st, rb);
				}
			}

			last1 = st->push;
			while (st->len - st->push != 2)
			{
				rot_min_a(st);
				ft_printf("pb\n");
				st->push++;
			}
			if (st->cur[st->len - 1].a_p < st->cur[st->len - 2].a_p)
			{
				ft_printf("sa\n");
				set_operation(st, sa);
			}
			while (st->push != last1)
			{
				ft_printf("pa\n");
				st->push--;
			}

			k = -1;
			while (++k < 2 * last)
			{
				rot_max_b(st);
				ft_printf("pa\n");
				st->push--;
			}
			to_left(st, 4, 11);
			to_left(st, 4, 11);
			to_left(st, 11, 33);
			to_left(st, 11, 34);

/*
			min_a = st->push;
			last0 = st->len - min_a;
			last = 11;
			while (st->len - st->push != last0 + 2 * last)
			{
				rot_next_b(st, st->len - last0 - 2 * last);
				ft_printf("pa\n");
				st->push--;
			}

			if (st->cur[st->push - 2].a_p > st->cur[st->push - 1].a_p && st->cur[st->push].a_p > st->cur[st->push + 1].a_p)
			{
				ft_printf("ss\n");
				set_operation(st, ss);
			}

			max_b = st->push;
			last = 11;
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
			k = -1;
			while (++k < last - 1)
			{
				ft_printf("rrr\n");
				set_operation(st, rrr);
			}
			ft_printf("rra\n");
			set_operation(st, rra);
			k = -1;
			while (++k < last)
			{
				ft_printf("pa\n");
				set_operation(st, pa);
			}




			max_b = st->push;
			last = 11;
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
			k = -1;
			while (++k < last)
			{
				ft_printf("rra\n");
				set_operation(st, rra);
			}



			max_b = st->push;
			last = 4;
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
			k = -1;
			while (++k < last)
			{
				ft_printf("rra\n");
				set_operation(st, rra);
			}
			k = -1;
			while (++k < last * 2)
			{
				ft_printf("pb\n");
				set_operation(st, pb);
			}


			i = -1;
			while (++i < 7)
			{
				max_b = st->push;
				last = 4;
				while (st->push != max_b + last * 2)
				{
					rot_next_a(st, max_b + last * 2);
					ft_printf("pb\n");
					st->push++;
					if (st->cur[st->push].a_p < max_b + last && st->cur[st->push + 1].a_p >= max_b + last)
					{
						ft_printf("rb\n");
						set_operation(st, rb);
					}
				}
				last1 = 11;
				left = 0;
				while (st->cur[st->len - 1 - left].a_p < max_b + last1)
					left++;
				right = 0;
				while (st->cur[right].a_p >= max_b)
					right++;
				//ft_printf("left = %d, right = %d\n", left, right);
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
				while (++k < left)
				{
					ft_printf("pb\n");
					st->push++;
				}
				k = -1;
				while (++k < right - min_l_r)
				{
					ft_printf("rrb\n");
					set_operation(st, rrb);
				}
			}
*/
			/*
			max_b = st->cur[0].a_p;
			k = -1;
			while (++k < st->push)
			{
				if (max_b < st->cur[k].a_p)
					max_b = st->cur[k].a_p;
			}
			min_a = st->cur[st->push].a_p;
			k = st->push - 1;
			while (++k < st->len)
			{
				if (min_a > st->cur[k].a_p)
					min_a = st->cur[k].a_p;
			}
			//ft_printf("max_b = %d, min_a = %d\n", max_b, min_a);
			is_push_b *= -1;
		//}
		*/
	}
	/*
	while (st->push)
	{
		rot_max_b(st);
		ft_printf("pa\n");
		st->push--;
	}
	*/
	//rot_b(st);
	//while (st->push)
	//	push_a(st);
	//rot_a(st);
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
