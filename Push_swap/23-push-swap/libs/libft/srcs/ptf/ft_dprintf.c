/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:39:39 by wetieven          #+#    #+#             */
/*   Updated: 2022/02/10 13:41:23 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ptf_parsing.h"
#include "ptf_converters.h"

int	ft_dprintf(int fd, const char *src, ...)
{
	va_list	args;
	int		prt_len;
	t_vctr	*vct;

	va_start(args, src);
	vctr_init(&vct, sizeof(char), 512);
	if (!vct)
		return (0);
	prt_len = ptf_parser(vct, (char **)&src, args);
	if (prt_len)
		write(fd, vct->data, vct->entries);
	vctr_exit(vct);
	va_end(args);
	return (prt_len);
}
