/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 17:35:43 by wetieven          #+#    #+#             */
/*   Updated: 2022/02/10 15:04:09 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lst.h"

t_error	free_lst(t_lst *lst, t_error (*free_ctnt)(void *))
{
	t_node	*temp;
	t_node	*ptr;
	t_error	error;

	ptr = *lst;
	temp = ptr;
	while (temp)
	{
		ptr = temp;
		temp = ptr->next;
		error = free_node(ptr, free_ctnt);
		if (error)
			return (error);
	}
	*lst = NULL;
	return (CLEAR);
}
