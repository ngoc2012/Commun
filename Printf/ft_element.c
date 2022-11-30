/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_element.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:23:04 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/29 20:03:05 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static void	free_elmt(void	*c0)
{
	t_elmt	*c;

	c = (t_elmt *) c0;
	free(c->flag);
	free(c->str);
	free(c);
}

static void	print(t_elmt	*e)
{	
	ft_putstr_fd("type :", 1);
	ft_putchar_fd(e->type, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("prefix :", 1);
	ft_putchar_fd(e->prefix, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("fill :", 1);
	ft_putchar_fd(e->fill, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("size :", 1);
	ft_putnbr_fd(e->size, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("limit :", 1);
	ft_putnbr_fd(e->limit, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("str :", 1);
	ft_putstr_fd(e->str, 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("flag :", 1);
	ft_putstr_fd(e->flag, 1);
	ft_putchar_fd('\n', 1);
}

t_elmt	*ft_new_elmt(char type, char *str)
{
	t_elmt	*new_elmt;

	if (!str && type != 'c')
		return (0);
	new_elmt = malloc(sizeof(t_elmt));
	if (!new_elmt)
		return (0);
	new_elmt->type = 0;
	new_elmt->prefix = 0;
	new_elmt->size = INT_MAX;
	new_elmt->limit = 0;
	new_elmt->type = type;
	new_elmt->str = str;
	new_elmt->print_elmt = &print;
	new_elmt->free_elmt = &free_elmt;
	new_elmt->flag = ft_calloc(7, sizeof(char));
	if (!new_elmt->flag)
		return (0);
	return (new_elmt);
}
