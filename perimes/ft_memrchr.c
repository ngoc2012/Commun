/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:25:20 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/08 13:17:43 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memrchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s0;
	void			*o;

	s0 = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (s0[i] == c)
			o = &(s0[i]);
		i++;
	}
	return (o);
}
