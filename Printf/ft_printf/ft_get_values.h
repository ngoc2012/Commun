/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_values.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:23:54 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/03 12:28:24 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_VALUES_H
# define FT_GET_VALUES_H

# include "ft_printf.h"

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
			if (ft_strchr("xX", e->type)
				&& ft_strncmp(e->str, "8000000000000000", 17) == 0)
			{
				free(e->str);
				e->str = ft_strdup("0");
			}
		}
		lst = lst->next;
	}
}

#endif
