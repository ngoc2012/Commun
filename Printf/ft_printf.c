/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:23:54 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/30 17:37:53 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_elmt(char type, t_prtf *tp, size_t start, size_t end)
{
	t_elmt	*new;
	t_list	*lst;

	if (end > start || type != '_')
	{
		new = ft_new_elmt(type, tp, start, end);
		if (!new)
			tp->error = 1;
		lst = ft_lstnew(new);
		if (!lst)
			tp->error = 1;
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
			while (ft_strchr(tp->numflags, s[i]) && s[i] && !ft_strchr(tp->types, s[i]))
				i++;
			if (ft_strchr(tp->types, s[i]))
				get_elmt(s[i], tp, start, i);
			i++;
			start = i;
		}
		if (s[i])
			i++;
	}
	get_elmt('_', tp, start, i);
}

static char	*get_cc(t_prtf *tp, char c)
{
	char	*s;

	s = ft_calloc(2, sizeof(char));
	if (!s)
		tp->error = 1;
	if (!s)
		return (0);
	s[0] = c;
	return (s);
}

static void	get_values(t_prtf *tp, va_list ap)
{
	t_list	*lst;
	t_elmt	*elt;
	long unsigned int	i;

	lst = tp->elmts;
	while (lst)
	{
		elt = (t_elmt *) lst->content;
		if (elt->type == 'c')
			elt->str = get_cc(tp, (char) va_arg(ap, int));
		if (elt->type == 's')
			elt->str = va_arg(ap, char *);
		if (ft_strchr("pxX", elt->type))
			i = (long unsigned int) va_arg(ap, void *);
		if (ft_strchr("pxX", elt->type))
			elt->str = ft_itoa_base("0123456789abcdef", &i);
		if (elt->type == 'u')
			elt->str =  ft_usitoa(va_arg(ap, unsigned int));
		if (elt->type == 'i' || elt->type == 'd')
			elt->str = ft_itoa(va_arg(ap, int));
		lst = lst->next;
	}
}

//va_start(ap, s);
size_t	ft_printf(const char *s, ...)
{
	va_list	ap;
	size_t		n;
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
	n = tp->print_elmts(tp);
	tp->free_prtf(tp);
	va_end(ap);
	return (n);
}
