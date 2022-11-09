/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:09:14 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/09 09:41:44 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*o;
	unsigned int	i;

	if (ft_strlen(s) <= start || len == 0)
		return (NULL);
	o = malloc(sizeof(char) * (len + 1));
	if (o == NULL)
		return (NULL);
	len += start;
	printf("start %d, len %ld\n", start, len);
	i = 0;
	while (start < len && s[start])
		o[i++] = s[start++];
	printf("start %d, len %ld, i %d\n", start, len, i);
	o[i] = 0;
	return (o);
}
