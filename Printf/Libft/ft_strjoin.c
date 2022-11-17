/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:21:28 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/09 18:19:14 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*o;

	o = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (o == NULL)
		return (0);
	o[0] = 0;
	ft_strlcat(o, s1, ft_strlen(s1) + 1);
	ft_strlcat(o, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (o);
}
