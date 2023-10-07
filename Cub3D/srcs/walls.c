/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/07 15:56:08 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	render(t_game *g, int ix)
{
	float	ai;
	float	d;
	int	tx;
	int	ty;
	int	h_slide;
	float	h;
	float	p;
	t_tex	*tex;
	int	*addr_f;
	int	*addr_c;
	int	*addr;
	int	*addr_t;

	ai = g->ai[ix][g->pos.rot];
	addr_f = (int *)g->tex[FL].addr;
	addr_c = (int *)g->tex[CL].addr;
	if (g->pos.dA > g->pos.dB)
	{
		d = g->pos.dB / g->cos_ai0[ix];
		tx = (int) (g->pos.Bpy - BOX_SIZE * (float) g->pos.By);
		if (g->map.v[g->pos.By][g->pos.Bx] == B_DOOR)
		{
			if (g->pos.By == g->opened_door_y && g->pos.Bx == g->opened_door_x)
				tx -= g->hidden_door;
			tex = &g->tex[DO];
		}
		else if (ai > -90 && ai < 90)
			tex = &g->tex[WE];
		else
			tex = &g->tex[EA];
	}
	else
	{
		d = g->pos.dA / g->cos_ai0[ix];
		tx = (int) (g->pos.Apx - BOX_SIZE * (float) g->pos.Ax);
		if (g->map.v[g->pos.Ay][g->pos.Ax] == B_DOOR)
		{
			if (g->pos.Ay == g->opened_door_y && g->pos.Ax == g->opened_door_x)
				tx -= g->hidden_door;
			tex = &g->tex[DO];
		}
		else if (ai > 0)
			tex = &g->tex[NO];
		else
			tex = &g->tex[SO];
	}
	if (d < 0)
		d = -d;
	h = BOX_SIZE / d * g->dpp;
	p = 1.0 / d * g->dpp;
	h_slide = (int) (BOX_SIZE / d * g->dpp);
	if (h_slide > HEIGHT)
		h_slide = HEIGHT;
	int	yp;
	addr = (int *)g->mlx.addr;
	addr_t = (int *)tex->addr;
	addr += ix;
	int	start = HEIGHT / 2 - h_slide / 2;
	float	dh;
	int	xh;
	int	yh;
	float	xph;
	float	yph;
	yp = -1;
	while (++yp < start)
	{
		if (g->cl_color)
			*addr = g->cl_color;
		else
		{
			dh = g->dpp * BOX_SIZE / 2 / (HEIGHT / 2 - yp) * g->cos_ai0[ix];
			xph = g->pos.px + dh * g->cos_ai[ix][g->pos.rot];
			yph = g->pos.py - dh * g->sin_ai[ix][g->pos.rot];
			xh = (int) (xph - ((int) (xph / BOX_SIZE)) * BOX_SIZE);
			yh = (int) (yph - ((int) (yph / BOX_SIZE)) * BOX_SIZE);
			if (xh < BOX_SIZE && xh >= 0 && yh < BOX_SIZE && yh >= 0)
				*addr = *(addr_c + xh + yh * g->tex[CL].l);
		}
		addr += WIDTH;
	}
	if (tx < BOX_SIZE && tx >= 0)
	{
		yp = -1;
		while (++yp < h_slide)
		{
			ty = (int) (((h - (float) h_slide) / 2.0 + (double) yp) / p);
			if (ty < BOX_SIZE && ty >= 0)
				*addr = *(addr_t + tx + ty * tex->l);
			addr += WIDTH;
		}
	}
	else
		addr += h_slide * WIDTH;
	yp = start + h_slide - 1;
	while (++yp < HEIGHT)
	{
		if (g->fl_color)
			*addr = g->fl_color;
		else
		{
			dh = g->dpp * BOX_SIZE / 2 / (yp - HEIGHT / 2) * g->cos_ai0[ix];
			xph = g->pos.px + dh * g->cos_ai[ix][g->pos.rot];
			yph = g->pos.py - dh * g->sin_ai[ix][g->pos.rot];
			xh = (int) (xph - ((int) (xph / BOX_SIZE)) * BOX_SIZE);
			yh = (int) (yph - ((int) (yph / BOX_SIZE)) * BOX_SIZE);
			if (xh < BOX_SIZE && xh >= 0 && yh < BOX_SIZE && yh >= 0)
				*addr = *(addr_f + xh + yh * g->tex[FL].l);
		}
		addr += WIDTH;
	}
	return (d);
}

