/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_A.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:27:15 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/09 05:27:56 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_A(t_game *g, int ix, float ai)
{
	int	door_coor;

	if (ai > 0.0)
	{
		g->pos.Apy = ((int) (g->pos.py / BOX_SIZE)) * BOX_SIZE;
		g->pos.dpy = -BOX_SIZE;
	}
	else
	{
		g->pos.Apy = ((int) (g->pos.py / BOX_SIZE)) * BOX_SIZE + BOX_SIZE;
		g->pos.dpy = BOX_SIZE;
	}
	g->pos.Apx = g->pos.px + (g->pos.py - g->pos.Apy) * g->cos_ai[ix][g->pos.rot] / g->sin_ai[ix][g->pos.rot];
	g->pos.dpx = BOX_SIZE * g->cos_ai[ix][g->pos.rot] / g->sin_ai[ix][g->pos.rot];
	if (ai < 0)
		g->pos.dpx = -g->pos.dpx;
	if (g->pos.Apx < 0 || g->pos.Apx >= g->map.pl)
	{
		g->pos.dA = INFINI;
		return ;
	}
	g->pos.Ax = g->pos.Apx / BOX_SIZE;
	if (ai > 0.0)
		g->pos.Ay = g->pos.Apy / BOX_SIZE - 1;
	else
		g->pos.Ay = g->pos.Apy / BOX_SIZE;
	door_coor = (int) (g->pos.Apx + g->pos.dpx / 2 - BOX_SIZE * (float) g->pos.Ax);
	while ((g->pos.Ax >= 0 && g->pos.Ax < g->map.l) && (g->pos.Ay >= 0 && g->pos.Ay < g->map.h) &&
			((g->map.v[g->pos.Ay][g->pos.Ax] != B_WALL && g->map.v[g->pos.Ay][g->pos.Ax] != B_DOOR)
			 || (g->pos.Ay == g->opened_door_y && g->pos.Ax == g->opened_door_x && g->map.v[g->pos.Ay][g->pos.Ax] == B_DOOR && door_coor < g->hidden_door)))
	{
		g->pos.Apx += g->pos.dpx;
		g->pos.Apy += g->pos.dpy;
		g->pos.Ax = g->pos.Apx / BOX_SIZE;
		if (ai > 0.0)
			g->pos.Ay = g->pos.Apy / BOX_SIZE - 1;
		else
			g->pos.Ay = g->pos.Apy / BOX_SIZE;
		door_coor = (int) (g->pos.Apx + g->pos.dpx / 2 - BOX_SIZE * (float) g->pos.Ax);
	}
	if (g->pos.Ax < 0 || g->pos.Ax >= g->map.l || g->pos.Ay < 0 || g->pos.Ay >= g->map.h)
	{
		g->pos.dA = INFINI;
		return ;
	}
	if (g->map.v[g->pos.Ay][g->pos.Ax] == B_DOOR && ai > 0.0)
	{
		g->pos.dA = (g->pos.py - g->pos.Apy + BOX_SIZE / 2) / g->sin_ai[ix][g->pos.rot];
		g->pos.Apx += g->pos.dpx / 2;
	}
	else if (g->map.v[g->pos.Ay][g->pos.Ax] == B_DOOR)
	{
		g->pos.dA = (g->pos.py - g->pos.Apy - BOX_SIZE / 2) / g->sin_ai[ix][g->pos.rot];
		g->pos.Apx += g->pos.dpx / 2;
	}
	else
		g->pos.dA = (g->pos.py - g->pos.Apy) / g->sin_ai[ix][g->pos.rot];
}
