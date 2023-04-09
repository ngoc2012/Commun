/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 18:19:56 by wetieven          #+#    #+#             */
/*   Updated: 2022/02/10 14:58:31 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

t_error	lst_iter(t_lst lst, t_error (*fct)(void *))
{
	t_error	error;

	if (!lst)
		return (NULL_PTR);
	while (lst)
	{
		error = (*fct)(lst->ctnt);
		if (error)
			return (error);
		lst = lst->next;
	}
	return (CLEAR);
}
