/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:25:55 by minh-ngu          #+#    #+#             */
/*   Updated: 2023/04/27 15:39:44 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER 100

char	*get_next_line(int fd)
{
	int	ret;
	static char	buf[BUFFER + 1];
	char	*s;

	while (ret)
	{
		ret = read(fd, buf, BUFFER);
	}
	return (0);
}

int	main()
{
	fd = open("ft_printf.c", O_RDONLY);
	get_next_line(fd);
}
