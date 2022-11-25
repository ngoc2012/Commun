/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:08:19 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/25 16:30:30 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "Libft/libft.h"

typedef struct s_printf
{
	va_list	ap;
	int		i;
	int		start;
	size_t	limit;
	size_t	size;
	char	type;
	char	fill;
	char	prefix;
	char	*types;
	char	*flag;
	char	*all_flags;
	char	*base10;
	char	*hex;
	char	*hex_cap;
	char	*numbers;
	t_list	*out;
}	t_printf;

typedef struct s_content
{
	char	type;
	char	*str;
}	t_content;

char	*ft_usitoa(unsigned int n);
char	*ft_itoa_base(char *base, void *nbr);
int		ft_printf(const char *s, ...);
void	get_type_prop(const char *s, t_printf *tp);
void	get_cspu(t_printf *tp);
int		get_xx(t_printf *tp, char *hex);
void	get_idxx(t_printf *tp);
int		get_type(const char *s, t_printf *tp);
int		get_number(const char *s, t_printf *tp);
void	get_str(const char *s, t_printf *tp);
char	*get_0x(char *str, const char *res);
int		set_size(t_printf *tp);
void	get_fill_prefix(t_printf *tp, t_list *last);
int		set_fill_prefix(t_printf *tp, t_list *last);

#endif
