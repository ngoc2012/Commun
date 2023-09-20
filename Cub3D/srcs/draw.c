/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/20 08:49:04 by minh-ngu         ###   ########.fr       */
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
	int	Apx;
	int	Apy;
	int	Ax;
	int	Ay;
	int	Bpx;
	int	Bpy;
	int	Bx;
	int	By;
	double	dpx;
	double	dpy;
	double	dA;
	double	dB;
	double	d;
	double	tol;

	if (g->map.h > g->map.l)
		tol = 1.0 / (double) g->map.h;
	else
		tol = 1.0 / (double) g->map.l;
	g->pos.alpha = 0;
	ix = WIDTH / 2 - 1;
	while (++ix < WIDTH / 2 + 1)
	{
		dA = 0.0;
		dB = 0.0;
		Xp = WIDTH / 2 - ix;
		printf("Xp = %d\n", Xp);
		ai0 = atan((double) Xp / g->dpp) * 180 / PI; 
		printf("ai0 = %f\n", ai0);
		ai = g->pos.alpha + ai0;
		printf("1 - ai = %f\n", ai );
		ai = angle_convert(ai);
		printf("2 - ai = %f\n", ai );
		//if (ai == 0.0)
		if (-tol < ai && ai < tol)
		{
			Bpx = (g->pos.px / BOX_SIZE) * BOX_SIZE + BOX_SIZE;
			Bpy = g->pos.py + (Bpx - g->pos.px) * tan(ai * PI / 180.0);
			dpx = BOX_SIZE;
			dpy = BOX_SIZE * tan(ai * PI / 180.0);
			Bx = Bpx / BOX_SIZE;
			By = g->pos.y;
			while (!g->map.v[By][Bx])
			{
				Bpx += dpx;
				Bpy += dpy;
				Bx = Bpx / BOX_SIZE;
			}
			dA = INFINI;
			dB = Bpx - g->pos.px;
			printf("v = %d, px = %d, Bpx = %d, x = %d, Bx = %d, dB = %f\n", g->map.v[By][Bx], g->pos.px, Bpx, g->pos.x, Bx, dB);
			printf("v = %d, py = %d, Bpy = %d, y = %d, By = %d, dB = %f\n", g->map.v[By][Bx], g->pos.py, Bpy, g->pos.y, By, dB);
		}
		//else if (ai == 180.0)
		else if (180.0 - tol < ai && ai < 180.0 + tol)
		{
			Bpx = (g->pos.px / BOX_SIZE) * BOX_SIZE - 1;
			//Bpy = g->pos.py;
			dpx = -BOX_SIZE;
			//dpy = 0;
			dA = INFINI;
			Bx = Bpx / BOX_SIZE;
			while (!g->map.v[g->pos.y][Bx])
			{
				Bpx += dpx;
				Bx = Bpx / BOX_SIZE;
			}
			dB = -Bpx + g->pos.px;
			d = dB;
			printf("v = %d, px = %d, Bpx = %d, x = %d, Bx = %d, dB = %f\n", g->map.v[g->pos.y][Bx], g->pos.px, Bpx, g->pos.x, Bx, dB);
		}
		//else if (ai == 90.0)
		else if (90.0 - tol < ai && ai < 90.0 + tol)
		{
			//Apx = g->pos.px;
			Apy = (g->pos.py / BOX_SIZE) * BOX_SIZE - 1;
			//dpx = 0;
			dpy = -BOX_SIZE;
			dB = INFINI;
		}
		//else if (ai == -90.0)
		else if (-90.0 - tol < ai && ai < -90.0 + tol)
		{
			Apx = g->pos.px;
			Apy = (g->pos.py / BOX_SIZE) * BOX_SIZE + BOX_SIZE;
			dpx = 0;
			dpy = BOX_SIZE;
		}
		else
		{
			// CHECKING HORIZONTAL INTERSECTIONS
			//Find A
			if (ai > 0.0 && ai < 180.0)
			{
				Apy = (g->pos.py / BOX_SIZE) * BOX_SIZE - 1;
				dpy = -BOX_SIZE;
				dpx = BOX_SIZE / tan(ai * PI / 180.0);
			}
			else
			{
				Apy = (g->pos.py / BOX_SIZE) * BOX_SIZE + BOX_SIZE;
				dpy = BOX_SIZE;
				dpx = -BOX_SIZE / tan(ai * PI / 180.0);
			}
			Apx = g->pos.px + (g->pos.py - Apy) / tan(ai * PI / 180.0);
			Ax = Apx / BOX_SIZE;
			Ay = Apy / BOX_SIZE;
			if (Ax >= 0 && Ax <= g->map.l - 1)
			{
				printf("px = %d, Apx = %d, x = %d, Ax = %d\n", g->pos.px, Apx, g->pos.x, Ax);
				printf("py = %d, Apy = %d, y = %d, Ay = %d\n", g->pos.py, Apy, g->pos.y, Ay);
				while (!g->map.v[Ay][Ax])
				{
					Apy += dpy;
					Apx += dpx;
					Ax = Apx / BOX_SIZE;
					Ay = Apy / BOX_SIZE;
					printf("px = %d, Apx = %d, x = %d, Ax = %d\n", g->pos.px, Apx, g->pos.x, Ax);
					printf("py = %d, Apy = %d, y = %d, Ay = %d\n", g->pos.py, Apy, g->pos.y, Ay);
				}
				//dA = (g->pos.y - Apy) / sin(ai * PI / 180.0);
				dA = g->pos.y - Apy;
				printf("value = %d, dA = %f\n", g->map.v[Ay][Ax], dA);
			}
			else
				dA = INFINI;
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
