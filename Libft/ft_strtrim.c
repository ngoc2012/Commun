/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:26:39 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/09 09:31:46 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;
	size_t		i;
	char	*o;

	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		start++;
	if (start == ft_strlen(s1))
		return (NULL);
	end = ft_strlen(s1) - 1;
	while (end > 0 && ft_strchr(set, s1[end]) != NULL)
		end--;
	printf("start %ld, end %ld\n", start, end);
	o = malloc(sizeof(char) * (end - start + 1));
	i = 0;
	while (start < end)
		o[i++] = s1[start++];
	return (o);
}
