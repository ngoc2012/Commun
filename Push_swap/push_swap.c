/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/01/01 22:38:27 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
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
*/

typedef struct s_stack	t_stack;

struct s_stack
{
	int	*ini;
	int	*current;
	int	*position;
	int	*abs_pos;
	int	*pos_ind;
	int	*sorted;
	int	push;
	int	len;
	int	score;
	int	b_max_abs_pos;
	int	b_min_abs_pos;
	int	prev_ind;
	int	next_ind;
	void	(*calculate)(t_stack *);
	int	(*get_score)(t_stack *, char *);
	void	(*unset_operation)(t_stack *, char *);
	void	(*set_operation)(t_stack *, char *);
	void	(*get_position)(t_stack *);
	void	(*print_position)(t_stack *);
	void	(*print_stack)(t_stack *);
	void	(*free)(t_stack *);
};

void	print_position(t_stack *st)
{
	int	i;

	i = -1;
	while (++i < st->len)
	{
		if (i == st->push)
			ft_printf("   -------\n");
		ft_printf("%5d", st->current[i]);
		ft_printf("%5d", st->position[i]);
		ft_printf("%5d", st->abs_pos[i]);
		ft_printf("%5d", st->pos_ind[i]);
		ft_printf("\n");
	}
	if (i == st->push)
		ft_printf("   -------\n");
	ft_printf("%5s", "___");
	ft_printf("%5s", "___");
	ft_printf("\n");
	ft_printf("%5s", "ini");
	ft_printf("%5s", "pos");
	ft_printf("%5s", "abs");
	ft_printf("%5s", "ind");
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
			ft_printf("%5d", st->current[i]);
		else if (i > st->len - 1 - st->push)
			ft_printf("%5s", "");
		if (i > st->len - 1 - st->push)
			ft_printf("%5d", st->current[st->len - 1 - i]);
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

int	*cp_array(int *ini, int len)
{
	int	*new;
	
	new = malloc(sizeof(int) * len);
	if (!new)
		return (0);
	while (--len >= 0)
		new[len] = ini[len];
	return (new);
}

void	free_stack(t_stack *st)
{
	free(st->ini);
	free(st->current);
	free(st->position);
	free(st->abs_pos);
	free(st->pos_ind);
	free(st);
}

int	get_score_a(t_stack *st, int start, int end)
{
	int	i;
	int	score;

	score = 0;
	i = start - 1;
	while (++i < end)
		score += st->position[i];
	return (score);
}

void	get_position(t_stack *st)
{
	int	i;
	int	j;

	i = -1;
	while (++i < st->len)
	{
		st->position[i] = 0;
		j = -1;
		while (++j < i)
		{
			if (st->current[j] > st->current[i])
				st->position[i]++;
		}
	}
	st->score = 0;
	i = -1;
	while (++i < st->len)
		st->score += st->position[i];
}

void	set_operation(t_stack *st, char *op)
{
	int	i;
	int	j;

	//ft_printf("%s :\n", op);
	if ((ft_strncmp(op, "sa", 2) == 0 || ft_strncmp(op, "ss", 2) == 0) && st->len - st->push >= 2)
	{
		j = st->current[st->push];
		st->current[st->push] = st->current[st->push + 1]; 
		st->current[st->push + 1] = j;
		//st->print(st);
		//return ;
	}
	if ((ft_strncmp(op, "sb", 2) == 0 || ft_strncmp(op, "ss", 2) == 0) && st->push >= 2)
	{
		j = st->current[st->push - 1];
		st->current[st->push - 1] = st->current[st->push - 2]; 
		st->current[st->push - 2] = j;
		//st->print(st);
		//return ;
	}
	if ((ft_strncmp(op, "ra", 3) == 0 || ft_strncmp(op, "rr", 3) == 0) && st->len - st->push >= 2)
	{
		//ft_printf("ra\n");
		i = st->push;
		while (i < st->len - 1)
		{
			j = st->current[i];
			st->current[i] = st->current[i + 1]; 
			st->current[i + 1] = j;
			i++;
		}
		//st->print(st);
		//return ;
	}
	if ((ft_strncmp(op, "rrb", 3) == 0 || ft_strncmp(op, "rrr", 3) == 0) && st->push >= 2)
	{
		//ft_printf("rrb\n");
		i = 0;
		while (i < st->push - 1)
		{
			j = st->current[i];
			st->current[i] = st->current[i + 1]; 
			st->current[i + 1] = j;
			i++;
		}
		//st->print(st);
		//return ;
	}
	if ((ft_strncmp(op, "rra", 3) == 0 || ft_strncmp(op, "rrr", 3) == 0) && st->len - st->push >= 2)
	{
		//ft_printf("rra\n");
		i = st->len - 1;
		while (i > st->push)
		{
			j = st->current[i];
			st->current[i] = st->current[i - 1]; 
			st->current[i - 1] = j;
			i--;
		}
		//st->print(st);
		//return ;
	}
	if ((ft_strncmp(op, "rb", 3) == 0 || ft_strncmp(op, "rr", 3) == 0) && st->push >= 2)
	{
		//ft_printf("rb\n");
		i = st->push - 1;
		while (i > 0)
		{
			j = st->current[i];
			st->current[i] = st->current[i - 1]; 
			st->current[i - 1] = j;
			i--;
		}
		//st->print(st);
		//return ;
	}
	if (ft_strncmp(op, "pa", 2) == 0 && st->push > 0)
	{
		st->push--;
		//st->print(st);
	}
	if (ft_strncmp(op, "pb", 2) == 0 && st->push < st->len)
	{
		st->push++;
		//st->print(st);
	}
}

void	unset_operation(t_stack *st, char *op)
{
	if (ft_strncmp(op, "sa", 3) == 0)
		st->set_operation(st, "sa");
	if (ft_strncmp(op, "ra", 3) == 0)
		st->set_operation(st, "rra");
	if (ft_strncmp(op, "rra", 3) == 0)
		st->set_operation(st, "ra");
	if (ft_strncmp(op, "sb", 3) == 0)
		st->set_operation(st, "sb");
	if (ft_strncmp(op, "rb", 3) == 0)
		st->set_operation(st, "rrb");
	if (ft_strncmp(op, "rrb", 3) == 0)
		st->set_operation(st, "rb");
	if (ft_strncmp(op, "rr", 3) == 0)
		st->set_operation(st, "rrr");
	if (ft_strncmp(op, "rrr", 3) == 0)
		st->set_operation(st, "rr");
	st->get_position(st);
}

int	get_score_sa(t_stack *st)
{
	//st->print_position(st);
	//ft_printf("st->score = %d\n", st->score);
	if (st->len - st->push < 2)
	{
		//ft_printf("st->score = %d\n", st->score);
		return (st->score);
	}
	else
	{
		//ft_printf("i[push] = %d, i[push+1] = %d\n", st->current[st->push], st->current[st->push + 1]);
		if (st->current[st->push] > st->current[st->push + 1])
			return (st->score - 1);
		else	
			return (st->score + 1);
	}
}

int	get_score_sb(t_stack *st)
{
	//st->print_position(st);
	//ft_printf("st->score = %d\n", st->score);
	if (st->push < 2)
	{
		//ft_printf("st->score = %d\n", st->score);
		return (st->score);
	}
	else
	{
		//ft_printf("i[push] = %d, i[push+1] = %d\n", st->current[st->push], st->current[st->push + 1]);
		if (st->current[st->push - 2] > st->current[st->push - 1])
			return (st->score - 1);
		else	
			return (st->score + 1);
	}
}

int	get_score_rra(t_stack *st)
{
	int	i;
	int	score;
	int	new_pos;

	//st->print_position(st);
	//ft_printf("st->score = %d\n", st->score);
	if (st->len - st->push == 1 || st->push == st->len)
		return (st->score);
	if (st->len - st->push == 2)
		return (get_score_sa(st));
	//ft_printf("num = %d, abs = %d\n",  st->position[st->len - 1],  abs(st->position[st->len - 1]));
	new_pos = 0;
	i = -1;
	while (++i < st->push)
		if (st->current[st->len - 1] < st->current[i])
			new_pos++;
	score = st->score - st->position[st->len - 1] + new_pos;
	//ft_printf("i = %d\n", i);
	i = st->push - 1;
	while (++i < st->len - 1)
		if (st->current[st->len - 1] > st->current[i])
			score++;
	return (score);
}

int	get_score_rrb(t_stack *st)
{
	int	i;
	int	score;
	int	new_pos;

	if (st->push == 1 || st->push == 0)
		return (st->score);
	if (st->push == 2)
		return (get_score_sb(st));
	new_pos = 0;
	i = 0;
	while (++i < st->push)
		if (st->current[0] < st->current[i])
			new_pos++;
	score = st->score + new_pos;
	i = 0;
	while (++i < st->push)
		if (st->current[0] > st->current[i])
			score--;
	return (score);
}

int	get_score_ra(t_stack *st)
{
	int	i;
	int	score;
	int	new_pos;

	//st->print_position(st);
	//ft_printf("st->score = %d\n", st->score);
	if (st->len - st->push == 1 || st->push == st->len)
		return (st->score);
	if (st->len - st->push == 2)
		return (get_score_sa(st));
	//ft_printf("num = %d, abs = %d\n",  st->position[st->len - 1],  abs(st->position[st->len - 1]));
	new_pos = st->position[st->push];
	i = st->push;
	//ft_printf("st->push = %d\n", st->push);
	//ft_printf("start i = %d\n", i + 1);
	while (++i < st->len)
		if (st->current[st->push] < st->current[i])
			new_pos++;
	//ft_printf("end i = %d\n", i - 1);
	score = st->score - st->position[st->push] + new_pos;
	//ft_printf("old_pos %d, new_pos %d\n", st->position[st->push], new_pos);
	i = st->push;
	while (++i < st->len)
		if (st->current[st->push] > st->current[i])
			score--;
	//ft_printf("**********\n");
	return (score);
}

int	get_score_rb(t_stack *st)
{
	int	i;
	int	score;
	//int	new_pos;

	//st->print_position(st);
	//ft_printf("st->score = %d\n", st->score);
	if (st->push == 1 || st->push == 0)
		return (st->score);
	if (st->push == 2)
		return (get_score_sb(st));
	//ft_printf("num = %d, abs = %d\n",  st->position[st->len - 1],  abs(st->position[st->len - 1]));
	score = st->score - st->position[st->push - 1];
	//ft_printf("%d\n", i);
	i = -1;
	while (++i < st->push - 1)
		if (st->current[st->push - 1] > st->current[i])
			score++;
	return (score);
}

int	get_score(t_stack *st, char *op)
{
	if (ft_strncmp(op, "sa", 3) == 0)
		return (get_score_sa(st));
	if (ft_strncmp(op, "sb", 3) == 0)
		return (get_score_sb(st));
	if (ft_strncmp(op, "ra", 3) == 0)
		return (get_score_ra(st));
	if (ft_strncmp(op, "rra", 3) == 0)
		return (get_score_rra(st));
	if (ft_strncmp(op, "rb", 3) == 0)
		return (get_score_rb(st));
	if (ft_strncmp(op, "rrb", 3) == 0)
		return (get_score_rrb(st));
	if (ft_strncmp(op, "rr", 3) == 0)
		return (get_score_ra(st) + get_score_rb(st) - st->score);
	if (ft_strncmp(op, "rrr", 3) == 0)
		return (get_score_rra(st) + get_score_rrb(st) - st->score);
	//ft_printf("current st->score %d\n", st->score);
/*	
	int	score;

	st->set_operation(st, op);
	st->get_position(st);
	score = st->score;
	st->unset_operation(st, op);
	if (ft_strncmp(op, "rrr", 3) == 0)
	{
		//if (score != get_score_ra(st))
		if (score != get_score_rra(st) + get_score_rrb(st) - st->score)
		{
			ft_printf("==============================================\n");
			ft_printf("st->push = %d\n", st->push);
			//ft_printf("current score %d, score %d, get_score_rr %d\n", st->score, score, get_score_rr(st));
			ft_printf("current score %d, score %d, get_score_rra %d, get_score_rrb %d\n", st->score, score, get_score_rra(st), get_score_rrb(st));
			st->print_position(st);
			st->set_operation(st, op);
			st->get_position(st);
			st->print_position(st);
			st->unset_operation(st, op);
			ft_printf("==============================================\n");
		}
	}
	return (score);
*/	
	return (-1);
}

char	*best_operation(t_stack *st)
{
	int	min;
	int	i;
	int	scores[8];
	char	*ops[8] = {"sb", "rb", "rrb", "sa", "ra", "rra", "rr", "rrr"};
	//char	*ops[8] = {"sa", "sb", "ra", "rb", "rra", "rrb", "rr", "rrr"};
	//char	*ops[8] = {"rr", "rrr", "ra", "rb", "rra", "rrb", "sa", "sb"};
	char	*op_min;

	//ft_printf("push = %d\n", st->push);
	if (SCORE)
		ft_printf("score = %d\n", st->score);
	op_min = 0;
	min = st->score;
	i = -1;
	while (++i < 8)
	{
		scores[i] = get_score(st, ops[i]);
		if (i <= 2 && st->push < 2)
			scores[i] = st->score + 100;
		if (i > 2 && st->len - st->push < 2)
			scores[i] = st->score + 100;
		if (SCORE)
			ft_printf("%s %d, ", ops[i], scores[i] - st->score);
		//st->print(st);
		if (min >= scores[i])
		{
			min = scores[i];
			op_min = ops[i];
			//ft_printf("op = %s, sum = %d\n", ops[i], sum);
		}
	}
	if (SCORE)
		ft_printf("\nmin = %d\n", min);
	if (scores[1] == min && scores[6] == min)
		op_min = ops[1];
	if (scores[4] == min && scores[6] == min)
		op_min = ops[4];
	if (scores[2] == min && scores[7] == min)
		op_min = ops[2];
	if (scores[5] == min && scores[7] == min)
		op_min = ops[5];
	if (scores[4] == min && scores[5] == min)
	{
		if (st->current[0] > st->current[st->len - 2])
			op_min = ops[4];
		else
			op_min = ops[5];
	}
	return (op_min);
}

int	abs_position(t_stack *st, int i0)
{
	int	i;
	int	pos;

	pos = 0;
	i = -1;
	while (++i < st->len)
		if (i != i0 && st->current[i] < st->current[i0])
			pos++;
	//ft_printf("val = %d, pos = %d\n", st->ini[i0],  pos);
	return (pos);
}

int	position(t_stack *st, int i0)
{
	int	i;
	int	pos;

	pos = 0;
	i = i0;
	while (++i < st->len)
		if (st->current[i] < st->current[i0])
			pos++;
	//ft_printf("val = %d, pos = %d\n", st->current[i0],  pos);
	return (pos);
}

int	min_a(t_stack *st)
{
	int	i;
	int	v_min;

	if (st->len - st->push <= 0)
		return (INT_MAX);
	v_min = st->current[st->push];
	i = st->push;
	while (++i < st->len)
		if (v_min > st->current[i])
			v_min = st->current[i];
	return (v_min);
}

int	max_b(t_stack *st)
{
	int	i;
	int	v_max;

	if (st->push == 0)
		return (INT_MIN);
	v_max = st->current[0];
	i = 0;
	while (++i < st->push)
		if (v_max < st->current[i])
			v_max = st->current[i];
	return (v_max);
}

void	get_abs_position(t_stack *st)
{
	int	i;

	i = -1;
	while (++i < st->len)
		st->abs_pos[i] = abs_position(st, i);
	i = -1;
	while (++i < st->len)
		st->pos_ind[st->abs_pos[i]] = i;
}

void	get_next(t_stack *st, int start, int end)
{
	int	j;
	int	direction;
	int	dis;
	char	*ops[3] = {"rra", "", "ra"};

	// direction = 1 -> ra, direction = -1 -> rra
	direction = 1;
	if (start > end)
		direction *= -1;
	dis = abs(start - end);
	if (SHOW)
		ft_printf("direction = %d\n", direction);
	if (SHOW)
		ft_printf("start = %d, end = %d, dis = %d\n", start, end, dis);
	if (dis + dis > st->len)
	{
		dis = st->len - st->push - dis;
		direction *= -1;
	}
	if (SHOW)
		ft_printf("direction = %d\n", direction);
	if (SHOW)
		ft_printf("dis = %d\n", dis);
	j = -1;
	while (++j < dis)
	{
		ft_printf("%s\n", ops[direction + 1]);
		st->set_operation(st, ops[direction + 1]);

		if (SHOW == 1)
			st->print_stack(st);
		if (SHOW == 2)
			st->print_position(st);
	}
	ft_printf("pb\n");
	st->push++;
	if (SHOW == 1)
		st->print_stack(st);
	if (SHOW == 2)
		st->print_position(st);
}

void	next_push(t_stack *st)
{
	//int	j;
	int	prev_dis;
	int	next_dis;

	//j = -1;
	//while (++j < i)
	//	ft_printf("pb\n");
	//st->push += i;

	if (SHOW)
		ft_printf("========== next_push =========\n");

	get_abs_position(st);
	if (st->push == 0)
	{
		st->b_max_abs_pos = st->abs_pos[st->push];
		st->b_min_abs_pos = st->abs_pos[st->push];

		ft_printf("pb\n");
		st->push++;

		if (SHOW == 1)
			st->print_stack(st);
		if (SHOW)
			st->print_position(st);


		return ;
	}

	if (SHOW == 1)
		st->print_stack(st);
	if (SHOW)
		st->print_position(st);
	
	if (st->b_max_abs_pos + 1 <= st->len - 1)
		st->next_ind = st->pos_ind[st->b_max_abs_pos + 1];
	else
		st->next_ind = -1;

	if (st->b_min_abs_pos - 1 >= 0)
		st->prev_ind = st->pos_ind[st->b_min_abs_pos - 1];
	else
		st->prev_ind = -1;
	
	if (SHOW)
		ft_printf("b_max_abs_pos = %d, b_min_abs_pos = %d\n", st->b_max_abs_pos, st->b_min_abs_pos);
	if (SHOW)
		ft_printf("push = %d, prev_ind = %d, next_ind = %d\n", st->push, st->prev_ind, st->next_ind);
	prev_dis = abs(st->prev_ind - st->push); 
	if (prev_dis > st->len - prev_dis)
		prev_dis = st->len - st->push - prev_dis;
	next_dis = abs(st->next_ind - st->push); 
	if (next_dis > st->len - next_dis)
		next_dis = st->len - st->push - next_dis;

	if (SHOW)
		ft_printf("prev_dis = %d, next_dis = %d\n", prev_dis, next_dis);
	if (st->prev_ind != -1 && (prev_dis < next_dis || st->next_ind == -1))
	{
		if (SHOW)
			ft_printf("Get prev\n");
		get_next(st, st->push, st->prev_ind);
		ft_printf("rb\n");
		st->set_operation(st, "rb");
		if (SHOW == 1)
			st->print_stack(st);
		if (SHOW == 2)
			st->print_position(st);
		st->b_min_abs_pos--;
	}
	else if (st->next_ind != -1)
	{
		if (SHOW)
			ft_printf("Get next\n");
		get_next(st, st->push, st->next_ind);
		st->b_max_abs_pos++;
	}
}

//void	check_best(t_stack *st, int *last_push)
void	check_best(t_stack *st)
{
	//int		current_push;
	char	*best;
	int	last_score;

	if (SHOW)
		ft_printf("========== check best =========\n");
	best = best_operation(st);
	if (!best)
	{
		if (st->push > 0)
		{
			st->push--;
			best = best_operation(st);
			if (best)
			{
				ft_printf("pa\n");
				ft_printf("%s\n", best);
				st->set_operation(st, best);
			}
			else
				st->push++;
		}
		if (st->push > 0)
		{
			st->push--;
			best = best_operation(st);
			if (best)
			{
				ft_printf("pa\n");
				ft_printf("%s\n", best);
				st->set_operation(st, best);
			}
			else
				st->push++;
		}
	}
	while (best && st->score)
	{
		//ft_printf("best operation = %s\n", best);

		last_score = st->score;
		st->set_operation(st, best);
		st->get_position(st);
		get_abs_position(st);
		if (last_score == st->score && st->abs_pos[st->push] >= st->b_min_abs_pos - 1 && st->abs_pos[st->push] <= st->b_max_abs_pos + 1)
		{
			if (SHOW)
			{
				st->print_position(st);
				ft_printf("Unset %s\n", best);
			}
			st->unset_operation(st, best);
			next_push(st);
		}
		else	
			ft_printf("%s\n", best);
		st->get_position(st);

		if (SHOW == 1)
			st->print_stack(st);
		if (SHOW == 2)
			st->print_position(st);

		best = best_operation(st);
	}
}

void	calculate(t_stack *st)
{
	//int	last_push;

	st->score = 1;
	st->push = 0;
	st->get_position(st);
	if (SHOW)
		ft_printf("score = %d\n", st->score);
	if (SHOW)
		st->print_stack(st);

	//last_push = st->push;
	while (st->push < st->len - 1 && st->score)
	{
		//check_best(st, &last_push);
		check_best(st);
		if (st->score)
			next_push(st);
		st->get_position(st);
	}
	//else {

		//ft_printf("push = %d\n", st->push);
	//last_push = st->push;
	//st->push--;
	//while (st->score)
	//{
	//	while (++st->push <= st->len && st->score)
	//		check_best(st, &last_push);
	//	while (--st->push && st->score)
	//		check_best(st, &last_push);
	//}
	//st->push = last_push;
	////}
	while (st->push--)
	{
		ft_printf("pa\n");

		if (SHOW == 1)
			st->print_stack(st);

	}
}

t_stack	*new_stack(int *ini, int len)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (0);
	new->ini = ini;
	new->current = cp_array(ini, len);
	new->position = malloc(sizeof(int) * len);
	if (!new->position)
		return (0);
	new->abs_pos = malloc(sizeof(int) * len);
	if (!new->abs_pos)
		return (0);
	new->pos_ind = malloc(sizeof(int) * len);
	if (!new->pos_ind)
		return (0);
	new->len = len;
	new->push = 0;	
	new->b_max_abs_pos = 0;
	new->b_min_abs_pos = 0;
	new->calculate = calculate;
	new->unset_operation = unset_operation;
	new->set_operation = set_operation;
	new->get_position = get_position;
	new->print_position = print_position;
	new->print_stack = print_stack;
	new->free = free_stack;
	return (new);
}

