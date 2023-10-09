/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_box.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/09 06:31:59 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	*render_ceiling(t_game *g, int ix, int start)
{
	int		yp;
	int		*addr;
	int		*addr_c;
	t_render	r;

	addr = (int *)g->mlx.addr + ix;
	addr_c = (int *)g->tex[CL].addr;
	yp = -1;
	while (++yp < start)
	{
		if (g->cl_color)
			*addr = g->cl_color;
		else
		{
			r.dh = g->dpp * BOX_SIZE / 2 / (HEIGHT / 2 - yp) * g->cos_ai0[ix];
			r.xph = g->pos.px + r.dh * g->cos_ai[ix][g->pos.rot];
			r.yph = g->pos.py - r.dh * g->sin_ai[ix][g->pos.rot];
			r.xh = (int) (r.xph - ((int) (r.xph / BOX_SIZE)) * BOX_SIZE);
			r.yh = (int) (r.yph - ((int) (r.yph / BOX_SIZE)) * BOX_SIZE);
			if (r.xh < BOX_SIZE && r.xh >= 0 && r.yh < BOX_SIZE && r.yh >= 0)
				*addr = *(addr_c + r.xh + r.yh * g->tex[CL].l);
		}
		addr += WIDTH;
	}
	return (addr);
}

static void	render_floor(t_game *g, int ix, int yp, int *addr)
{
	float	dh;
	int	xh;
	int	yh;
	float	xph;
	float	yph;
	int	*addr_f;

	addr_f = (int *)g->tex[FL].addr;
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
}

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
	addr = render_ceiling(g, ix, start);
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
	render_floor(g, ix, start + h_slide - 1, addr);
	return (d);
}

float	render_box(t_game *g, int ix)
{
	float	ai;

	g->pos.dA = 0.0;
	g->pos.dB = 0.0;
	ai = g->ai[ix][g->pos.rot];
	if ((-g->tol_l < ai && ai < g->tol_l) ||
		(180.0 - g->tol_l < ai) || ai < -(180.0 - g->tol_l))
	{
		g->pos.dA = INFINI;
		get_B(g, ix, ai);
	}
	else if ((90.0 - g->tol_h < ai && ai < 90.0 + g->tol_h) ||
		(-90.0 - g->tol_h < ai && ai < -90.0 + g->tol_h))
	{
		g->pos.dB = INFINI;
		get_A(g, ix, ai);
	}
	else
	{
		get_A(g, ix, ai);
		get_B(g, ix, ai);
	}
	return (render(g, ix));
}
