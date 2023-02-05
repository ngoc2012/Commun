/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:38:39 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/02/05 07:29:05 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"

enum e_ops {ss, sb, rb, rrb, sa, ra, rra, rr, rrr, pa, pb};

typedef struct s_el
{
	int	v;
	int	a_p;
}	t_el;

typedef struct s_stack	t_stack;

struct s_stack
{
	int	*ini;
	t_el	*cur;
	int	push;
	int	len;
	int	r_sc_a;
	void	(*calculate)(t_stack *);
	int	(*get_score)(t_stack *, enum e_ops);
	void	(*get_position)(t_stack *);

	void	(*free)(t_stack *);
};

void	print_position(t_stack *);
void	print_stack(t_stack *);
void	set_operation(t_stack *st, enum e_ops op);
char	*get_ops_str(enum e_ops op);
enum e_ops	get_ops(char *op);
void	unset_operation(t_stack *st, enum e_ops op);
int	get_score_sa(t_stack *st);
int	get_score_sb(t_stack *st);
int	get_score_ss(t_stack *st);
int	get_score_rra(t_stack *st);
int	get_score_rrb(t_stack *st);
int	get_score_ra(t_stack *st);
int	get_score_rb(t_stack *st);
int	get_score(t_stack *st, enum e_ops op);
void	get_abs_position(t_stack *st);
void	rot_next_a(t_stack *st, int max_a_p);
void	rot_next_b(t_stack *st, int min_a_p);
int	rot_min_a(t_stack *st, int right);
int	rot_min_a_2(t_stack *st, int min_v, int right);
void	rot_max_b(t_stack *st);
int	set_d_ra(t_stack *st, int d_ra, int d_rra, int right);
int	set_d_rb(t_stack *st, int d_rb, int d_rrb, int left);
void	calculate_3(t_stack *st);
void	calculate_9(t_stack *st);
void	calculate_27(t_stack *st);
void	calculate_81(t_stack *st);
void	calculate_243(t_stack *st);
void	calculate_729(t_stack *st);
void	calculate(t_stack *st);
void	to_left(t_stack *st, int last, int last1, int set_rrr);
void	to_left_1(t_stack *st, int last);
int	divide_third(int n);
void	to_right(t_stack *st, int max_b, int last, int last1);
void	to_right_1(t_stack *st, int last, int last1);
void	to_right_2(t_stack *st);
int	relative_ascendant(t_stack *st, int start, int end);

#endif