int	main(int argc, char **argv)
{
	int		i;
	int		fd;
	int		*ini;
	t_stack		*st;
	char	*s;
	char	*ops[8] = {"sb", "rb", "rrb", "sa", "ra", "rra", "rr", "rrr"};
	int	scores[8];

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
	if (!MANUAL)
		st->calculate(st);
	//st->print_position(st);
	//ft_printf("Score :%d\n", st->score);
	if (MANUAL)
	{
		st->get_position(st);
		if (SHOW == 1)
			st->print_stack(st);
		if (SHOW == 2)
			st->print_position(st);
		fd = open("operations.txt", O_RDONLY);
		while ((s = get_next_line(fd)))
		{
			if (SCORE)
			{
				i = -1;
				while (++i < 8)
				{
					scores[i] = get_score(st, ops[i]);
					ft_printf("%s %d, ", ops[i], scores[i] - st->score);
				}
				ft_printf("\n");
			}
			if (s[ft_strlen(s) - 1] == '\n')
				s[ft_strlen(s) - 1] = 0;
			ft_printf("%s\n", s);
			st->set_operation(st, s);
			st->get_position(st);
			if (SHOW == 1)
				st->print_stack(st);
			if (SHOW == 2)
				st->print_position(st);
			free(s);
		}
	}
	st->free(st);
}
