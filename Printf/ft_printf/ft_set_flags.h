/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_flags.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:23:04 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/03 13:45:10 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SET_FLAGS_H
# define FT_SET_FLAGS_H

# include "ft_printf.h"

static size_t	size_lst(t_elmt *e)
{
	size_t	n;
	t_list	*lst;

	n = 0;
	lst = e->lst;
	while (lst)
	{
		n += ft_strlen(lst->content);
		lst = lst->next;
	}
	return (n);
}

static void	set_zero_sign(t_elmt *e)
{
	char	*fills;
	int		i;

	if (!ft_strchr("cs", e->type) && e->zero_flag)
	{
		i = e->size - size_lst(e);
		if (e->space_flag || e->plus_flag || (e->zero_flag && e->sign == -1))
			i--;
		if (i > 0)
		{
			fills = ft_calloc(sizeof(char), i + 1);
			ft_memset(fills, '0', i);
			ft_lstadd_front(&e->lst, ft_lstnew(fills));
		}
	}
	if (e->space_flag && e->sign != -1 && e->type != 's')
		ft_lstadd_front(&e->lst, ft_lstnew(ft_strdup(" ")));
	if (e->plus_flag && e->sign == 1)
		ft_lstadd_front(&e->lst, ft_lstnew(ft_strdup("+")));
	if (e->sign == -1)
		ft_lstadd_front(&e->lst, ft_lstnew(ft_strdup("-")));
}

static void	set_precision(t_elmt *e)
{
	char	*s;
	char	*fills;
	int		i;

	if (!ft_strchr(e->tp->nums, e->type))
		return ;
	if (e->type == 's')
	{
		s = (char *) e->lst->content;
		if (e->dot_flag && e->precision < ft_strlen(s))
			s[e->precision] = 0;
		return ;
	}
	i = e->precision - size_lst(e);
	if (i > 0)
	{
		fills = ft_calloc(sizeof(char), i + 1);
		ft_memset(fills, '0', i);
		ft_lstadd_front(&e->lst, ft_lstnew(fills));
	}
}

static void	set_space(t_elmt *e)
{
	char	*fills;
	int		i;

	if (!ft_strchr(e->tp->nums, e->type))
		return ;
	i = e->size - size_lst(e);
	if (e->type == 'c' && e->str && e->str[0] == 0)
		i--;
	if (i > 0)
	{
		fills = ft_calloc(sizeof(char), i + 1);
		ft_memset(fills, ' ', i);
		if (e->minus_flag)
			ft_lstadd_back(&e->lst, ft_lstnew(fills));
		else
			ft_lstadd_front(&e->lst, ft_lstnew(fills));
	}
}

static void	set_flags(t_elmt *e)
{
	if (!ft_strchr(e->tp->nums, e->type))
		return ;
	if (e->str)
	{
		if (ft_strchr("diuxX", e->type) && e->dot_flag && e->precision == 0
			&& ft_strncmp(e->str, "0", 2) == 0)
			((char *) e->lst->content)[0] = 0;
		if ((e->type == 'p')
			|| (ft_strchr("xX", e->type) && ft_strchr(e->flag, '#')))
		{
			if (ft_strncmp(e->str, "0", 2) != 0)
			{
				if (e->type == 'X')
					ft_lstadd_front(&e->lst, ft_lstnew(ft_strdup("0X")));
				else
					ft_lstadd_front(&e->lst, ft_lstnew(ft_strdup("0x")));
			}
		}
		set_precision(e);
		set_zero_sign(e);
	}
	else
		if (e->type == 's' && e->dot_flag && e->precision < 6)
			((char *) e->lst->content)[0] = 0;
	set_space(e);
}

#endif
