/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wetieven <wetieven@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:18:50 by wetieven          #+#    #+#             */
/*   Updated: 2022/03/01 13:19:50 by wetieven         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *src, const char *cmp)
{
	while (*src || *cmp)
	{
		if (*src++ != *cmp++)
			return ((*(unsigned char *)--src) - (*(unsigned char *)--cmp));
	}
	return (0);
}
