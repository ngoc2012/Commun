/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_if.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:33:52 by ngoc              #+#    #+#             */
/*   Updated: 2023/05/30 12:53:53 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstremove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*del)(void *))
{
	t_list	*remove;
	t_list	*cur;

	if (!begin_list || !(*begin_list))
		return ;
	cur = *begin_list;
	while (cur && !(*cmp)(cur->content, data_ref))
	{
		remove = cur;
		cur = remove->next;
		del(remove->content);
		free(remove);
	}
	*begin_list = cur;
	while (cur)
	{
		if (cur->next && !(*cmp)(cur->next->content, data_ref))
		{
			remove = cur->next;
			cur->next = remove->next;
			del(remove->content);
			free(remove);
		}
		cur = cur->next;
	}
}
