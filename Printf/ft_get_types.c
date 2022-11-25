/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:23:54 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/25 14:06:11 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include "Libft/libft.h"
#include "ft_printf.h"

void	get_type_prop(const char *s, t_printf *tp)
{
	get_str(s, tp);
	tp->i++;
	while ((ft_strchr(tp->all_flags, s[tp->i])
			|| ft_strchr(tp->base10, s[tp->i]))
		&& s[tp->i] && !ft_strchr(tp->types, s[tp->i]))
	{
		if (s[tp->i] == '.')
		{
			tp->i++;
			if (s[tp->i] != '0')
				tp->size = get_number(s, tp);
		}
		while (s[tp->i] && (ft_strchr(tp->all_flags, s[tp->i]))
			&& !ft_strchr(tp->types, s[tp->i]))
		{
			if (!ft_strchr(tp->flag, s[tp->i]))
				ft_strlcat(tp->flag, &s[tp->i], ft_strlen(tp->flag) + 2);
			tp->i++;
		}
		if (ft_strchr(tp->base10, s[tp->i]))
			tp->limit = get_number(s, tp);
	}
	if (ft_strchr(tp->types, s[tp->i]))
		tp->type = s[tp->i];
}

void	get_cspu(t_printf *tp)
{
	int		ar;
	char	*str;

	if (tp->type == 's')
	{
		str = ft_strdup((const char *) va_arg(tp->ap, char *));
		ft_lstadd_back(&tp->out, ft_lstnew(str));
	}
	if (tp->type == 'p')
	{
		str = ft_itoa_base(tp->hex, va_arg(tp->ap, void *));
		ft_lstadd_back(&tp->out, ft_lstnew(get_0x(str, "(nil)")));
	}
	if (tp->type == 'u')
	{
		ar = va_arg(tp->ap, int);
		if (ar >= 0)
			ft_lstadd_back(&tp->out, ft_lstnew(ft_itoa(ar)));
		else
			ft_lstadd_back(&tp->out, ft_lstnew(ft_usitoa(ar)));
	}
}

int	get_xx(t_printf *tp, char *hex)
{
	char	*str;

	str = ft_itoa_base(hex, va_arg(tp->ap, void *));
	if (!str)
		return (0);
	if (ft_strlen(str) > 8)
		ft_memmove(str, &str[ft_strlen(str) - 8], 9);
	if (ft_strchr(tp->flag, '#'))
		str = get_0x(str, "0");
	ft_lstadd_back(&tp->out, ft_lstnew(str));
	return (1);
}

void	get_idxx(t_printf *tp)
{
	int	ar;

	if (tp->type == 'i' || tp->type == 'd')
	{
		ar = va_arg(tp->ap, int);
		ft_lstadd_back(&tp->out, ft_lstnew(ft_itoa(ar)));
	}
	if (tp->type == 'x')
		get_xx(tp, tp->hex);
	if (tp->type == 'X')
		get_xx(tp, tp->hex_cap);
	if (tp->type == '%')
		ft_lstadd_back(&tp->out, ft_lstnew(ft_strdup("%")));
}

int	get_type(const char *s, t_printf *tp)
{
	char	*str;
	t_list	*last;

	get_type_prop(s, tp);
	if (tp->type == 'c')
	{
		str = ft_strdup(" ");
		str[0] = (char) va_arg(tp->ap, int);
		ft_lstadd_back(&tp->out, ft_lstnew(str));
	}
	get_cspu(tp);
	get_idxx(tp);
	set_size(tp);
	if (ft_strchr(tp->types, tp->type) && tp->limit > 0)
	{
		last = ft_lstlast(tp->out);
		if (tp->limit > ft_strlen(last->content))
		{
			get_fill_prefix(tp, last);
			set_fill_prefix(tp, last);
		}
	}
	tp->start = tp->i + 1;
	return (1);
}
