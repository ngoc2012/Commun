/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 16:40:37 by wetieven          #+#    #+#             */
/*   Updated: 2022/02/10 15:22:41 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lst.h"

t_error	free_node(t_node *to_free, t_error (*free_ctnt)(void *))
{
	t_error	error;

	error = CLEAR;
	if (free_ctnt)
		error = (*free_ctnt)(to_free->ctnt);
	if (error)
		return (error);
	free(to_free);
	return (CLEAR);
}
