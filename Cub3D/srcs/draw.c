/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/20 13:59:01 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	create_trgb(unsigned char t, unsigned char r,
		unsigned char g, unsigned char b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
 
void	draw_wall(t_game *g)
{
	printf("draw wall\n");
	int	ix;
	int	Xp;
	double	ai;
	double	ai0;
	double	Apx;
	double	Apy;
	int	Ax;
	int	Ay;
	double	Bpx;
	double	Bpy;
	int	Bx;
	int	By;
	double	dpx;
	double	dpy;
	double	dA;
	double	dB;
	double	d;
	double	tol_h;
	double	tol_l;

	// Angle tolerance 10 pixel / size
	tol_h= 10.0 / (double) g->map.h / BOX_SIZE;
	tol_l = 10.0 / (double) g->map.l / BOX_SIZE;
	printf("tol_h = %f, tol_l = %f\n", tol_h, tol_l);
	g->pos.alpha = 160;
	int	deli = 0;
	ix = WIDTH / 2 - 1 + deli;
	while (++ix < WIDTH / 2 + 1 + deli)
	{
		dA = 0.0;
		dB = 0.0;
		Xp = WIDTH / 2 - ix;
		printf("Xp = %d\n", Xp);
		ai0 = atan((double) Xp / g->dpp) * 180 / PI; 
		printf("ai0 = %f\n", ai0);
		ai = g->pos.alpha + ai0;
		printf("1 - ai = %f\n", ai);
		ai = angle_convert(ai);
		printf("2 - ai = %f\n", ai);
		//if (ai == 0.0 || 180.0)
		if ((-tol_l < ai && ai < tol_l) || (180.0 - tol_l < ai) || ai < -(180.0 - tol_l))
		{
			if (ai < tol_l && ai > -tol_l)
			{
				Bpx = (g->pos.px / BOX_SIZE) * BOX_SIZE + BOX_SIZE;
				dpx = BOX_SIZE;
			}
			else
			{
				Bpx = (g->pos.px / BOX_SIZE) * BOX_SIZE - 1;
				dpx = -BOX_SIZE;
			}
			Bpy = g->pos.py + (g->pos.px - Bpx) * tan(ai * PI / 180.0);
			dpy = BOX_SIZE * tan(ai * PI / 180.0);
			if (ai * dpy > 0)
				dpy = -dpy;
			printf("First Bpy = %f, dpy = %.20e\n", Bpy, dpy);
			Bx = Bpx / BOX_SIZE;
			By = g->pos.y;
			while (!g->map.v[By][Bx])
			{
				Bpx += dpx;
				Bpy += dpy;
				Bx = Bpx / BOX_SIZE;
			}
			dA = INFINI;
			dB = (Bpx - g->pos.px) / cos(ai * PI / 180);
			printf("v = %d, px = %f, Bpx = %f, x = %d, Bx = %d, dB = %f\n", g->map.v[By][Bx], g->pos.px, Bpx, g->pos.x, Bx, dB);
			printf("v = %d, py = %f, Bpy = %f, y = %d, By = %d, dB = %f\n", g->map.v[By][Bx], g->pos.py, Bpy, g->pos.y, By, dB);
		}
		//else if (ai == 90.0)
		else if ((90.0 - tol_h < ai && ai < 90.0 + tol_h) || (-90.0 - tol_h < ai && ai < -90.0 + tol_h))
		{
			if (ai > 90.0 - tol_h)
			{
				Apy = (g->pos.py / BOX_SIZE) * BOX_SIZE - 1;
				dpy = -BOX_SIZE;
			}
			else
			{
				Apy = (g->pos.py / BOX_SIZE) * BOX_SIZE + BOX_SIZE;
				dpy = BOX_SIZE;
			}
			Apx = g->pos.px + (g->pos.py - Apy) * cos(ai * PI / 180.0) / sin(ai * PI / 180.0);
			dpx = BOX_SIZE * cos(ai * PI / 180.0) / sin(ai * PI / 180.0);
			if (ai < 0)
				dpx = -dpx;
			printf("First Apx = %f, dpx = %.20e\n", Apx, dpx);
			Ay = Apy / BOX_SIZE;
			Ax = g->pos.x;
			while (!g->map.v[Ay][Ax])
			{
				Apx += dpx;
				Apy += dpy;
				Ay = Apy / BOX_SIZE;
			}
			dA = (g->pos.py - Apy) / sin(ai * PI / 180);
			dB = INFINI;
			printf("v = %d, px = %f, Apx = %f, x = %d, Ax = %d, dA = %f\n", g->map.v[Ay][Ax], g->pos.px, Apx, g->pos.x, Ax, dA);
			printf("v = %d, py = %f, Apy = %f, y = %d, Ay = %d, dA = %f\n", g->map.v[Ay][Ax], g->pos.py, Apy, g->pos.y, Ay, dA);
		}
		else
		{
			// CHECKING HORIZONTAL INTERSECTIONS
			//Find A
			if (ai > 0.0 && ai < 180.0)
			{
				Apy = (g->pos.py / BOX_SIZE) * BOX_SIZE - 1;
				dpy = -BOX_SIZE;
			}
			else
			{
				Apy = (g->pos.py / BOX_SIZE) * BOX_SIZE + BOX_SIZE;
				dpy = BOX_SIZE;
			}
			Apx = g->pos.px + (g->pos.py - Apy) / tan(ai * PI / 180.0);
			dpx = BOX_SIZE / tan(ai * PI / 180.0);
			if (ai < 0)
				dpx = -dpx;
			printf("First Apx = %f, dpx = %.20e\n", Apx, dpx);
			Ax = Apx / BOX_SIZE;
			Ay = Apy / BOX_SIZE;
			if (!(Ax >= 0 && Ax <= g->map.l - 1))
				dA = INFINI;
			while (Ax >= 0 && Ax <= g->map.l - 1 && !g->map.v[Ay][Ax])
			{
				Apx += dpx;
				Apy += dpy;
				Ax = Apx / BOX_SIZE;
				Ay = Apy / BOX_SIZE;
			}
			if (Ax < 0 || Ax > g->map.l - 1)
			{
				Apx -= dpx;
				Apy -= dpy;
				Ax = Apx / BOX_SIZE;
				Ay = Apy / BOX_SIZE;
			}
			dA = (g->pos.py - Apy) / sin(ai * PI / 180);
			printf("v = %d, px = %f, Apx = %f, x = %d, Ax = %d, dA = %f\n", g->map.v[Ay][Ax], g->pos.px, Apx, g->pos.x, Ax, dA);
			printf("v = %d, py = %f, Apy = %f, y = %d, Ay = %d, dA = %f\n", g->map.v[Ay][Ax], g->pos.py, Apy, g->pos.y, Ay, dA);
		}
		//Find C
		//alpha = 
	}
}

void	draw_map(t_game *g)
{
	printf("draw map\n");
	int	i = -1;
	int	j = -1;

	while (++i < g->map.h)
	{
		j = -1;
		while (++j < g->map.l)
			if (i == g->pos.y && j == g->pos.x)
				printf("x");
			else
				printf("%d", g->map.v[i][j]);
		printf("\n");
	}
}

void	draw(t_game *g)
{
	int	xp;
	int	yp;
	int	*addr;

	//addr = (int *)g->mlx.addr;
	//yp = -1;
	//while (++yp < HEIGHT)
	//{
	//	xp = -1;
	//	while (++xp < WIDTH)
	//		*(addr++) = create_trgb(1, 255, 0, 0);
	//}
	//mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->mlx.img, 0, 0);

	draw_wall(g);
	draw_map(g);
	draw_mini_map(g);
	end_game(g, 0, 0);
	//printf("g.h = %d, g.l = %d, g.x = %d, g.y = %d, g.dx = %d, g.dy = %d\n", g.h , g.l , g.x , g.y , g.dx , g.dy);
}
