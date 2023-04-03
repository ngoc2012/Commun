/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vctr_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:24:57 by wetieven          #+#    #+#             */
/*   Updated: 2022/03/01 16:23:27 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vct.h"

t_error	vctr_insert(t_vctr *vctr, size_t insertion_index, void *data)
{
	void	*replaced_entry;
	void	*next_to_replaced;

	if (!vctr->entries || insertion_index >= vctr->entries)
		return (vctr_push(vctr, data));
	if (vctr->entries == vctr->capacity)
		if (vctr_extd(vctr, vctr->init_count))
			return (MEM_ALLOC);
	replaced_entry = vctr_entry(vctr, insertion_index);
	next_to_replaced = replaced_entry + vctr->unit_size;
	ft_memmove(next_to_replaced, replaced_entry,
		vctr->entries * vctr->unit_size - (replaced_entry - vctr->data));
	ft_memcpy(replaced_entry, data, vctr->unit_size);
	vctr->entries++;
	return (CLEAR);
}

// Removes an entry and shifts the rest of the vctr entries over it
t_error	vctr_remove(t_vctr *vctr, size_t entry, t_error (*free_entry)(void *))
{
	void	*deleted_entry;
	void	*next_to_deleted;
	t_error	error;

	error = CLEAR;
	deleted_entry = vctr_entry(vctr, entry);
	if (!deleted_entry)
		return (PARSE);
	if (free_entry)
		error = (*free_entry)(deleted_entry);
	if (error)
		return (error);
	next_to_deleted = deleted_entry + vctr->unit_size;
	ft_memcpy(deleted_entry, next_to_deleted,
		vctr->capacity * vctr->unit_size - (next_to_deleted - vctr->data));
	vctr->entries--;
	return (CLEAR);
}

t_error	vctr_iter(t_vctr *vctr, t_error (*fct)(void *))
{
	t_error	error;
	size_t	idx;

	error = CLEAR;
	idx = 0;
	while (!error && idx < vctr->entries)
		error = (fct)(vctr_entry(vctr, idx++));
	return (error);
}

// Erases (and if needed, frees) a vector's content so we can reuse it.
t_error	vctr_recycle(t_vctr *vctr, t_error (*free_ctnt)(void *))
{
	t_error	error;

	error = CLEAR;
	if (free_ctnt)
		error = vctr_iter(vctr, free_ctnt);
	if (!error)
	{
		ft_bzero(vctr->data, vctr->entries * vctr->unit_size);
		vctr->entries = 0;
	}
	return (error);
}
