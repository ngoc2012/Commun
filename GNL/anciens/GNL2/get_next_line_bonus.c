/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:52:53 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/16 15:31:51 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_line(int fd, char *buf, int pos, t_str_list *strs)
{
	t_containter	c;
	char			con[CONTAINER_SIZE + 1];
	char			*b;

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
	printf("get_next_line_buf\n");
	return (get_next_line_buf(fd, buf, strs, pos));
}

static char	*get_next_line_ini(int fd, char *buf)
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
	static t_fd	fdl[1024];
	t_fd		*f;
	char		buf[BUFFER_SIZE + 1];
	char		*out;
	int			i;

	f = 0;
	i = -1;
	while (++i < 1024 && fdl[i].buf)
		if (fd == fdl[i].fd)
			f = &fdl[i];
	if (!f)
	{
		f = &fdl[i];
		f->fd = fd;
		f->buf = malloc(sizeof(char));
		f->buf[0] = 0;
	}
	if (*(f->buf))
	{
		i = -1;
		while (f->buf[++i])
			buf[i] = f->buf[i];
		free(f->buf);
	}
	out = get_next_line_ini(fd, buf);
	if (*buf)
	{
		i = 0;
		while (buf[i])
			i++;
		free(f->buf);
		f->buf = malloc(sizeof(char) * (i + 1));
		i = -1;
		while (buf[++i])
			f->buf[i] = buf[i];
		f->buf[++i] = 0;
	}
	return (out);
}
