/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:00:51 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/15 12:57:58 by minh-ngu         ###   ########.fr       */
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
	size_t	start;
	size_t	end;
}	t_fd;

typedef struct s_fd_list
{
	int		n;
	t_fd	fds[1024];
	char	buf[100000000];
}	t_fd_list;

#endif
