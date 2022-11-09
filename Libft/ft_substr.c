/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:09:14 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/09 18:15:46 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*o;
	unsigned int	i;

	if (len == 0 || (size_t) ft_strlen(s) <= start)
		return (0);
	o = malloc(sizeof(char) * (len + 1));
	if (o == NULL)
		return (0);
	i = 0;
	while (i < len && s[start + i])
	{
		o[i] = s[start + i];
		i++;
	}
	o[i] = 0;
	return (o);
}
