/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:52:53 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/16 16:41:59 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	newline_pos(char *s)
{
	int	pos;

	pos = 0;
	while (s[pos] && s[pos] != '\n')
		pos++;
	if (pos == 0 && s[pos] != '\n')
		return (-1);
	if (s[pos] == '\n')
		return (pos);
	else
		return (-1);
}


size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if ((!dest) && (!src))
		return (dest);
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup(char *src)
{
	char	*o;

	o = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!o)
		return (0);
	return (ft_memcpy(o, src, ft_strlen(src) + 1));
}

int	get_line(char *buf, char *s)
{
	char	*new;
	int		pos;

	pos = -1;
	if (!*buf)
		return (pos);
	pos = newline_pos(buf);
	if (pos == -1)
	{
		s = ft_strdup(buf);	
		buf[0] = 0;
	}
	else
	{
		buf[pos] = 0;
		new = malloc(sizeof(char) * (ft_strlen(s) + pos));	
		new = ft_memcpy(new, s, ft_strlen(s));	
		s = ft_strdup(buf);	
		ft_memcpy(buf, &buf[pos + 1], ft_strlen(buf) - pos);
		return (s);
	}
	return (pos);
}

char	*get_next_line(int fd)
{
	static t_fd	fdl[1024];
	t_fd		*f;
	char		*s;	
	char		con[CONTAINER_SIZE + 1];
	char		buf[BUFFER_SIZE + 1];
	char		*out;
	int			i;
	int			pos;
	int			ret;

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
	s = malloc(sizeof(char));
	s[0] = 0;
	pos = get_line(buf, s);
	if (pos != -1)
		return (s);
	if (CONTAINER_SIZE > 10 * BUFFER_SIZE)
		b = &con[0];
	else
		b = &buf[0];
	if (CONTAINER_SIZE > 10 * BUFFER_SIZE)
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
	return (s);
}
