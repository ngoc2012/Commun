/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:52:53 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/15 08:59:51 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line_ini(int fd, char *buf)
{
	int			pos;
	t_str_list	*strs;	

	pos = -1;
	strs = 0;
	if (*buf)
	{
		pos = newline_pos(buf);
		if (pos == -1)
		{
			t_strlst_new(&strs, buf, BUFFER_SIZE);
			buf[0] = 0;
		}
		else
		{
			t_strlst_new(&strs, buf, pos + 1);
			return (get_strs(strs, buf, buf, pos + 1));
		}
	}
	return (get_line(fd, buf, pos, strs));
}

char	*get_next_line(int fd)
{
	static t_fd_list	fdl;
	char	buf[BUFFER_SIZE + 1];
	char	*out;

	if (!fdl.buf[0])
		fdl.n = 0;
	out = get_next_line_ini(fd, buf);
	return (out);
}
