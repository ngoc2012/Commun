/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 08:17:16 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/26 04:44:47 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
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
	int	*sorted;
	int	push;
	int	len;
	int	score;
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
		ft_printf("\n");
	}
	if (i == st->push)
		ft_printf("   -------\n");
	ft_printf("%5s", "___");
	ft_printf("%5s", "___");
	ft_printf("\n");
	ft_printf("%5s", "ini");
	ft_printf("%5s", "pos");
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
	free(st);
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
	{
		if (st->len - st->position[i] < st->position[i])
			st->position[i] = st->position[i] - st->len;
		if (st->position[i] < 0)
			st->score -= st->position[i];
		else
			st->score += st->position[i];
	}
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
		{
			//ft_printf("st->score - 1 = %d\n", st->score - 1);
			if (st->position[st->push + 1] < 0)
				return (st->score + 1);
			else
				return (st->score - 1);
		}
		else	
		{
			//ft_printf("st->score + 1 = %d\n", st->score + 1);
			if (st->position[st->push] < 0)
				return (st->score - 1);
			else
				return (st->score + 1);
		}
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
		{
			//ft_printf("st->score - 1 = %d\n", st->score - 1);
			if (st->position[st->push - 1] < 0)
				return (st->score + 1);
			else
				return (st->score - 1);
		}
		else	
		{
			//ft_printf("st->score + 1 = %d\n", st->score + 1);
			if (st->position[st->push - 2] < 0)
				return (st->score - 1);
			else
				return (st->score + 1);
		}
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
	if (st->len - new_pos < new_pos)
		new_pos = new_pos - st->len;
	score = st->score - abs(st->position[st->len - 1]) + abs(new_pos);
	//ft_printf("i = %d\n", i);
	i = st->push - 1;
	while (++i < st->len - 1)
	{
		if (st->current[st->len - 1] > st->current[i])
		{
			if (st->position[i] < 0)
			{
				score--;
				
				//if (st->position[i] > 0)
				//	ft_printf("%d\n", st->position[i] - 1);
				//else
				//	ft_printf("%d\n", st->position[i] + 1);
				
			}
			else
			{
				new_pos = st->position[i] + 1;
				if (st->len - new_pos < new_pos)
					new_pos = new_pos - st->len;
				score += abs(new_pos) - abs(st->position[i]);
				
				//if (st->position[i] > 0)
				//	ft_printf("%d\n", st->position[i] + 1);
				//else
				//	ft_printf("%d\n", st->position[i] - 1);
			
			}
		}
		//else
		//	ft_printf("%d\n", st->position[i]);
	}
	//ft_printf("**********\n");
	return (score);
}

int	get_score_rrb(t_stack *st)
{
	int	i;
	int	score;
	int	new_pos;

	//st->print_position(st);
	//ft_printf("st->score = %d\n", st->score);
	if (st->push == 1 || st->push == 0)
		return (st->score);
	if (st->push == 2)
		return (get_score_sb(st));
	//ft_printf("num = %d, abs = %d\n",  st->position[st->len - 1],  abs(st->position[st->len - 1]));
	new_pos = 0;
	i = 0;
	while (++i < st->push)
		if (st->current[0] < st->current[i])
			new_pos++;
	if (st->len - new_pos < new_pos)
		new_pos = new_pos - st->len;
	score = st->score + abs(new_pos);
	//ft_printf("%d\n", i);
	i = 0;
	while (++i < st->push)
	{
		if (st->current[0] > st->current[i])
		{
			if (st->position[i] > 0)
			{
				score--;
				/*
				if (st->position[i] > 0)
					ft_printf("%d\n", st->position[i] - 1);
				else
					ft_printf("%d\n", st->position[i] + 1);
					*/
			}
			else if (st->position[i] < 0)
			{
				score++;
				/*
				if (st->position[i] > 0)
					ft_printf("%d\n", st->position[i] + 1);
				else
					ft_printf("%d\n", st->position[i] - 1);
					*/
			}
		}
		//else
		//	ft_printf("%d\n", st->position[i]);
	}
	//ft_printf("**********\n");
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
	if (st->len - new_pos < new_pos)
		new_pos = new_pos - st->len;
	score = st->score - abs(st->position[st->push]) + abs(new_pos);
	//ft_printf("old_pos %d, new_pos %d\n", st->position[st->push], new_pos);
	i = st->push;
	while (++i < st->len)
	{
		if (st->current[st->push] > st->current[i])
		{
			if (st->position[i] > 0)
			{
				score--;
				/*	
				if (st->position[i] > 0)
					ft_printf("%d\n", st->position[i] - 1);
				else
					ft_printf("%d\n", st->position[i] + 1);
				*/	
			}
			else if (st->position[i] < 0)
			{
				score++;
				/*	
				if (st->position[i] > 0)
					ft_printf("%d\n", st->position[i] + 1);
				else
					ft_printf("%d\n", st->position[i] - 1);
				*/	
			}
		}
		//else
		//	ft_printf("%d\n", st->position[i]);
	}
	//ft_printf("**********\n");
	return (score);
}

