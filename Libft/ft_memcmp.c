/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:23:10 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/16 11:07:45 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*t1;
	unsigned char	*t2;

	if ((!s1) || (!s2) || (n <= 0))
		return (-1);
	t1 = (unsigned char *) s1;
	t2 = (unsigned char *) s2;
	while (n != 0 && (*t1 == *t2))
	{
		t1++;
		t2++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return (*t1 - *t2);
}
