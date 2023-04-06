/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prtf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 07:11:02 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/12 11:21:38 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prtf.h"

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
		elt->get_flags(elt);
		elt->set_flags(elt);
		n += elt->print_elmt(elt);
		lst = lst->next;
	}
	return (n);
}

static void	free_prtf(t_prtf	*tp)
{
	if (tp->elmts)
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
	new->nums = "cspdiuxX";
	new->flags = "-0.# +";
	new->numflags = "123456789-0.# +";
	new->elmts = 0;
	new->error = 0;
	new->str = str;
	new->free_prtf = &free_prtf;
	new->print_elmts = &print_elmts;
	return (new);
}
