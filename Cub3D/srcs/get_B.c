/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_B.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 05:30:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/09 20:53:54 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_b(t_game *g, int ix, float ai)
{
	int	Bx;
	int	By;
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
	By = bpy / BOX_SIZE;
	if (ai > -90.0 && ai < 90.0)
		Bx = bpx / BOX_SIZE;
	else
		Bx = bpx / BOX_SIZE - 1;
	door_coor = (int) (bpy + dpy / 2 - BOX_SIZE * (float) By);
	while ((Bx >= 0 && Bx < g->map.l) && (By >= 0 && By < g->map.h) &&
			((g->map.v[By][Bx] != b_wall && g->map.v[By][Bx] != b_door)
			 || (By == g->opened_door_y && Bx == g->opened_door_x && g->map.v[By][Bx] == b_door && door_coor < g->hidden_door)))
	{
		bpx += dpx;
		bpy += dpy;
		By = bpy / BOX_SIZE;
		if (ai > -90.0 && ai < 90.0)
			Bx = bpx / BOX_SIZE;
		else
			Bx = bpx / BOX_SIZE - 1;
		door_coor = (int) (bpy + dpy / 2 - BOX_SIZE * (float) By);
	}
	if (Bx < 0 || Bx >= g->map.l || By < 0 || By >= g->map.h)
	{
		g->pos.dB = INFINI;
		return ;
	}
	if (g->map.v[By][Bx] == b_door && ai > -90.0 && ai < 90.0)
	{
		g->pos.dB = (bpx - g->pos.px + BOX_SIZE / 2) / g->cos_ai[ix][g->pos.rot];
		bpy += dpy / 2;
	}
	else if (g->map.v[By][Bx] == b_door)
	{
		g->pos.dB = (bpx - g->pos.px - BOX_SIZE / 2) / g->cos_ai[ix][g->pos.rot];
		bpy += dpy / 2;
	}
	else
		g->pos.dB = (bpx - g->pos.px) / g->cos_ai[ix][g->pos.rot];
	g->pos.Bx = Bx;
	g->pos.By = By;
	g->pos.bpy = bpy;
}
