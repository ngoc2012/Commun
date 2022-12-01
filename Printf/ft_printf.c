/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:23:54 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/01 16:02:35 by minh-ngu         ###   ########.fr       */
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
			//printf("\ni1 = %d\n", i);
			get_elmt('_', tp, start, i);
			i++;
			start = i;
			//printf("i2 = %d\n", i);
			while (ft_strchr(tp->numflags, s[i]) && s[i]
				&& !ft_strchr(tp->types, s[i]))
				i++;
			//printf("i3 = %d\n", i);
			if (ft_strchr(tp->types, s[i]))
				get_elmt(s[i], tp, start, i);
			//printf("i4 = %d\n", i);
			start = i + 1;
		}
		if (s[i])
			i++;
	}
	get_elmt('_', tp, start, i);
}

static void	get_csui(t_prtf *tp, t_elmt *elt, va_list ap)
{
	char	c;

	if (elt->type == 'c')
	{
		c = (char) va_arg(ap, int);
		elt->str = ft_calloc(2, sizeof(char));
		if (!elt->str)
			tp->error = 1;
		else
			elt->str[0] = c;
	}
	if (elt->type == 's')
		elt->str = va_arg(ap, char *);
	if (elt->type == 'u')
		elt->str = ft_usitoa(va_arg(ap, unsigned int));
	if (elt->type == 'i' || elt->type == 'd')
		elt->str = ft_itoa(va_arg(ap, int));
}

static void	get_values(t_prtf *tp, va_list ap)
{
	t_list				*lst;
	t_elmt				*e;
	long unsigned int	i;

	lst = tp->elmts;
	while (lst)
	{
		e = (t_elmt *) lst->content;
		get_csui(tp, e, ap);
		if (ft_strchr("pxX", e->type))
		{
			i = va_arg(ap, long unsigned int);
			e->str = ft_itoa_base("0123456789abcdef", i);
			if (ft_strchr("xX", e->type) && ft_strncmp(e->str, "8000000000000000", 17) == 0)
			{
				free(e->str);
				e->str = ft_strdup("0");
			}
		}
		lst = lst->next;
	}
}

//va_start(ap, s);
size_t	ft_printf(const char *s, ...)
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
	n = tp->print_elmts(tp);
	tp->free_prtf(tp);
	va_end(ap);
	return (n);
}
