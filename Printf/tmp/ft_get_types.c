/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:23:54 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/29 09:03:53 by minh-ngu         ###   ########.fr       */
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

t_content	*get_xx(t_printf *tp, char *hex)
{
	//void	*a;
	long int	i;
	char	*str;

	//if (!(a = va_arg(tp->ap, void *)))
	//	return (0);
	str = 0;
	if ((i = va_arg(tp->ap, long int)))
	{
		if (i == LONG_MIN)
		{
			str = ft_strdup("0");
			if (!str)
				return (0);
			return (ft_new_content(tp->type, str));
		}
		str = ft_itoa_base(hex, &i);
	}
	if (!str)
		return (0);
	if (ft_strlen(str) > 8)
		ft_memmove(str, &str[ft_strlen(str) - 8], 9);
	if (ft_strchr(tp->flag, '#'))
		str = get_0x(str, "0");
	return (ft_new_content(tp->type, str));
}

void	get_idxx(t_printf *tp)
{
	int	ar;
	t_content	*new;

	new = 0;
	if (tp->type == 'i' || tp->type == 'd')
	{
		ar = va_arg(tp->ap, int);
		new = ft_new_content(tp->type, ft_itoa(ar));
	}
	if (tp->type == 'x')
		new = get_xx(tp, tp->hex);
	if (tp->type == 'X')
		new = get_xx(tp, tp->hex_cap);
	if (tp->type == '%')
		new = ft_new_content(tp->type, ft_strdup("%"));
	if (new)
		ft_lstadd_back(&tp->out, ft_lstnew(new));
}

int	get_type(const char *s, t_printf *tp)
{
	char	*str;
	t_list	*last;
	t_content	*cont;

	get_type_prop(s, tp);
	if (!get_cs(tp))
		return (0);
	if (!get_pu(tp))
		return (0);
	get_idxx(tp);
	if (!set_size(tp))
		return (0);
	if (ft_strchr(tp->types, tp->type) && tp->limit > 0)
	{
		last = ft_lstlast(tp->out);
		cont = (t_content *) last->content;
		if (tp->limit > ft_strlen(cont->str))
		{
			get_fill_prefix(tp, cont->str);
			str = set_fill_prefix(tp, cont->str);
			free(cont->str);
			cont->str = str;
		}
	}
	tp->start = tp->i + 1;
	return (1);
}
