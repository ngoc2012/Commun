/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:38:39 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/01/13 11:03:09 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define MANUAL 0
# define SHOW 0
# define SCORE 0

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
	int	p;
	int	r_p_a;
	int	a_p;
	int	a_p_a;
}	t_el;

typedef struct s_stack	t_stack;

struct s_stack
{
	int	*ini;
	t_el	*cur;
	int	push;
	int	len;
	int	r_sc;
	int	r_sc_a;
	int	score;
	int	score_a;
	void	(*calculate)(t_stack *);
	int	(*get_score)(t_stack *, enum e_ops);
	void	(*get_position)(t_stack *);

	void	(*free)(t_stack *);
};

void	unset_operation(t_stack *, enum e_ops);
void	set_operation(t_stack *, enum e_ops);
void	print_position(t_stack *);
void	print_stack(t_stack *);
void	get_position(t_stack *st);
int	position(t_stack *st, int i0);
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

#endif
