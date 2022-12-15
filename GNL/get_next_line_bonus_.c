/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:52:53 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/14 19:06:17 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>

char	*get_next_line_ini(int fd, char *buf)
{
	t_containter	c;
	int			pos;
	char		con[CONTAINER_SIZE + 1];
	t_str_list	*strs;	
	char		*b;

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
	c.fd = fd;
	c.ret = 1;
	c.icon = 0;
	c.pos = pos;
	c.size = BUFFER_SIZE;
	if (CONTAINER_SIZE > 10 * BUFFER_SIZE)
		b = &con[0];
	else
		b = &buf[0];
	if (CONTAINER_SIZE > 10 * BUFFER_SIZE)
		return (get_container_line_con(b, buf, strs, c));
	return (get_next_line_buf(fd, buf, strs, pos));
}



char	*get_next_line(int fd)
{
	static t_fd_list	fdl;
	char	*buf[BUFFER_SIZE + 1];
	char	*out;

	if (!fdl.buf[0])
		fdl.n = 0;
	out = get_next_line_ini(fd, buf);
	return (out);
}
