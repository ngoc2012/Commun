/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elmt_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:23:04 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/30 18:40:47 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	free_elmt(void	*c0)
{
	t_elmt	*e;

	e = (t_elmt *) c0;
	ft_lstclear(&e->lst, free);
	if (e->str && e->type != 's' && e->type != '%')
		free(e->str);
	if (e->flag)
		free(e->flag);
	free(e);
}

static size_t	print_lst(t_elmt *e, int show)
{
	size_t	n;
	t_list	*lst;

	n = 0;
	lst = e->lst;
	while (lst)
	{
		if (show)
			ft_putstr_fd(lst->content, 1);
		n += ft_strlen(lst->content);
		lst = lst->next;
	}
	return (n);
}

static size_t	print_elmt(t_elmt *e)
{	
	int	len;

	len = 0;
	if (e->type == '_')
	{
		write(1, &(e->tp->str[e->start]), e->end - e->start);
		return (e->end - e->start);
	}
	else if (e->type == 'c')
	{
		write(1, e->str, 1);	
		return (1);
	}
	else if (e->type == '%')
	{
		write(1, "%", 1);	
		return (1);
	}
	else
	{
		if (ft_strchr(e->tp->nums, e->type))
			return (print_lst(e, 1));
		ft_putstr_fd(e->str, 1);
		if (e->str)
			return (len + ft_strlen(e->str));
	}
	return (0);
}

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

static void	get_prop(t_elmt	*e)
{
	int		len;
	char	*s;

	if (!ft_strchr(e->tp->nums, e->type))
		return ;
	e->flag = ft_substr(e->tp->str, e->start, e->end - e->start);
	//printf("\n1 e->flag #%s#\n", e->flag);
	s = e->flag;
	while (*s)
	{
		if (*s == '.')
		{
			s++;
			e->size = get_number(s, &len);
			ft_memset(s, '_', len); 
			s += len;
		}
		if (ft_strchr("123456789", *s))
		{
			e->limit = get_number(s, &len);
			ft_memset(s, '_', len); 
			s += len;
		}
		if (*s)
			s++;
	}
	//printf("\n2 e->flag #%s#\n", e->flag);
}

static void	set_prop(t_elmt	*e)
{
	char	prefix;
	char	fill;
	char	*fills;
	int	i;

	i = -1;
	if (e->type == 'X')
		while (e->str[++i])
			e->str[i] = ft_toupper(e->str[i]);
	if (ft_strchr(e->tp->nums, e->type))
	{
		if (ft_strchr("xX", e->type) && ft_strlen(e->str) > 8)
			ft_lstadd_back(&e->lst, ft_lstnew(ft_strdup(&e->str[ft_strlen(e->str) - 8])));
		else
			ft_lstadd_back(&e->lst, ft_lstnew(ft_strdup(e->str)));
	}
	if (e->type == 'p' || (ft_strchr("xX", e->type) && ft_strchr(e->flag, '#')))
		if (ft_strncmp(e->str, "0", 2) != 0)
			ft_lstadd_front(&e->lst, ft_lstnew(ft_strdup("0x")));
	prefix = 0;
	fill = ' ';
	if (e->flag)
	{
		if (ft_strchr(e->flag, ' '))
			prefix = ' ';
		if (ft_strchr(e->flag, '+'))
			prefix = '+';
		if (ft_strchr(e->flag, '0'))
			fill = '0';
	}
	if (print_lst(e, 0) < e->limit)
}

t_elmt	*ft_new_elmt(char type, t_prtf *tp, size_t start, size_t end)
{
	t_elmt	*new_elmt;

	new_elmt = malloc(sizeof(t_elmt));
	if (!new_elmt)
		return (0);
	new_elmt->type = type;
	new_elmt->tp = tp;
	new_elmt->start = start;
	new_elmt->end = end;
	new_elmt->size = -1;
	new_elmt->limit = 0;
	new_elmt->flag = 0;
	new_elmt->str = 0;
	new_elmt->lst = 0;
	new_elmt->print_elmt = &print_elmt;
	new_elmt->free_elmt = &free_elmt;
	new_elmt->get_prop = &get_prop;
	new_elmt->set_prop = &set_prop;
	new_elmt->print_lst = &print_lst;
	return (new_elmt);
}
