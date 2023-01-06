/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:28:12 by wetieven          #+#    #+#             */
/*   Updated: 2022/02/10 15:12:41 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

// Deletes the head of a list, allowing us to use lists as stacks
t_error	lst_del_head(t_lst *lst, t_error (*free_ctnt)(void *))
{
	t_node	*new_head;
	t_error	error;

	if (!*lst)
		return (NULL_PTR);
	new_head = (*lst)->next;
	error = free_node(*lst, free_ctnt);
	if (error)
		return (error);
	*lst = new_head;
	return (CLEAR);
}

// Pops the queue of a list, allowing us to use lists as queues
t_node	*lst_pop_tail(t_lst lst)
{
	t_node	*popped_tail;

	if (!lst)
		return (NULL);
	popped_tail = last_node(lst);
	while (lst->next != popped_tail)
		lst = lst->next;
	lst->next = NULL;
	return (popped_tail);
}
