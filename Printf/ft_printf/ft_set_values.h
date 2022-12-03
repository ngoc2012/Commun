/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_values.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:23:04 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/03 13:34:01 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SET_VALUES_H
# define FT_SET_VALUES_H

# include "ft_printf.h"

static void	set_spx(t_elmt *e)
{
	if (!e->str)
	{
		if (e->type == 's')
			ft_lstadd_back(&e->lst, ft_lstnew(ft_strdup("(null)")));
		else
			ft_lstadd_back(&e->lst, ft_lstnew(e->str));
	}
	else
	{
		if (e->type == 'p' && ft_strncmp(e->str, "0", 2) == 0)
			ft_lstadd_back(&e->lst, ft_lstnew(ft_strdup("(nil)")));
		else if (ft_strchr("xX", e->type) && ft_strlen(e->str) > 8)
			ft_lstadd_back(&e->lst,
				ft_lstnew(ft_strdup(&e->str[ft_strlen(e->str) - 8])));
		else
			ft_lstadd_back(&e->lst, ft_lstnew(ft_strdup(e->str)));
	}
}

static void	set_values(t_prtf *tp)
{
	int		i;
	t_list	*elmts;
	t_elmt	*e;

	elmts = tp->elmts;
	while (elmts)
	{
		e = (t_elmt *) elmts->content;
		i = -1;
		if (e->type == 'X' && e->str)
			while (e->str[++i])
				e->str[i] = ft_toupper(e->str[i]);
		set_spx(e);
		elmts = elmts->next;
	}
}

#endif
