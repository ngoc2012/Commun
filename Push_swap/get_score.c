/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_score.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:17:03 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/01/05 18:38:23 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_score_sa(t_stack *st)
{
	if (st->len - st->push < 2)
		return (st->score);
	else
	{
		//ft_printf("i[push] = %d, i[push+1] = %d\n", st->cur[st->push], st->cur[st->push + 1]);
		if (st->cur[st->push].v > st->cur[st->push + 1].v)
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
		return (st->score);
	else
	{
		//ft_printf("i[push] = %d, i[push+1] = %d\n", st->cur[st->push], st->cur[st->push + 1]);
		if (st->cur[st->push - 2].v > st->cur[st->push - 1].v)
			return (st->score - 1);
		else	
			return (st->score + 1);
	}
}

int	get_score_ss(t_stack *st)
{
	int	score;

	score = st->score;
	//st->print_position(st);
	//ft_printf("st->score = %d\n", st->score);
	if (st->len - st->push >= 2)
	{
		//ft_printf("st->score = %d\n", st->score);
		if (st->cur[st->push].v > st->cur[st->push + 1].v)
			score--;
		else	
			score++;
	}
	if (st->push >= 2)
	{
		//ft_printf("i[push] = %d, i[push+1] = %d\n", st->cur[st->push], st->cur[st->push + 1]);
		if (st->cur[st->push - 2].v > st->cur[st->push - 1].v)
			score--;
		else	
			score++;
	}
	return (score);
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
		if (st->cur[st->len - 1].v < st->cur[i].v)
			new_pos++;
	score = st->score - st->cur[st->len - 1].p + new_pos;
	//ft_printf("i = %d\n", i);
	i = st->push - 1;
	while (++i < st->len - 1)
		if (st->cur[st->len - 1].v > st->cur[i].v)
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
		if (st->cur[0].v < st->cur[i].v)
			new_pos++;
	score = st->score + new_pos;
	i = 0;
	while (++i < st->push)
		if (st->cur[0].v > st->cur[i].v)
			score--;
	return (score);
}

int	get_score_ra(t_stack *st)
{
	int	i;
	int	score;
	int	new_pos;

	if (st->len - st->push == 1 || st->push == st->len)
		return (st->score);
	if (st->len - st->push == 2)
		return (get_score_sa(st));
	new_pos = st->cur[st->push].p;
	i = st->push;
	while (++i < st->len)
		if (st->cur[st->push].v < st->cur[i].v)
			new_pos++;
	score = st->score - st->cur[st->push].p + new_pos;
	i = st->push;
	while (++i < st->len)
		if (st->cur[st->push].v > st->cur[i].v)
			score--;
	return (score);
}

int	get_score_rb(t_stack *st)
{
	int	i;
	int	score;

	if (st->push == 1 || st->push == 0)
		return (st->score);
	if (st->push == 2)
		return (get_score_sb(st));
	score = st->score - st->cur[st->push - 1].p;
	i = -1;
	while (++i < st->push - 1)
		if (st->cur[st->push - 1].v > st->cur[i].v)
			score++;
	return (score);
}

int	get_score(t_stack *st, enum e_ops op)
{
	if (op == sa)
		return (get_score_sa(st));
	if (op == sb)
		return (get_score_sb(st));
	if (op == ss)
		return (get_score_ss(st));
	if (op == ra)
		return (get_score_ra(st));
	if (op == rra)
		return (get_score_rra(st));
	if (op == rb)
		return (get_score_rb(st));
	if (op == rrb)
		return (get_score_rrb(st));
	if (op == rr)
		return (get_score_ra(st) + get_score_rb(st) - st->score);
	if (op == rrr)
		return (get_score_rra(st) + get_score_rrb(st) - st->score);
	return (-1);
}

