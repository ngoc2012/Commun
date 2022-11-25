/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:23:54 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/25 14:28:39 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include "Libft/libft.h"
#include "ft_printf.h"

int	init(t_printf	*tp)
{
	tp->hex = "0123456789abcdef";
	tp->hex_cap = "0123456789ABCDEF";
	tp->base10 = "0123456789";
	tp->types = "cspdiuxX%";
	tp->numbers = "pdiuxX";
	tp->all_flags = "-0.# +";
	tp->type = 0;
	tp->prefix = 0;
	tp->size = INT_MAX;
	tp->i = 0;
	tp->start = 0;
	tp->limit = 0;
	tp->out = 0;
	tp->flag = ft_calloc(7, sizeof(char));
	if (!tp->flag)
		return (0);
	return (1);
}

int	set_fill_prefix(t_printf *tp, t_list *last)
{
	char	*str;

	str = ft_calloc(tp->limit + 1, sizeof(char));
	if (!str)
		return (0);
	ft_memset(str, tp->fill, tp->limit);
	if (tp->fill == '0' && tp->prefix && ft_strlen(last->content) < tp->limit)
		ft_memset(str, tp->prefix, 1);
	if (tp->fill == ' ' && tp->prefix && ft_strlen(last->content) < tp->limit)
	{
		if (tp->start == 0)
		{
			ft_memset(str, tp->prefix, 1);
			tp->start++;
		}
		else
			ft_memset(str + tp->start - 1, tp->prefix, 1);
	}
	ft_memcpy(str + tp->start, last->content, ft_strlen(last->content));
	free(last->content);
	last->content = str;
	return (1);
}

int	get_out(const char *s, t_printf *tp)
{
	while (s[tp->i])
	{
		if (s[tp->i] == '%')
			if (!get_type(s, tp))
				return (0);
		if (s[tp->i])
			tp->i++;
	}
	get_str(s, tp);
	return (1);
}

void	free_all(t_printf *tp)
{
	ft_lstclear(&tp->out, free);
	va_end(tp->ap);
	free(tp->flag);
	free(tp);
}

int	ft_printf(const char *s, ...)
{
	int			n;
	t_printf	*tp;
	t_list		*out;

	tp = malloc(sizeof(t_printf));
	if (!tp)
		return (0);
	va_start(tp->ap, s);
	n = 0;
	if (init(tp))
	{
		if (get_out(s, tp))
		{
			out = tp->out;
			while (out)
			{
				n += ft_strlen(out->content);
				if (ft_strlen(out->content) == 0)
					n++;
				ft_putstr_fd(out->content, 1);
				out = out->next;
			}
		}
	}
	free_all(tp);
	return (n);
}
