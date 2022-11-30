/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prtf_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 07:11:02 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/30 17:05:24 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	print_elmts(t_prtf	*tp)
{
	size_t	n;
	t_list	*lst;
	t_elmt	*elt;

	n = 0;
	lst = tp->elmts;
	while (lst)
	{
		elt = (t_elmt *) lst->content;
		elt->get_prop(elt);
		elt->set_prop(elt);
		n += elt->print_elmt(elt);
		lst = lst->next;
	}
	return (n);
}

static void	free_prtf(t_prtf	*tp)
{
	ft_lstclear(&(tp->elmts), ((t_elmt *) tp->elmts->content)->free_elmt);
	free(tp);
}

t_prtf	*ft_new_prtf(const char *str)
{
	t_prtf	*new;

	new = malloc(sizeof(t_prtf));
	if (!new)
		return (0);
	new->types = "cspdiuxX%";
	new->nums = "pdiuxX";
	new->flags = "-0.# +";
	new->numflags = "123456789-0.# +";
	new->elmts = 0;
	new->error = 0;
	new->str = str;
	new->free_prtf = &free_prtf;
	new->print_elmts = &print_elmts;
	return (new);
}
