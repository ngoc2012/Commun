/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:00:51 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/16 15:34:11 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# define CONTAINER_SIZE 100

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_str_list
{
	char				*s;
	struct s_str_list	*next;
}	t_str_list;

typedef struct s_container
{
	int					fd;
	int					pos;
	int					ret;
	int					icon;
	unsigned long long	size;
}	t_containter;

typedef struct s_fd
{
	int		fd;
	char	*buf;
}	t_fd;

void	t_strlst_new(t_str_list **strs, char *s, int len);
char	*get_strs(t_str_list *strs, char *buf, char *src, int start);

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

static char	*get_container_line_con(char *con, char *buf, t_str_list *strs,
		t_containter c)
{
	while (c.ret)
	{
		if (c.icon + BUFFER_SIZE > CONTAINER_SIZE)
		{
			t_strlst_new(&strs, con, c.icon);
			c.icon = 0;
		}
		c.ret = read(c.fd, &con[c.icon], BUFFER_SIZE);
		if (c.ret == -1)
			return (0);
		if (c.ret)
		{
			con[c.icon + c.ret] = 0;
			c.pos = newline_pos(&con[c.icon]);
			if (c.pos != -1)
			{
				t_strlst_new(&strs, con, c.icon + c.pos + 1);
				return (get_strs(strs, buf, &con[c.icon], c.pos + 1));
			}
			c.icon += c.ret;
		}
		else
			t_strlst_new(&strs, con, c.icon + c.ret);
	}
	return (get_strs(strs, buf, con, c.pos + 1));
}

static char	*get_next_line_buf(int fd, char *buf, t_str_list *strs, int pos)
{
	int		ret;

	ret = 1;
	while (ret && pos == -1)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (0);
		buf[ret] = 0;
		if (ret)
		{
			pos = newline_pos(buf);
			if (pos == -1)
			{
				t_strlst_new(&strs, buf, ret);
				if (ret < BUFFER_SIZE)
					return (get_strs(strs, buf, buf, ret));
				else
					buf[0] = 0;
			}
			else
				t_strlst_new(&strs, buf, pos + 1);
		}
	}
	return (get_strs(strs, buf, buf, pos + 1));
}

char	*get_next_line(int fd);

#endif
