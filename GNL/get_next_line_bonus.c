/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:52:53 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/17 07:30:38 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	newline_pos(char *s)
{
	int	pos;

	pos = 0;
	if (!*s)
		return (-1);
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

int	get_line(char *buf, char *con, char **s)
{
	char	*new;
	int		pos;
	int		ls;
	int		lc;
	int		lc1;

	if (!*con)
		return (-1);
	ls = ft_strlen(*s);
	lc = ft_strlen(con);
	pos = newline_pos(con);
	lc1 = lc;
	if (pos != -1)
		lc1 = pos + 1;
	new = malloc(sizeof(char) * (ls + lc1 + 1));
	ft_memcpy(new, *s, ls);	
	ft_memcpy(&new[ls], con, lc1);	
	new[ls + lc1] = 0;
	free(*s);
	*s = new;
	if (pos == -1)
		buf[0] = 0;
	else
		ft_memcpy(buf, &con[pos + 1], lc - pos);
	return (pos);
}

char	*get_out_put(char *s, char *buf, t_fd *f)
{
	if (*buf)
	{
		f->bs = ft_strlen(buf);
		f->buf = malloc(sizeof(char) * (ft_strlen(buf) + 1));
		ft_memcpy(f->buf, buf, ft_strlen(buf) + 1);
	}
	else
		f->bs = 0;
	free(buf);
	if (*s)
		return (s);
	free(s);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_fd	fdl[1024];
	t_fd		*f;
	char		*s;	
	char		con[CONTAINER_SIZE + 1];
	char		*buf;
	char		*b;
	int			icon;
	int			pos;
	int			ret;
	int			i;

	if (CONTAINER_SIZE > 10 * BUFFER_SIZE)
		buf = malloc(sizeof(char) * (CONTAINER_SIZE + 1));
	else
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	buf[0] = 0;
	con[0] = 0;
	f = 0;
	i = -1;
	while (++i < 1024 && fdl[i].buf)
		if (fd == fdl[i].fd)
			f = &fdl[i];
	if (!f)
	{
		f = &fdl[i];
		f->fd = fd;
		f->bs = 0;
	}
	if (f->bs > 0)
	{
		ft_memcpy(buf, f->buf, ft_strlen(f->buf) + 1);
		free(f->buf);
		f->bs = 0;
	}
	s = malloc(sizeof(char));
	s[0] = 0;
	if (*buf)
	{
		pos = get_line(buf, buf, &s);
		if (pos != -1)
			return (get_out_put(s, buf, f));
	}
	b = &buf[0];
	if (CONTAINER_SIZE > 10 * BUFFER_SIZE)
		b = &con[0];
	ret = 1;
	while (ret)
	{
		if (CONTAINER_SIZE > 10 * BUFFER_SIZE)
		{
			icon = 0;
			while (ret && (icon + BUFFER_SIZE) < CONTAINER_SIZE)
			{
				ret = read(fd, &con[icon], BUFFER_SIZE);
				if (ret == -1)
				{
					free(buf);
					free(s);
					return (0);
				}
				icon += ret;
			}
			b[icon] = 0;
			//printf("con: b = #%s#\n", b);
		}
		else
		{
			ret = read(fd, buf, BUFFER_SIZE);
			if (ret == -1)
			{
				free(buf);
				free(s);
				return (0);
			}
			b[ret] = 0;
			//printf("buf: b = #%s#\n", b);
		}
		pos = get_line(buf, b, &s);
		if (pos != -1)
			return (get_out_put(s, buf, f));
	}
	return (get_out_put(s, buf, f));
}
