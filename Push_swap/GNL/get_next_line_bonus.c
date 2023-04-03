/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:52:53 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/07 18:03:09 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "get_next_line.h"
#include "get_next_line_bonus.h"

static char	*get_strs0(t_str_list *strs)
{
	char		*s;
	t_str_list	*lst;
	t_str_list	*next;

	if (!strs)
		return (0);
	s = strlst_str(strs);
	lst = strs;
	while (lst)
	{
		next = lst->next;
		free(lst->s);
		free(lst);
		lst = 0;
		lst = next;
	}	
	return (s);
}

static char	*get_container(t_str_list *strs, t_containter c, char *con)
{
	while (c.ret)
	{
		if (c.icon + 1 > CONTAINER_SIZE)
		{
			t_strlst_new(&strs, con, c.icon);
			c.icon = 0;
		}
		c.ret = read(c.fd, &con[c.icon], c.size);
		if (c.ret == -1)
			return (0);
		if (c.ret)
		{
			con[c.icon + c.ret] = 0;
			if (con[c.icon] == '\n')
			{
				t_strlst_new(&strs, con, c.icon + 1);
				return (get_strs0(strs));
			}
			c.icon += c.ret;
		}
		else
			t_strlst_new(&strs, con, c.icon + c.ret);
	}
	return (get_strs0(strs));
}

char	*get_next_line(int fd)
{
	t_str_list		*strs;
	t_containter	c;
	char			con[CONTAINER_SIZE + 1];

	c.fd = fd;
	c.ret = 1;
	c.icon = 0;
	c.size = 1;
	strs = 0;
	return (get_container(strs, c, con));
}
