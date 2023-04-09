/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:52:53 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/12/05 10:41:28 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static void	t_strlst_print(t_str_list  *lst)
{
	printf("t_strlst_print\n");
	while (lst)
	{
		printf("%s", lst->s);
		lst = lst->next;
	}
}

static void	t_strlst_new(t_str_list **strs, char *s, int len)
{
	int		i;
	char	*s0;
	t_str_list	*new;
	t_str_list	*last;

	if (len <= 0)
		return ;
	new = malloc(sizeof(t_str_list)); 
	if (!new)
		return ;
	s0 = malloc(sizeof(char) * (len + 1)); 
	if (!s0)
		return ;
	i = 0;
	while (s[i] && i < len)
	{
		s0[i] = s[i];
		i++;
	}
	s0[i] = 0;
	new->s = s0;
	new->next = 0;
	if (*strs)
	{
		last = *strs;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*strs = new;
}

static void	t_strlst_clear(t_str_list  **strs)
{
	t_str_list	*lst;

	lst = *strs;
	if (lst)
	{
		t_strlst_clear(&(lst->next));
		free(lst->s);
		free(lst);
	}	
	*strs = 0;
}

static char	*strlst_str(t_str_list *strs)
{
	int		i;
	int		size;
	char	*s;
	t_str_list	*lst;

	lst = strs;
	size = 0;
	while (lst)
	{
		i = -1;
		while (lst->s[++i])
			size++;
		lst = lst->next;
	}
	s = malloc(sizeof(char) * (size + 1));
	if (!s)
		return (0);
	lst = strs;
	size = 0;
	while (lst)
	{
		i = -1;
		while (lst->s[++i])
			s[size++] = lst->s[i];
		lst = lst->next;
	}
	s[size] = 0;
	return (s);
}

int	newline_pos(char *s)
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

char	*get_strs(t_str_list *strs, char *buf, int pos)
{
	int		i;
	char	*s;

	//printf("buf %s\n", buf);
	//printf("pos = %d\n", pos);
	t_strlst_new(&strs, buf, pos + 1);
	i = 0;
	while (buf[pos + i + 1])
	{
		buf[i] = buf[pos + i + 1];
		i++;
	}
	buf[i] = 0;
	s = strlst_str(strs);
	t_strlst_clear(&strs);
	return (s);
}

char	*get_next_line(int fd)
{
	int		ret;
	int		pos;
	static char	buf[BUFFER_SIZE + 1];
	t_str_list	*strs;	

	strs = 0;
	if (*buf)
	{
		pos = newline_pos(buf);
		if (pos == -1)
			t_strlst_new(&strs, buf, BUFFER_SIZE);
		else
			return (get_strs(strs, buf,  pos));
	}
	ret = 1;
	pos = -1;
	while (ret && pos == -1)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (0);
		if (ret)
		{
			buf[ret] = 0;
			pos = newline_pos(buf);
			if (pos == -1)
				t_strlst_new(&strs, buf, ret);
			else
				return (get_strs(strs, buf,  pos));
		}
	}
	//t_strlst_print(strs);
	return (0);
}
