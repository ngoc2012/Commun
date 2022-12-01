/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:08:19 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/01 09:58:14 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
# include "Libft/libft.h"

typedef struct s_prtf	t_prtf;

struct s_prtf
{
	const char	*str;
	int			error;
	char		*types;
	char		*flags;
	char		*nums;
	char		*numflags;
	t_list		*elmts;
	size_t		(*print_elmts)(t_prtf *);
	void		(*free_prtf)(t_prtf *);
};

typedef struct s_elmt	t_elmt;

struct s_elmt
{
	size_t	size;
	size_t	precision;
	size_t	start;
	size_t	end;
	char	type;
	int		sign;
	int		zero_flag;
	int		space_flag;
	int		minus_flag;
	int		plus_flag;
	char	*flag;
	char	*str;
	t_list	*lst;
	t_prtf	*tp;
	size_t	(*print_elmt)(t_elmt *);
	void	(*free_elmt)(void *);
	void	(*get_prop)(t_elmt *);
	void	(*set_prop)(t_elmt *);
	size_t	(*print_lst)(t_elmt *);
	size_t	(*size_lst)(t_elmt *);
};

t_elmt	*ft_new_elmt(char type, t_prtf *tp, size_t start, size_t end);
t_prtf	*ft_new_prtf(const char *str);
char	*ft_itoa_base(char *base, void *nbr);
char	*ft_usitoa(unsigned int n);

#endif
