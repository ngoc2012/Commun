/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:25:20 by minh-ngu          #+#    #+#             */
/*   Updated: 2022/11/08 13:16:54 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	*o;

	o = (char *) s;
	while (*o)
	{
		if (*o == c)
			return (o);
		o++;
	}
	return (0);
}