void	get_B1(t_game *g, int ix, float ai)
{
	int	Bx;
	int	By;
	float	Bpx;
	float	Bpy;
	float	dpx;
	float	dpy;
	int	door_coor;

	if (ai > -90.0 && ai < 90.0)
	{
		Bpx = ((int) (g->pos.px / BOX_SIZE)) * BOX_SIZE + BOX_SIZE;
		dpx = BOX_SIZE;
	}
	else
	{
		Bpx = ((int) (g->pos.px / BOX_SIZE)) * BOX_SIZE;
		dpx = -BOX_SIZE;
	}
	Bpy = g->pos.py + (g->pos.px - Bpx) * g->tan_ai[ix][g->pos.rot];
	dpy = BOX_SIZE * g->tan_ai[ix][g->pos.rot];
	if (ai * dpy > 0)
		dpy = -dpy;
	if (Bpy < 0 || Bpy >= g->map.ph)
	{
		g->pos.dB = INFINI;
		return ;
	}
	if (ai > -90.0 && ai < 90.0)
		Bx = Bpx / BOX_SIZE;
	else
		Bx = Bpx / BOX_SIZE - 1;
	//By = g->pos.y;
	By = Bpy / BOX_SIZE;
	door_coor = (int) (Bpy + dpy / 2 - BOX_SIZE * (float) By);
	while ((Bx >= 0 && Bx < g->map.l) && (By >= 0 && By < g->map.h) &&
			((g->map.v[By][Bx] != B_WALL && g->map.v[By][Bx] != B_DOOR)
			 || (By == g->opened_door_y && Bx == g->opened_door_x && g->map.v[By][Bx] == B_DOOR && door_coor < g->hidden_door)))
	{
		Bpx += dpx;
		Bpy += dpy;
		if (ai > -90.0 && ai < 90.0)
			Bx = Bpx / BOX_SIZE;
		else
			Bx = Bpx / BOX_SIZE - 1;
		By = Bpy / BOX_SIZE;
		door_coor = (int) (Bpy + dpy / 2 - BOX_SIZE * (float) By);
	}
	if (Bx < 0 || Bx >= g->map.l || By < 0 || By >= g->map.h)
	{
		g->pos.dB = INFINI;
		return ;
	}
	if (g->map.v[By][Bx] == B_DOOR && ai > -90.0 && ai < 90.0)
	{
		g->pos.dB = (Bpx - g->pos.px + BOX_SIZE / 2) / cos(ai * PI / 180);
		Bpy += dpy / 2;
	}
	else if (g->map.v[By][Bx] == B_DOOR)
	{
		g->pos.dB = (Bpx - g->pos.px - BOX_SIZE / 2) / cos(ai * PI / 180);
		Bpy += dpy / 2;
	}
	else
		g->pos.dB = (Bpx - g->pos.px) / g->cos_ai[ix][g->pos.rot];
	g->pos.Bx = Bx;
	g->pos.By = By;
	g->pos.Bpy = Bpy;
}

