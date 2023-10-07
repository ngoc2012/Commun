/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/07 12:24:33 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	render_walls(t_game *g, int ix)
{
	float	ai;
	float	Apx;
	float	Apy;
	int	Ax;
	int	Ay;
	float	Bpx;
	float	Bpy;
	int	Bx;
	int	By;
	float	dpx;
	float	dpy;
	float	dA;
	float	dB;
	int	*addr;
	int	*addr_t;
	int	*addr_f;
	int	*addr_c;
	int	door_coor;
	float	d;
	t_tex	*tex;

	addr_f = (int *)g->tex[FL].addr;
	addr_c = (int *)g->tex[CL].addr;
	dA = 0.0;
	dB = 0.0;
	d = INFINI;
	ai = g->ai[ix][g->pos.rot];
	if ((-g->tol_l < ai && ai < g->tol_l) || (180.0 - g->tol_l < ai) || ai < -(180.0 - g->tol_l))
	{
		if (ai < g->tol_l && ai > -g->tol_l)
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
		if (ai < g->tol_l && ai > -g->tol_l)
			Bx = Bpx / BOX_SIZE;
		else
			Bx = Bpx / BOX_SIZE - 1;
		By = g->pos.y;
		door_coor = (int) (Bpy + dpy / 2 - BOX_SIZE * (float) By);
		while ((g->map.v[By][Bx] != B_WALL && g->map.v[By][Bx] != B_DOOR)
				|| (By == g->opened_door_y && Bx == g->opened_door_x && g->map.v[By][Bx] == B_DOOR && door_coor < g->hidden_door))
		{
			Bpx += dpx;
			Bpy += dpy;
			if (ai < g->tol_l && ai > -g->tol_l)
				Bx = Bpx / BOX_SIZE;
			else
				Bx = Bpx / BOX_SIZE - 1;
			if (g->map.v[By][Bx] == B_DOOR)
				door_coor = (int) (Bpy + dpy / 2 - BOX_SIZE * (float) By);
		}
		dA = INFINI;
		if (g->map.v[By][Bx] == B_DOOR && ai < g->tol_l && ai > -g->tol_l)
		{
			dB = (Bpx - g->pos.px + BOX_SIZE / 2) / cos(ai * PI / 180);
			Bpy += dpy / 2;
		}
		else if (g->map.v[By][Bx] == B_DOOR)
		{
			dB = (Bpx - g->pos.px - BOX_SIZE / 2) / cos(ai * PI / 180);
			Bpy += dpy / 2;
		}
		else
			dB = (Bpx - g->pos.px) / cos(ai * PI / 180);
		g->pos.Bx = Bx;
		g->pos.By = By;
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
			dA = (g->pos.py - Apy + BOX_SIZE / 2) / sin(ai * PI / 180);
			Apx += dpx / 2;
		}
		else if (g->map.v[Ay][Ax] == B_DOOR)
		{
			dA = (g->pos.py - Apy - BOX_SIZE / 2) / sin(ai * PI / 180);
			Apx += dpx / 2;
		}
		else
			dA = (g->pos.py - Apy) / sin(ai * PI / 180);
		dB = INFINI;
		g->pos.Ax = Ax;
		g->pos.Ay = Ay;
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
			dA = INFINI;
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
				dA = INFINI;
			else
			{
				if (g->map.v[Ay][Ax] == B_DOOR && ai > 0.0)
				{
					dA = (g->pos.py - Apy + BOX_SIZE / 2) / sin(ai * PI / 180);
					Apx += dpx / 2;
				}
				else if (g->map.v[Ay][Ax] == B_DOOR)
				{
					dA = (g->pos.py - Apy - BOX_SIZE / 2) / sin(ai * PI / 180);
					Apx += dpx / 2;
				}
				else
					dA = (g->pos.py - Apy) / g->sin_ai[ix][g->pos.rot];
				g->pos.Ax = Ax;
				g->pos.Ay = Ay;
			}
		}
		//Find B
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
			dB = INFINI;
		else
		{
			if (ai > -90.0 && ai < 90.0)
				Bx = Bpx / BOX_SIZE;
			else
				Bx = Bpx / BOX_SIZE - 1;
			By = Bpy / BOX_SIZE;
			door_coor = (int) (Bpy + dpy / 2 - BOX_SIZE * (float) By);
			//while ((Bpy >= 0 && Bpy < g->map.ph) &&
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
			//if (Bpy < 0 || Bpy >= g->map.ph)
			if (Bx < 0 || Bx >= g->map.l || By < 0 || By >= g->map.h)
				dB = INFINI;
			else
			{
				if (g->map.v[By][Bx] == B_DOOR && ai > -90.0 && ai < 90.0)
				{
					dB = (Bpx - g->pos.px + BOX_SIZE / 2) / cos(ai * PI / 180);
					Bpy += dpy / 2;
				}
				else if (g->map.v[By][Bx] == B_DOOR)
				{
					dB = (Bpx - g->pos.px - BOX_SIZE / 2) / cos(ai * PI / 180);
					Bpy += dpy / 2;
				}
				else
					dB = (Bpx - g->pos.px) / g->cos_ai[ix][g->pos.rot];
				g->pos.Bx = Bx;
				g->pos.By = By;
			}
		}
	}
	int	tx;
	int	ty;
	int	h_slide;
	float	h;
	float	p;
	if (dA > dB)
	{
		d = dB / g->cos_ai0[ix];
		tx = (int) (Bpy - BOX_SIZE * (float) By);
		if (g->map.v[By][Bx] == B_DOOR)
		{
			if (By == g->opened_door_y && Bx == g->opened_door_x)
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
		d = dA / g->cos_ai0[ix];
		tx = (int) (Apx - BOX_SIZE * (float) Ax);
		if (g->map.v[Ay][Ax] == B_DOOR)
		{
			if (Ay == g->opened_door_y && Ax == g->opened_door_x)
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
