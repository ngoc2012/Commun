/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:35:06 by nbechon           #+#    #+#             */
/*   Updated: 2023/10/16 14:54:12 by nbechon          ###   ########.fr       */
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

// DOWN LEFT CORNER
// UP LEFT CORNER
// UP RIGHT CORNER
// DOWN RIGHT CORNER

void	check_corner(t_game *g, int x, int w)
{
	if (g->map.v[w][g->map.l - 1] == b_ground || g->map.v[w][0] == b_ground
			|| g->map.v[w][g->map.l - 1] == b_door)
		end_game(g, 1, "Error: Invalid map\n");
	if ((g->map.v[w][x] == b_ground && g->map.v[w + 1][x] == b_wall
		&& g->map.v[w][x - 1] == b_wall && g->map.v[w + 1][x - 1] == b_empty))
		end_game(g, 1, "Error: Invalid map Empty Wall 5\n");
	if ((g->map.v[w][x] == b_ground && g->map.v[w - 1][x] == b_wall
		&& g->map.v[w][x - 1] == b_wall && g->map.v[w - 1][x - 1] == b_empty))
		end_game(g, 1, "Error: Invalid map Empty Wall 5\n");
	if ((g->map.v[w][x] == b_ground && g->map.v[w - 1][x] == b_wall
		&& g->map.v[w][x + 1] == b_wall && g->map.v[w - 1][x + 1] == b_empty))
		end_game(g, 1, "Error: Invalid map Empty Wall 5\n");
	if ((g->map.v[w][x] == b_ground && g->map.v[w + 1][x] == b_wall
		&& g->map.v[w][x + 1] == b_wall && g->map.v[w + 1][x + 1] == b_empty))
		end_game(g, 1, "Error: Invalid map Empty Wall 5\n");
}

void	check(int x, int w, t_game *g)
{
	if (g->map.v[0][x] == b_ground || g->map.v[g->map.h - 1][x]
		== b_ground || g->map.v[0][x] == b_door
		|| g->map.v[g->map.h - 1][x] == b_door)
		end_game(g, 1, "Error: Invalid map Ground Wall 1\n");
	if (x != 0)
		if ((g->map.v[w][x] == b_ground && g->map.v[w][x - 1] == b_empty)
			|| g->map.v[w][0] == b_door)
			end_game(g, 1, "Error: Invalid map Empty Wall 2\n");
	if (w != 0)
		if (g->map.v[w][x] == b_ground && g->map.v[w - 1][x] == b_empty)
			end_game(g, 1, "Error: Invalid map Empty Wall 3\n");
	if (x != g->map.l - 1)
		if (g->map.v[w][x] == b_ground && g->map.v[w][x + 1] == b_empty)
			end_game(g, 1, "Error: Invalid map Empty Wall 4\n");
	if (g->map.v[w][x] == b_door && g->map.v[w][x + 1] == b_empty)
		end_game(g, 1, "Error: Invalid map Empty Wall 4\n");
	check_corner(g, x, w);
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
		w++;
	}
}