void	get_B2(t_game *g, int ix, float ai)
{
	int	Bx;
	int	By;
	float	Bpx;
	float	Bpy;
	float	dpx;
	float	dpy;
	int	door_coor;

	if (ai > -90.0 && ai < 90.0)
	{
		Bpx = ((int) (g->pos.px / BOX_SIZE)) * BOX_SIZE + BOX_SIZE;
		dpx = BOX_SIZE;
	}
	else
	{
		Bpx = ((int) (g->pos.px / BOX_SIZE)) * BOX_SIZE;
		dpx = -BOX_SIZE;
	}
	Bpy = g->pos.py + (g->pos.px - Bpx) * g->tan_ai[ix][g->pos.rot];
	dpy = BOX_SIZE * g->tan_ai[ix][g->pos.rot];
	if (ai * dpy > 0)
		dpy = -dpy;
	if (Bpy < 0 || Bpy >= g->map.ph)
	{
		g->pos.dB = INFINI;
		return ;
	}
	if (ai > -90.0 && ai < 90.0)
		Bx = Bpx / BOX_SIZE;
	else
		Bx = Bpx / BOX_SIZE - 1;
	By = Bpy / BOX_SIZE;
	door_coor = (int) (Bpy + dpy / 2 - BOX_SIZE * (float) By);
	while ((Bx >= 0 && Bx < g->map.l) && (By >= 0 && By < g->map.h) &&
			((g->map.v[By][Bx] != B_WALL && g->map.v[By][Bx] != B_DOOR)
			 || (By == g->opened_door_y && Bx == g->opened_door_x && g->map.v[By][Bx] == B_DOOR && door_coor < g->hidden_door)))
	{
		Bpx += dpx;
		Bpy += dpy;
		if (ai > -90.0 && ai < 90.0)
			Bx = Bpx / BOX_SIZE;
		else
			Bx = Bpx / BOX_SIZE - 1;
		By = Bpy / BOX_SIZE;
		door_coor = (int) (Bpy + dpy / 2 - BOX_SIZE * (float) By);
	}
	if (Bx < 0 || Bx >= g->map.l || By < 0 || By >= g->map.h)
	{
		g->pos.dB = INFINI;
		return ;
	}
	if (g->map.v[By][Bx] == B_DOOR && ai > -90.0 && ai < 90.0)
	{
		g->pos.dB = (Bpx - g->pos.px + BOX_SIZE / 2) / cos(ai * PI / 180);
		Bpy += dpy / 2;
	}
	else if (g->map.v[By][Bx] == B_DOOR)
	{
		g->pos.dB = (Bpx - g->pos.px - BOX_SIZE / 2) / cos(ai * PI / 180);
		Bpy += dpy / 2;
	}
	else
		g->pos.dB = (Bpx - g->pos.px) / g->cos_ai[ix][g->pos.rot];
	g->pos.Bx = Bx;
	g->pos.By = By;
	g->pos.Bpy = Bpy;
}

