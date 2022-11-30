/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:08:19 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/30 17:35:33 by minh-ngu         ###   ########.fr       */
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
	int	error;
	char	*types;
	char	*flags;
	char	*nums;
	char	*numflags;
	t_list	*elmts;
	size_t	(*print_elmts)(t_prtf *);
	void	(*free_prtf)(t_prtf *);
};

typedef struct s_elmt	t_elmt;

struct s_elmt
{
	size_t	limit;
	size_t	size;
	size_t	start;
	size_t	end;
	char	type;
	char	*flag;
	char	*str;
	t_list	*lst;
	t_prtf	*tp;
	size_t	(*print_elmt)(t_elmt *);
	void	(*free_elmt)(void *);
	void	(*get_prop)(t_elmt *);
	void	(*set_prop)(t_elmt *);
	size_t	(*print_lst)(t_elmt *, int);
};

t_elmt	*ft_new_elmt(char type, t_prtf *tp, size_t start, size_t end);
t_prtf	*ft_new_prtf(const char *);
char	*ft_itoa_base(char *base, void *nbr);
char	*ft_usitoa(unsigned int n);

#endif
