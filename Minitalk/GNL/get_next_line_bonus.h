/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:00:51 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/07 16:53:08 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# define CONTAINER_SIZE 100

# include <stdio.h>
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

char	*get_next_line(int fd);
void	t_strlst_new(t_str_list **strs, char *s, int len);
//void	t_strlst_clear(t_str_list **strs);
char	*get_strs(t_str_list *strs, char *buf, char *src, int start);
char	*strlst_str(t_str_list *strs);

#endif
