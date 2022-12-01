/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elmt_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:23:04 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/01 22:49:59 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_get_flags.h"
#include "ft_set_flags.h"

static void	free_elmt(void	*c0)
{
	t_elmt	*e;

	e = (t_elmt *) c0;
	ft_lstclear(&e->lst, free);
	if (e->str && e->type != 's' && e->type != '%')
		free(e->str);
	if (e->flag)
		free(e->flag);
	free(e);
}

static size_t	print_lst(t_elmt *e)
{
	size_t	n;
	t_list	*lst;

	n = 0;
	lst = e->lst;
	while (lst)
	{
		ft_putstr_fd(lst->content, 1);
		n += ft_strlen(lst->content);
		lst = lst->next;
	}
	return (n);
}

static size_t	print_elmt(t_elmt *e)
{	
	if (e->type == '_')
	{
		write(1, &(e->tp->str[e->start]), e->end - e->start);
		return (e->end - e->start);
	}
	if (e->type == 'c' && e->str[0] == 0)
	{
		write(1, e->str, 1);
		if (e->size > 1)
			return (e->size);
		else
			return (1);
	}
	if (e->type == 'p' && ft_strncmp(e->str, "0", 2) == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	if (e->type == 's' && e->dot_flag && e->precision < ft_strlen(e->str))
	{
		write(1, e->str, e->precision);
		return (e->precision);
	}
	if (e->type == 's' && e->str == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	if (e->type == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	if (ft_strchr(e->tp->nums, e->type))
		return (print_lst(e));
	ft_putstr_fd(e->str, 1);
	if (e->str)
		return (ft_strlen(e->str));
	return (0);
}

t_elmt	*ft_new_elmt(char type, t_prtf *tp, size_t start, size_t end)
{
	t_elmt	*e;

	e = malloc(sizeof(t_elmt));
	if (!e)
		return (0);
	e->type = type;
	e->tp = tp;
	e->start = start;
	e->end = end;
	e->size = 0;
	e->precision = 0;
	e->sign = 0;
	e->zero_flag = 0;
	e->space_flag = 0;
	e->minus_flag = 0;
	e->plus_flag = 0;
	e->dot_flag = 0;
	e->flag = 0;
	e->str = 0;
	e->lst = 0;
	e->print_elmt = &print_elmt;
	e->free_elmt = &free_elmt;
	e->get_flags = &get_flags;
	e->set_flags = &set_flags;
	return (e);
}
