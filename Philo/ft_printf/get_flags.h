/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:23:04 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/12 11:28:01 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_FLAGS_H
# define GET_FLAGS_H

# include "prtf.h"

static int	get_number(char *s, int *len)
{
	int		nbr;
	char	*str;

	nbr = 0;
	*len = 0;
	while (s[*len] && ft_strchr("0123456789", s[*len]))
		(*len)++;
	if (*len > 0)
	{
		str = ft_substr(s, 0, *len);
		nbr = ft_atoi(str);
		free(str);
	}
	return (nbr);
}

static void	get_lengths(t_elmt *e)
{
	int		len;
	char	*s;

	if (!ft_strchr(e->tp->nums, e->type))
		return ;
	s = e->flag;
	while (*s)
	{
		if (*s == '.')
		{
			s++;
			e->precision = get_number(s, &len);
			ft_memset(s, '_', len);
			s += len - 1;
		}
		if (ft_strchr("123456789", *s))
		{
			e->size = get_number(s, &len);
			ft_memset(s, '_', len);
			s += len - 1;
		}
		s++;
	}
}

static void	get_sign(t_elmt *e)
{
	if (ft_strchr("di", e->type) && e->str)
	{
		if (e->str[0] == '-')
		{
			e->sign = -1;
			ft_memmove(e->lst->content, e->lst->content + 1,
				ft_strlen((char *) e->lst->content));
		}
		else
			e->sign = 1;
	}
}

static void	get_flags(t_elmt *e)
{
	e->flag = ft_substr(e->tp->str, e->start, e->end - e->start);
	if (!e->flag)
		return ;
	get_lengths(e);
	get_sign(e);
	if (ft_strchr(e->flag, ' '))
		e->space_flag = 1;
	if (ft_strchr(e->flag, '+'))
	{
		e->plus_flag = 1;
		e->space_flag = 0;
	}
	if (ft_strchr(e->flag, '0'))
		e->zero_flag = 1;
	if (ft_strchr(e->flag, '.'))
	{
		e->dot_flag = 1;
		e->zero_flag = 0;
	}
	if (ft_strchr(e->flag, '-'))
	{
		e->minus_flag = 1;
		e->zero_flag = 0;
	}
}

#endif
