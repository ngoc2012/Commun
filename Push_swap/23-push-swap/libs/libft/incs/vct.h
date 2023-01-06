/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:18:02 by wetieven          #+#    #+#             */
/*   Updated: 2022/03/01 12:59:36 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VCT_H
# define VCT_H

# include <stddef.h>
# include "err.h"
# include "mem.h"

typedef struct s_vctr {
	void			*data;
	size_t			entries;
	size_t			unit_size;
	size_t			init_count;
	size_t			capacity;
}	t_vctr;

// Vector write
t_error	vctr_init(t_vctr **vct, size_t unit_size, size_t init_count);
t_error	vctr_push(t_vctr *vct, void *data);
t_error	str_to_vctr(t_vctr *vct, char *str);
t_error	vctr_extd(t_vctr *vct, size_t increase);
void	vctr_exit(t_vctr *vct);

// Vector edit
t_error	vctr_iter(t_vctr *vctr, t_error (*fct)(void *));
t_error	vctr_remove(t_vctr *vctr, size_t entry, t_error (*free_entry)(void *));
t_error	vctr_insert(t_vctr *vctr, size_t insertion_index, void *data);
t_error	vctr_recycle(t_vctr *vctr, t_error (*free_ctnt)(void *));

// Vector nav
void	*vctr_entry(t_vctr *vctr, size_t index);
void	*vctr_tail(t_vctr *vctr);

#endif