float	render_walls(t_game *g, int ix)
{
	float	ai;
	float	Apx;
	float	Apy;
	int	Ax;
	int	Ay;
	float	dpx;
	float	dpy;
	int	door_coor;

	g->pos.dA = 0.0;
	g->pos.dB = 0.0;
	ai = g->ai[ix][g->pos.rot];
	if ((-g->tol_l < ai && ai < g->tol_l) || (180.0 - g->tol_l < ai) || ai < -(180.0 - g->tol_l))
	{
		g->pos.dA = INFINI;
		get_B1(g, ix, ai);
	}
	else if ((90.0 - g->tol_h < ai && ai < 90.0 + g->tol_h) || (-90.0 - g->tol_h < ai && ai < -90.0 + g->tol_h))
	{
		if (ai > 90.0 - g->tol_h)
		{
			Apy = ((int) (g->pos.py / BOX_SIZE)) * BOX_SIZE;
			dpy = -BOX_SIZE;
		}
		else
		{
			Apy = ((int) (g->pos.py / BOX_SIZE)) * BOX_SIZE + BOX_SIZE;
			dpy = BOX_SIZE;
		}
		Apx = g->pos.px + (g->pos.py - Apy) * g->cos_ai[ix][g->pos.rot] / g->sin_ai[ix][g->pos.rot];
		dpx = BOX_SIZE * g->cos_ai[ix][g->pos.rot] / g->sin_ai[ix][g->pos.rot];
		if (ai < 0)
			dpx = -dpx;
		if (ai > 0.0)
			Ay = Apy / BOX_SIZE - 1;
		else
			Ay = Apy / BOX_SIZE;
		Ax = g->pos.x;
		door_coor = (int) (Apx + dpx / 2 - BOX_SIZE * (float) Ax);
		while ((g->map.v[Ay][Ax] != B_WALL && g->map.v[Ay][Ax] != B_DOOR)
				|| (Ay == g->opened_door_y && Ax == g->opened_door_x && g->map.v[Ay][Ax] == B_DOOR && door_coor < g->hidden_door))
		{
			Apx += dpx;
			Apy += dpy;
			if (ai > 0.0)
				Ay = Apy / BOX_SIZE - 1;
			else
				Ay = Apy / BOX_SIZE;
			door_coor = (int) (Apx + dpx / 2 - BOX_SIZE * (float) Ax);
		}
		if (g->map.v[Ay][Ax] == B_DOOR && ai > 0.0)
		{
			g->pos.dA = (g->pos.py - Apy + BOX_SIZE / 2) / sin(ai * PI / 180);
			Apx += dpx / 2;
		}
		else if (g->map.v[Ay][Ax] == B_DOOR)
		{
			g->pos.dA = (g->pos.py - Apy - BOX_SIZE / 2) / sin(ai * PI / 180);
			Apx += dpx / 2;
		}
		else
			g->pos.dA = (g->pos.py - Apy) / sin(ai * PI / 180);
		g->pos.dB = INFINI;
		g->pos.Ax = Ax;
		g->pos.Ay = Ay;
		g->pos.Apx = Apx;
	}
	else
	{
		// CHECKING HORIZONTAL INTERSECTIONS
		//Find A
		if (ai > 0.0)
		{
			Apy = ((int) (g->pos.py / BOX_SIZE)) * BOX_SIZE;
			dpy = -BOX_SIZE;
		}
		else
		{
			Apy = ((int) (g->pos.py / BOX_SIZE)) * BOX_SIZE + BOX_SIZE;
			dpy = BOX_SIZE;
		}
		Apx = g->pos.px + (g->pos.py - Apy) / g->tan_ai[ix][g->pos.rot];
		dpx = BOX_SIZE / g->tan_ai[ix][g->pos.rot];
		if (ai < 0)
			dpx = -dpx;
		if (Apx < 0 && Apx >= g->map.pl)
			g->pos.dA = INFINI;
		else
		{
			Ax = Apx / BOX_SIZE;
			if (ai > 0.0)
				Ay = Apy / BOX_SIZE - 1;
			else
				Ay = Apy / BOX_SIZE;
			door_coor = (int) (Apx + dpx / 2 - BOX_SIZE * (float) Ax);
			while ((Ax >= 0 && Ax < g->map.l) && (Ay >= 0 && Ay < g->map.h) &&
					((g->map.v[Ay][Ax] != B_WALL && g->map.v[Ay][Ax] != B_DOOR)
					 || (Ay == g->opened_door_y && Ax == g->opened_door_x && g->map.v[Ay][Ax] == B_DOOR && door_coor < g->hidden_door)))
			{
				Apx += dpx;
				Apy += dpy;
				Ax = Apx / BOX_SIZE;
				if (ai > 0.0)
					Ay = Apy / BOX_SIZE - 1;
				else
					Ay = Apy / BOX_SIZE;
				door_coor = (int) (Apx + dpx / 2 - BOX_SIZE * (float) Ax);
				//printf("Apx = %f, Ax = %d, Ay = %d\n", Apx, Ax, Ay);
			}
			if (Ax < 0 || Ax >= g->map.l || Ay < 0 || Ay >= g->map.h)
				g->pos.dA = INFINI;
			else
			{
				if (g->map.v[Ay][Ax] == B_DOOR && ai > 0.0)
				{
					g->pos.dA = (g->pos.py - Apy + BOX_SIZE / 2) / sin(ai * PI / 180);
					Apx += dpx / 2;
				}
				else if (g->map.v[Ay][Ax] == B_DOOR)
				{
					g->pos.dA = (g->pos.py - Apy - BOX_SIZE / 2) / sin(ai * PI / 180);
					Apx += dpx / 2;
				}
				else
					g->pos.dA = (g->pos.py - Apy) / g->sin_ai[ix][g->pos.rot];
				g->pos.Ax = Ax;
				g->pos.Ay = Ay;
				g->pos.Apx = Apx;
			}
		}
		//Find B
		get_B1(g, ix, ai);
	}
	return (render(g, ix));
}
