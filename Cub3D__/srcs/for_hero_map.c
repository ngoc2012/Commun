/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_hero_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:35:06 by nbechon           #+#    #+#             */
/*   Updated: 2023/10/10 13:21:29 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_hero_map(int yp, int xp, int *addr)
{
	int	i;
	int	j;

	yp -= 3;
	xp -= 5;
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			addr[yp * WIDTH + (xp + j)] = create_trgb(1, 255, 0, 0);
			j++;
		}
		yp += 1;
		i++;
	}
}
