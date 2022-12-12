/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:52:53 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/04 15:17:23 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static void	t_file_delone(t_file	*f)
{
}

size_t	get_len(int fd)
{
	int		ret;
	size_t	len;
	size_t	i;

	len = 0;
	ret = 1;
	while (ret)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = 0;
		i = 0;
		while (buf[i] && buf[i] != '\n')
			i++;
		if (buf[i] == '\n')
			len += i + 1;
		else
			len += i;
	}
	return (len);
}

void	get_next(int fd)
{
	int		ret;
	char	*s;
	char	buf[BUFFER_SIZE];
	//static t_file	f;

	ret = read(fd, buf, BUFFER_SIZE);
	buf[ret] = 0;
	printf("2====%s\n", buf);
}

char	*get_next_line(int fd)
{
	int		ret;
	char	*s;
	static char	buf[BUFFER_SIZE];
	//static t_file	f;

	ret = read(fd, buf, BUFFER_SIZE);
	buf[ret] = 0;
	printf("1====%s\n", buf);
	get_next(fd);
	//f->fd = fd;
	//f->pos = 0;
	//f->next = 0;
	//s = malloc(sizeof(char) (get_len(fd) + 1));
	//ret = 1;
	//while (ret)
	//{
	//	ret = read(fd, buf, BUFFER_SIZE);
	//	buf[ret] = 0;
	//	if (ret)
	//		printf("%s\n", buf);
	//}
	s = malloc(sizeof(char));
	s[0] = 0;
	return s;
}
