/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vctr_nav.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 13:59:28 by wetieven          #+#    #+#             */
/*   Updated: 2022/03/01 14:02:11 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vct.h"

// Granting clean access to any entry of our t_vctr struct,
// with overflow protection.
// A request for anything above the latest entry will point you to NULL.
// Meaning you can't access, safe yet empty preallocated vector spaces,
// but why would you ?
// Although you should be able to access to the first unallocated space
// for convenience, especially with yet empty vectors.
//
void	*vctr_entry(t_vctr *vctr, size_t index)
{
	if (index > vctr->entries)
		return (NULL);
	return (vctr->data + index * vctr->unit_size);
}

// I use vectors as stacks a LOT, so this is quite handy !
//
void	*vctr_tail(t_vctr *vctr)
{
	if (!vctr->entries)
		return (NULL);
	return (vctr->data + (vctr->entries - 1) * vctr->unit_size);
}

/*
void	*two_d_vctr_entry(t_vctr *grid, size_t col, size_t row, size_t wid)
{
	return ((void *)(&grid->data[col * grid->unit_size +
				(row * wid) * grid->unit_size]));
}
*/
