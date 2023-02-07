/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:38:39 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/02/07 17:17:35 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

enum e_ops {ss, sb, rb, rrb, sa, ra, rra, rr, rrr, pa, pb};

typedef struct s_el
{
	int	v;
	int	a_p;
}	t_el;

typedef struct s_stack	t_stack;

struct s_stack
{
	int		*ini;
	t_el	*cur;
	int		push;
	int		len;
	void	(*free)(t_stack *);
};

void		print_position(t_stack *st);
void		print_stack(t_stack *st);
void		set_operation(t_stack *st, enum e_ops op);
char		*get_ops_str(enum e_ops op);
enum e_ops	get_ops(char *op);
int			get_abs_position(t_stack *st);
void		rot_next_a(t_stack *st, int max_a_p);
void		rot_next_b(t_stack *st, int min_a_p);
int			rot_min_a(t_stack *st, int right);
int			rot_min_a_2(t_stack *st, int min_v, int right);
int			rot_max_b(t_stack *st);
int			set_d_ra(t_stack *st, int d_ra, int d_rra, int right);
int			set_d_rb(t_stack *st, int d_rb, int d_rrb, int left);
void		calculate_3(t_stack *st);
void		calculate_9(t_stack *st);
void		calculate_27(t_stack *st);
void		calculate_81(t_stack *st);
void		calculate_729(t_stack *st);
void		calculate(t_stack *st);
void		to_left(t_stack *st, int last, int last1, int set_rrr);
void		to_left_1(t_stack *st, int last);
int			divide_third(int n);
void		to_right(t_stack *st, int max_b, int last, int last1);
void		to_right_1(t_stack *st, int last, int last1);
void		to_right_2(t_stack *st);
int			relative_ascendant(t_stack *st, int start, int end);
t_stack		*get_args(int argc, char **argv);

#endif
