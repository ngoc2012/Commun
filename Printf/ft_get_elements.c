/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:23:54 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/27 13:45:05 by minh-ngu         ###   ########.fr       */
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
	int		nbr;
	char	*str;

	nbr = 0;
	tp->start = tp->i;
	while (s[tp->i] && ft_strchr(tp->base10, s[tp->i]))
		tp->i++;
	if (tp->i > tp->start)
	{
		str = ft_substr(s, tp->start, tp->i - tp->start);
		nbr = ft_atoi(str);
		free(str);
	}
	return (nbr);
}

void	get_str(const char *s, t_printf *tp)
{
	t_content	*new;

	if (tp->i > tp->start)
	{
		new = ft_new_content('s', ft_substr(s, tp->start, tp->i - tp->start));
		if (tp->out)
			ft_lstadd_back(&tp->out, ft_lstnew(new));
		else
			tp->out = ft_lstnew(new);
	}
}

char	*get_0x(char *str, const char *res)
{
	char	*s2;

	if (!str)
		return (0);
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
	char	*str0;
	t_list	*last;

	if (ft_strchr(tp->types, tp->type) && tp->type != 'c')
	{
		last = ft_lstlast(tp->out);
		str0 = ((t_content *) last->content)->str;
		if (tp->size < ft_strlen(str0))
		{
			str = ft_calloc(tp->size + 1, sizeof(char));
			if (!str)
				return (0);
			ft_strlcpy(str, str0, tp->size + 1);
			free(str0);
			str0 = str;
		}
	}
	return (1);
}

void	get_fill_prefix(t_printf *tp, char *lcs)
{
	tp->start = tp->limit - ft_strlen(lcs);
	if (tp->start < 0)
		tp->start = 0;
	tp->fill = ' ';
	tp->prefix = 0;
	if (ft_strchr(tp->flag, ' '))
		tp->prefix = ' ';
	if (ft_strchr(tp->flag, '+') && ft_strchr(tp->numbers, tp->type)
		&& (ft_memcmp(lcs, "-", 1)))
		tp->prefix = '+';
	if (ft_strchr(tp->flag, '0'))
		tp->fill = '0';
	if (ft_strchr(tp->flag, '-'))
	{
		tp->start = 0;
		tp->fill = ' ';
	}
}
