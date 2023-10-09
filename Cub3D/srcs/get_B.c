/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_B.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   by: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:30:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/09 20:56:40 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_b(t_game *g, int ix, float ai)
{
	int	bx;
	int	by;
	float	bpx;
	float	bpy;
	float	dpx;
	float	dpy;
	int	door_coor;

	if (ai > -90.0 && ai < 90.0)
	{
		bpx = ((int) (g->pos.px / BOX_SIZE)) * BOX_SIZE + BOX_SIZE;
		dpx = BOX_SIZE;
	}
	else
	{
		bpx = ((int) (g->pos.px / BOX_SIZE)) * BOX_SIZE;
		dpx = -BOX_SIZE;
	}
	bpy = g->pos.py + (g->pos.px - bpx) * g->tan_ai[ix][g->pos.rot];
	dpy = BOX_SIZE * g->tan_ai[ix][g->pos.rot];
	if (ai * dpy > 0)
		dpy = -dpy;
	if (bpy < 0 || bpy >= g->map.ph)
	{
		g->pos.dB = INFINI;
		return ;
	}
	by = bpy / BOX_SIZE;
	if (ai > -90.0 && ai < 90.0)
		bx = bpx / BOX_SIZE;
	else
		bx = bpx / BOX_SIZE - 1;
	door_coor = (int) (bpy + dpy / 2 - BOX_SIZE * (float) by);
	while ((bx >= 0 && bx < g->map.l) && (by >= 0 && by < g->map.h) &&
			((g->map.v[by][bx] != b_wall && g->map.v[by][bx] != b_door)
			 || (by == g->opened_door_y && bx == g->opened_door_x && g->map.v[by][bx] == b_door && door_coor < g->hidden_door)))
	{
		bpx += dpx;
		bpy += dpy;
		by = bpy / BOX_SIZE;
		if (ai > -90.0 && ai < 90.0)
			bx = bpx / BOX_SIZE;
		else
			bx = bpx / BOX_SIZE - 1;
		door_coor = (int) (bpy + dpy / 2 - BOX_SIZE * (float) by);
	}
	if (bx < 0 || bx >= g->map.l || by < 0 || by >= g->map.h)
	{
		g->pos.dB = INFINI;
		return ;
	}
	if (g->map.v[by][bx] == b_door && ai > -90.0 && ai < 90.0)
	{
		g->pos.dB = (bpx - g->pos.px + BOX_SIZE / 2) / g->cos_ai[ix][g->pos.rot];
		bpy += dpy / 2;
	}
	else if (g->map.v[by][bx] == b_door)
	{
		g->pos.dB = (bpx - g->pos.px - BOX_SIZE / 2) / g->cos_ai[ix][g->pos.rot];
		bpy += dpy / 2;
	}
	else
		g->pos.dB = (bpx - g->pos.px) / g->cos_ai[ix][g->pos.rot];
	g->pos.bx = bx;
	g->pos.by = by;
	g->pos.bpy = bpy;
}
