/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:23:54 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/30 06:23:51 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include "Libft/libft.h"
#include "ft_printf.h"

static int	init(t_printf	*tp)
{
	tp->hex = "0123456789abcdef";
	tp->hex_cap = "0123456789ABCDEF";
	tp->base10 = "0123456789";
	tp->all_types = "cspdiuxX%";
	tp->numbers = "pdiuxX";
	tp->all_flags = "-0.# +";
	tp->i = 0;
	tp->start = 0;
	tp->elmnts = 0;
	return (1);
}

void	get_str(const char *s, t_printf *tp, char type, int is_flag)
{
	t_elmt	*new;

	if (tp->i > tp->start)
	{
		if (is_flag)
		new = ft_new_elmt(type, ft_substr(s, tp->start, tp->i - tp->start));
		if (tp->elmnts)
			ft_lstadd_back(&tp->elmnts, ft_lstnew(new));
		else
			tp->elmnts = ft_lstnew(new);
	}
}

int	get_elmnts(const char *s, t_printf *tp)
{
	while (s[tp->i])
	{
		if (s[tp->i] == '%')
		{
			get_str(s, tp, '_', 0);
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
			tp->start = tp->i + 1;
		}
		if (s[tp->i])
			tp->i++;
	}
	get_str(s, tp, '_');
	return (1);
}

int	ft_printf(const char *s, ...)
{
	int			n;
	t_printf	*tp;

	tp = malloc(sizeof(t_printf));
	if (!tp)
		return (0);
	//va_start(tp->ap, s);
	n = 0;
	init(tp);
	get_elmnts(s, tp);
	//	if (get_elmnts(s, tp))
	//		n = ft_print_elmnts(tp);
	free(tp);
	return (n);
}
