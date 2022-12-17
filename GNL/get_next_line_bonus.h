/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:00:51 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/17 06:58:27 by minh-ngu         ###   ########.fr       */
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

typedef struct s_fd
{
	int		fd;
	int		bs;
	char	*buf;
}	t_fd;

char	*get_next_line(int fd);

#endif
