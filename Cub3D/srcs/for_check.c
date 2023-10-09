/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:33:50 by nbechon           #+#    #+#             */
/*   Updated: 2023/10/09 17:42:35 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_map(char *s)
{
	char	*s0;

	s0 = s;
	while (ft_strchr(" 	\n", *s0))
		s0++;
	if (!*s0)
		return (0);
	while (*s)
		if (!ft_strchr(MAP_CHAR, *(s++)))
			return (0);
	return (1);
}

void	check(int x, int w, t_game *g)
{
	if (g->map.v[0][x] == b_ground || g->map.v[g->map.h - 1][x]
		== b_ground)
		end_game(g, 1, "Invalid map\n");
	if (x != 0)
		if (g->map.v[w][x] == b_ground && g->map.v[w][x - 1] == b_empty)
			end_game(g, 1, "Invalid map\n");
	if (w != 0)
		if (g->map.v[w][x] == b_ground && g->map.v[w - 1][x] == b_empty)
			end_game(g, 1, "Invalid map\n");
	if (g->map.v[w][x] == b_ground && g->map.v[w][x + 1] == b_empty
		|| g->map.v[w][x] == b_ground && g->map.v[w + 1][x] == b_empty)
		end_game(g, 1, "Invalid map\n");
}

void	verif_wall(t_game *g)
{
	int	w;
	int	x;

	w = 0;
	while (w < g->map.h)
	{
		x = 0;
		while (x < g->map.l)
		{
			check(x, w, g);
			x++;
		}
		if (g->map.v[w][g->map.l - 1] == b_ground || g->map.v[w][0] == b_ground)
			end_game(g, 1, "Invalid map\n");
		w++;
	}
	if (g->map.h < 10 || g->map.l < 10)
		end_game(g, 1, "Invalid map\n");
}
