/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:00:51 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/15 08:58:53 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include "get_next_line.h"

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
