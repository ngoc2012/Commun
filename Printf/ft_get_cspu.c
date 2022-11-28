/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cspu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:23:54 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/27 14:10:54 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "Libft/libft.h"
#include "ft_printf.h"

int	get_cs(t_printf *tp)
{
	char		*str;
	t_content	*new;

	new = 0;
	if (tp->type == 'c')
	{
		str = malloc(sizeof(char));
		if (!str)
			return (0);
		*str = (char) va_arg(tp->ap, int);
		new = ft_new_content('c', str);
	}
	if (tp->type == 's')
	{
		str = va_arg(tp->ap, char *);
		if (str)
			new = ft_new_content('s', ft_strdup((const char *) str));
		else
			new = ft_new_content('s', ft_strdup("(null)"));
	}
	if (new)
		ft_lstadd_back(&tp->out, ft_lstnew(new));
	return (1);
}

int	get_pu(t_printf *tp)
{
	int			ar;
	t_content	*new;

	new = 0;
	if (tp->type == 'p')
		new = ft_new_content('p',
				get_0x(ft_itoa_base(tp->hex, va_arg(tp->ap, void *)), "(nil)"));
	if (tp->type == 'u')
	{
		ar = va_arg(tp->ap, int);
		if (ar >= 0)
			new = ft_new_content('u', ft_itoa(ar));
		else
			new = ft_new_content('u', ft_usitoa(ar));
	}
	if (new)
		ft_lstadd_back(&tp->out, ft_lstnew(new));
	return (1);
}
