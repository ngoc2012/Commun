/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 08:41:16 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/05 18:34:40 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *s, int len)
{
	char	*o;

	o = malloc(len + 1);
	if (!o)
		return (0);
	ft_memcpy(o, s, len);
	o[len] = 0;
	return (o);
}

int	split_ops(char *s, t_list **ops)
{
	int		i;
	int		i0;
	int		n_o;
	int		n_c;
	char	d;

	while (*s && ft_strchr(" \n", *s))
		s++;
	n_o = 0;
	n_c = 0;
	i0 = 0;
	i = 0;
	while (s[i])
	{
		if (ft_strchr("()", s[i]))
		{
			if (s[i] == '(')
				n_o++;
			else
				n_c++;
			if (i > i0)
				ft_lstadd_back(ops, ft_lstnew(ft_strndup(&s[i0], i - i0)));
			ft_lstadd_back(ops, ft_lstnew(ft_strndup(&s[i], 1)));
			while (s[++i] && ft_strchr(" \n", s[i]))
				;
			i0 = i;
		}
		else if (!ft_strncmp("&&", &s[i], 2) || !ft_strncmp("||", &s[i], 2))
		{
			if (i > i0)
				ft_lstadd_back(ops, ft_lstnew(ft_strndup(&s[i0], i - i0)));
			ft_lstadd_back(ops, ft_lstnew(ft_strndup(&s[i], 1)));
			i++;
			while (s[++i] && ft_strchr(" \n", s[i]))
				;
			i0 = i;
		}
		else if (ft_strchr("\n;", s[i]))
		{
			if (i > i0)
				ft_lstadd_back(ops, ft_lstnew(ft_strndup(&s[i0], i - i0)));
			while (s[++i] && ft_strchr(" \n", s[i]))
				;
			if (s[i] == ';')
				return (0);
			i0 = i;
		}
		else if (ft_strchr("\"'", s[i]))
		{
			d = s[i];
			while (s[++i] && s[i] != d)
				;
			if (!s[i])
				return (0);
			i++;
		}
		else
			i++;
	}
	if (i > i0)
		ft_lstadd_back(ops, ft_lstnew(ft_strndup(&s[i0], i - i0)));
	printf("%d %d", n_o, n_c);
	if (n_o != n_c)
		return (0);
	return (1);
}
