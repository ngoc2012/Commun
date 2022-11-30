/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:23:54 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/27 13:32:31 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "ft_printf.h"

int	ft_print_out(t_printf *tp)
{
	int			n;
	t_list		*out;
	t_content	*cont;

	n = 0;
	out = tp->out;
	while (out)
	{
		cont = (t_content *) out->content;
		if (cont->type == 'c')
		{
			ft_putchar_fd(*(cont->str), 1);
			n++;
		}
		else
		{
			ft_putstr_fd(cont->str, 1);
			n += ft_strlen(cont->str);
		}
		out = out->next;
	}
	return (n);
}
