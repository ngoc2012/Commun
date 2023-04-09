/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:05:29 by wetieven          #+#    #+#             */
/*   Updated: 2022/02/20 09:46:02 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

typedef enum e_outcome {
	FAILURE,
	SUCCESS
}	t_outcome;

typedef enum e_error {
	ERROR = -1,
	CLEAR,
	MEM_ALLOC,
	PARSE,
	NULL_PTR,
	MEM_REALLOC,
	INCOMPLETE,
	FD_OPENING,
	FD_READ,
	FD_CLOSING,
}	t_error;

t_error	ft_err_msg(const char *msg, t_error cause);

#endif