int	get_score_rb(t_stack *st)
{
	int	i;
	int	score;
	int	new_pos;

	//st->print_position(st);
	//ft_printf("st->score = %d\n", st->score);
	if (st->push == 1 || st->push == 0)
		return (st->score);
	if (st->push == 2)
		return (get_score_sb(st));
	//ft_printf("num = %d, abs = %d\n",  st->position[st->len - 1],  abs(st->position[st->len - 1]));
	score = st->score - abs(st->position[st->push - 1]);
	//ft_printf("%d\n", i);
	i = -1;
	while (++i < st->push - 1)
	{
		if (st->current[st->push - 1] > st->current[i])
		{
			if (st->position[i] < 0)
			{
				score--;
				/*
				if (st->position[i] > 0)
					ft_printf("%d\n", st->position[i] - 1);
				else
					ft_printf("%d\n", st->position[i] + 1);
					*/
			}
			else
			{
				new_pos = st->position[i] + 1;
				if (st->len - new_pos < new_pos)
					new_pos = new_pos - st->len;
				score += abs(new_pos) - abs(st->position[i]);
				/*
				if (st->position[i] > 0)
					ft_printf("%d\n", st->position[i] + 1);
				else
					ft_printf("%d\n", st->position[i] - 1);
					*/
			}
		}
		//else
		//	ft_printf("%d\n", st->position[i]);
	}
	//ft_printf("**********\n");
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
		return (get_score_ra(st));
	if (ft_strncmp(op, "rrb", 3) == 0)
		return (get_score_rra(st));
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
	int	sum;
	char	*ops[8] = {"sa", "sb", "ra", "rb", "rra", "rrb", "rr", "rrr"};
	//char	*ops[8] = {"rr", "rrr", "ra", "rb", "rra", "rrb", "sa", "sb"};
	char	*op_min;

	op_min = 0;
	min = st->score;
	//ft_printf("min = %d\n", min);
	i = -1;
	while (++i < 8)
	{
		sum = get_score(st, ops[i]);
		//st->print(st);
		if (min > sum)
		{
			min = sum;
			op_min = ops[i];
			//ft_printf("op = %s, sum = %d\n", ops[i], sum);
		}
	}
	return (op_min);
}

void	check_best(t_stack *st, int *last_push)
{
	int		current_push;
	char	*best;

	best = best_operation(st);
	while (best)
	{
		//ft_printf("best operation = %s\n", best);

		if (*last_push > st->push)
		{
			current_push = st->push;
			st->push = *last_push;
			while (--st->push >= current_push)
			{
				//ft_printf("1 ");
				ft_printf("pa\n");

				if (SHOW == 1)
					st->print_stack(st);

			}
			st->push++;
		}
		else if (*last_push < st->push)
		{
			current_push = st->push;
			st->push = *last_push;
			while (++st->push <= current_push)
			{
				//ft_printf("1 ");
				ft_printf("pb\n");

				if (SHOW == 1)
					st->print_stack(st);

			}
			st->push--;
		}
		*last_push = st->push;
		ft_printf("%s\n", best);
		st->set_operation(st, best);
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
	int		last_push;
	//int		current_push;
	//char	*best;

	st->score = 1;
	last_push = 0;
	st->get_position(st);
	if (SHOW == 1)
		st->print_stack(st);
	if (SHOW == 2)
		st->print_position(st);
	while (st->score)
	{
		//ft_printf("score = %d\n", st->score);
		//ft_printf("first half\n");
		//st->print_position(st);
		while (++st->push <= st->len && st->score)
			check_best(st, &last_push);
		//ft_printf("second half\n");
		//st->print_position(st);
		//ft_printf("last_push = %d\n", last_push);
		while (--st->push && st->score)
			check_best(st, &last_push);
	}
	st->push = last_push;
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
	new->len = len;
	new->push = 0;	
	new->calculate = calculate;
	//new->best_operation = best_operation;
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
