/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:23:54 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/10 22:36:09 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_VALUES_H
# define FT_GET_VALUES_H

# include "prtf.h"

static void	get_csui(t_elmt *e, va_list ap)
{
	char	c;

	if (e->type == 'c')
	{
		c = (char) va_arg(ap, int);
		e->str = ft_calloc(2, sizeof(char));
		//free(e->str);e->str=0;
		if (e->str)
			e->str[0] = c;
	}
	if (e->type == 's')
		e->str = va_arg(ap, char *);
	if (e->type == 'u')
		e->str = ft_usitoa(va_arg(ap, unsigned int));
		//free(e->str);e->str=0;
	if (e->type == 'i' || e->type == 'd')
		e->str = ft_itoa(va_arg(ap, int));
		//free(e->str);e->str=0;
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
		get_csui(e, ap);
		if (ft_strchr("pxX", e->type))
		{
			i = va_arg(ap, long unsigned int);
			e->str = ft_itoa_base("0123456789abcdef", i);
			//free(e->str);e->str=0;
			if (ft_strchr("xX", e->type)
				&& ft_strncmp(e->str, "8000000000000000", 17) == 0)
			{
				free(e->str);
				e->str = ft_strdup("0");
				//free(e->str);e->str=0;
			}
		}
		lst = lst->next;
	}
}

#endif
