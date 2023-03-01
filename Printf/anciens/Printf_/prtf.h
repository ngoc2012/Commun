/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prtf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:08:19 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/12 11:14:03 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRTF_H
# define PRTF_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
# include "libft/libft.h"

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
	char	type;
	t_prtf	*tp;
	size_t	start;
	size_t	end;
	size_t	size;
	size_t	precision;
	int		sign;
	int		zero_flag;
	int		space_flag;
	int		minus_flag;
	int		plus_flag;
	int		dot_flag;
	char	*flag;
	char	*str;
	t_list	*lst;
	size_t	(*print_elmt)(t_elmt *);
	void	(*free_elmt)(void *);
	void	(*get_flags)(t_elmt *);
	void	(*set_flags)(t_elmt *);
};

t_elmt	*ft_new_elmt(char type, t_prtf *tp, size_t start, size_t end);
t_prtf	*ft_new_prtf(const char *str);
char	*ft_itoa_base(char *base, long unsigned int i);
char	*ft_usitoa(unsigned int n);

#endif
