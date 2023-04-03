/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:30:53 by wetieven          #+#    #+#             */
/*   Updated: 2022/02/11 18:29:01 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "dll.h"

t_error	dll_iter(t_dll lst_head, t_error (*fct)(void *))
{
	t_error	error;

	if (!lst_head)
		return (NULL_PTR);
	while (lst_head)
	{
		error = (*fct)(lst_head->ctnt);
		if (error)
			return (error);
		lst_head = lst_head->next;
	}
	return (CLEAR);
}
