/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 07:47:36 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/19 04:02:47 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s0;

	s0 = (unsigned char *) s;
	i = 0;
	while (i < n)
		s0[i++] = c;
	return (s);
}
