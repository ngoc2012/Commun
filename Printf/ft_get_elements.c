/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:23:54 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/25 14:06:03 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include "Libft/libft.h"
#include "ft_printf.h"

int	get_number(const char *s, t_printf *tp)
{
	int		out;
	char	*str;

	out = 0;
	tp->start = tp->i;
	while (s[tp->i] && ft_strchr(tp->base10, s[tp->i]))
		tp->i++;
	if (tp->i > tp->start)
	{
		str = ft_substr(s, tp->start, tp->i - tp->start);
		out = ft_atoi(str);
		free(str);
	}
	return (out);
}

void	get_str(const char *s, t_printf *tp)
{
	if (tp->i > tp->start)
	{
		if (tp->out)
			ft_lstadd_back(&tp->out,
				ft_lstnew(ft_substr(s, tp->start, tp->i - tp->start)));
		else
			tp->out = ft_lstnew(ft_substr(s, tp->start, tp->i - tp->start));
	}
}

char	*get_0x(char *str, const char *res)
{
	char	*s2;

	if (ft_strncmp(str, "0", 2) != 0)
	{
		s2 = malloc(sizeof(char) * (ft_strlen(str) + 3));
		if (!s2)
			return (0);
		ft_strlcpy(s2, "0x", 3);
		ft_strlcat(s2, str, ft_strlen(str) + 3);
		free(str);
		return (s2);
	}
	else
	{
		free(str);
		return (ft_strdup(res));
	}
}

int	set_size(t_printf *tp)
{
	char	*str;
	t_list	*last;

	if (ft_strchr(tp->types, tp->type))
	{
		last = ft_lstlast(tp->out);
		if (tp->size < ft_strlen(last->content))
		{
			str = ft_calloc(tp->size + 1, sizeof(char));
			if (!str)
				return (0);
			ft_strlcpy(str, last->content, tp->size + 1);
			free(last->content);
			last->content = str;
		}
	}
	return (1);
}

void	get_fill_prefix(t_printf *tp, t_list *last)
{
	tp->start = tp->limit - ft_strlen(last->content);
	if (tp->start < 0)
		tp->start = 0;
	tp->fill = ' ';
	tp->prefix = 0;
	if (ft_strchr(tp->flag, ' '))
		tp->prefix = ' ';
	if (ft_strchr(tp->flag, '+') && ft_strchr(tp->numbers, tp->type)
		&& (ft_memcmp(last->content, "-", 1)))
		tp->prefix = '+';
	if (ft_strchr(tp->flag, '0'))
		tp->fill = '0';
	if (ft_strchr(tp->flag, '-'))
	{
		tp->start = 0;
		tp->fill = ' ';
	}
}
