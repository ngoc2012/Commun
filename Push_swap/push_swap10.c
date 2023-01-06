/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/01/06 08:33:58 by minh-ngu         ###   ########.fr       */
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

enum e_ops	best_operation(t_stack *st)
{
	int	min;
	int	i;
	int	scores[9];
	enum e_ops	ops[9] = {sb, rb, rrb, sa, ra, rra, rr, rrr, ss};
	enum e_ops	op_min;

	if (SCORE)
		ft_printf("score = %d\n", st->score);
	op_min = 100;
	min = st->score;
	i = 2;
	while (++i < 6)
	{
		scores[i] = get_score(st, ops[i]);
		if (i <= 2 && st->push < 2)
			scores[i] = st->score + 100;
		if (i > 2 && st->len - st->push < 2)
			scores[i] = st->score + 100;
		if (SCORE)
			ft_printf("%s %d, ", get_ops_str(ops[i]), scores[i] - st->score);
		if (min > scores[i])
		{
			min = scores[i];
			op_min = ops[i];
		}
	}
	if (SCORE)
	{
		ft_printf("\nmin = %d\n", min);
		if (op_min != 100)
			ft_printf("\nop_min = %s\n", get_ops_str(op_min));
		else
			ft_printf("No op_min\n");
	}
	return (op_min);
}

void	push_a(t_stack *st)
{
	int	d_ra;
	int	d_rra;

	if (st->push == 0)
		return ;
	if (st->len - st->push > 1)
	{
		d_ra = 0;
		while (st->cur[st->push + d_ra].v > st->cur[st->push - 1].v)
			d_ra++;
		d_rra = 0;
		while (st->cur[st->len - 1 - d_rra].v < st->cur[st->push - 1].v)
			d_rra++;
		if (d_ra >= d_rra)
		{
			while (d_ra--)
				set_operation(st, ra);
		}
		else
		{
			while (d_rra--)
				set_operation(st, rra);
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

	if (st->push > 1)
	{
		d_rb = 0;
		while (st->cur[st->push - 1 - d_rb].v > st->cur[st->push].v)
			d_rb++;
		d_rrb = 0;
		while (st->cur[d_rrb].v > st->cur[st->push].v)
			d_rrb++;
		if (d_rb >= d_rrb)
		{
			while (d_rb--)
				set_operation(st, rb);
		}
		else
		{
			while (d_rrb--)
				set_operation(st, rrb);
		}
	}
	st->push++;
	ft_printf("pb\n");

	if (st->push == 2 && st->cur[1].v < st->cur[0].v)
	{
		ft_printf("sb\n");
		set_operation(st, sb);
	}

	if (SHOW == 1)
		print_stack(st);
	if (SHOW == 2)
		print_position(st);
}

int	check_best(t_stack *st)
{
	int		check;
	enum e_ops	best;

	check = 0;
	if (SHOW)
		ft_printf("========== check best =========\n");
	get_position(st);
	best = best_operation(st);
	while (best != 100 && st->score)
	{
		check = 1;
		ft_printf("%s\n", get_ops_str(best));
		if (SCORE)
			ft_printf("best operation = %s\n", get_ops_str(best));

		set_operation(st, best);
		get_position(st);

		if (SHOW == 1)
			print_stack(st);
		if (SHOW == 2)
			print_position(st);

		best = best_operation(st);
	}
	return (check);
}

void	calculate(t_stack *st)
{
	int	last_sc_a;
	int	i;
	//enum e_ops	best;

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
			set_operation(st, sa);
	}
	else
	{
		i = -1;	
		while (st->r_sc_a && i < st->len - 2)
		{
			get_position(st);
			last_sc_a = st->r_sc_a;
			set_operation(st, sa);
			get_position(st);
			print_position(st);
			if (st->r_sc_a >= last_sc_a) 
			{
				set_operation(st, sa);
				push_b(st);
			}
			else
			{
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
		}
	}
	while (st->push--)
		push_a(st);
/*	if (st->score)
	{
		best = 100;
		i = -1;
		while (++i < st->len - 2 && best == 100)
		{
			set_operation(st, ra);
			get_position(st);
			if (get_score(st, sa) < st->score)
				best = sa;
		}
		//ft_printf("i = %d\n", i);
		//ft_printf("best = %d\n", best);
		if (best != 100)
		{
			if (i > st->len / 2)
			{
				i = st->len - i;
				while (i--)
					ft_printf("rra\n");
			}
			else
			{
				while (i--)
					ft_printf("ra\n");
			}
			ft_printf("%s\n", get_ops_str(best));
			set_operation(st, best);
			get_position(st);
		}
		else
			while (--i)
				unset_operation(st, ra);
	}
	while (st->push < st->len - 3 && st->score_a)
	{
		next_push(st);
		check_best(st);
		if (SCORE)
		{
			ft_printf("score = %d\n", st->score);
			ft_printf("score_a = %d\n", st->score_a);
		}
		if (SHOW == 1)
			print_stack(st);
		if (SHOW == 2)
			print_position(st);
	}
	while (st->push--)
	{
		ft_printf("pa\n");

		if (SHOW == 1)
			print_stack(st);
		if (SHOW == 2)
			print_position(st);

	}
*/	
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
