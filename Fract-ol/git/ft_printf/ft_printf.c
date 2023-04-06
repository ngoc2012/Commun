/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:23:54 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/15 17:15:43 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "prtf.h"
#include "get_values.h"
#include "set_values.h"

static void	get_elmt(char type, t_prtf *tp, size_t start, size_t end)
{
	t_elmt	*new;
	t_list	*lst;

	if (end > start || type != '_')
	{
		new = ft_new_elmt(type, tp, start, end);
		if (!new)
			return ;
		lst = ft_lstnew(new);
		if (!lst)
			return ;
		if (tp->elmts)
			ft_lstadd_back(&tp->elmts, lst);
		else
			tp->elmts = lst;
	}
}

static void	get_elmts(t_prtf *tp, const char *s)
{
	size_t	i;
	size_t	start;

	start = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			get_elmt('_', tp, start, i);
			i++;
			start = i;
			while (ft_strchr(tp->numflags, s[i]) && s[i]
				&& !ft_strchr(tp->types, s[i]))
				i++;
			if (ft_strchr(tp->types, s[i]))
				get_elmt(s[i], tp, start, i);
			start = i + 1;
		}
		if (s[i])
			i++;
	}
	get_elmt('_', tp, start, i);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	size_t	n;
	t_prtf	*tp;

	va_start(ap, s);
	tp = ft_new_prtf(s);
	if (!tp)
		return (0);
	n = 0;
	get_elmts(tp, s);
	if (tp->error)
		return (0);
	get_values(tp, ap);
	set_values(tp);
	n = tp->print_elmts(tp);
	tp->free_prtf(tp);
	va_end(ap);
	return ((int) n);
}
