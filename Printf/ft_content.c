/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_content.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:23:04 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/26 22:07:06 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

t_content	*ft_new_content(char type, char *str)
{
	t_content	*new_content;

	if (!str && type != 'c')
		return (0);
	new_content = malloc(sizeof(t_content));
	if (!new_content)
		return (0);
	new_content->type = type;
	new_content->str = str;
	return (new_content);
}

void	free_content(void	*c0)
{
	t_content	*c;

	c = (t_content *) c0;
	free(c->str);
	free(c);
}
