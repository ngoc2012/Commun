/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:08:19 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/29 21:41:43 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdio.h>

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
# include "Libft/libft.h"

typedef struct s_printf
{
	va_list	ap;
	int		i;
	int		start;
	char	*all_types;
	char	*all_flags;
	char	*base10;
	char	*hex;
	char	*hex_cap;
	char	*numbers;
	t_list	*elmnts;
}	t_printf;

typedef struct s_elmt
{
	size_t	limit;
	size_t	size;
	char	type;
	char	fill;
	char	prefix;
	char	*flag;
	char	*str;
	void	*print_elmt;
	void	*free_elmt;
}	t_elmt;

char	*ft_usitoa(unsigned int n);
char	*ft_itoa_base(char *base, void *nbr);
int		ft_printf(const char *s, ...);
void	get_type_prop(const char *s, t_printf *tp);
int		get_cs(t_printf *tp);
int		get_pu(t_printf *tp);
t_elmt	*get_xx(t_printf *tp, char *hex);
void	get_idxx(t_printf *tp);
int		get_type(const char *s, t_printf *tp);
int		get_number(const char *s, t_printf *tp);
void	get_str(const char *s, t_printf *tp);
char	*get_0x(char *str, const char *res);
int		set_size(t_printf *tp);
void	get_fill_prefix(t_printf *tp, char *lcs);
char		*set_fill_prefix(t_printf *tp, char *lcs);
t_elmt	*ft_new_elmt(char type, char *str);
int	ft_print_elmnts(t_printf *tp);

#endif
