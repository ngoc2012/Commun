/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/22 10:05:28 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	create_trgb(unsigned char t, unsigned char r,
		unsigned char g, unsigned char b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	redraw(t_game *g)
{
	int	xp;
	int	yp;
	int	*addr;

	addr = (int *)g->mlx.addr;
	yp = -1;
	while (++yp < HEIGHT)
	{
		xp = -1;
		while (++xp < WIDTH)
			*(addr++) = 0;
	}
}
 
void	draw_wall(t_game *g)
{
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
	double	tol_h;
	double	tol_l;
	int	*addr;
	int	*addr_t;

	g->pos.Ax = -1;
	g->pos.Ay = -1;
	g->pos.Bx = -1;
	g->pos.By = -1;
	// Angle tolerance 1 pixel / size
	tol_h= 1.0 / (double) g->map.h / BOX_SIZE;
	tol_l = 1.0 / (double) g->map.l / BOX_SIZE;
	ix = -1;
	while (++ix < WIDTH)
	{
		dA = 0.0;
		dB = 0.0;
		Xp = WIDTH / 2 - ix;
		ai0 = atan((double) Xp / g->dpp) * 180 / PI; 
		ai = g->pos.alpha + ai0;
		ai = angle_convert(ai);
		if ((-tol_l < ai && ai < tol_l) || (180.0 - tol_l < ai) || ai < -(180.0 - tol_l))
		{
			if (ai < tol_l && ai > -tol_l)
			{
				Bpx = ((int) (g->pos.px / BOX_SIZE)) * BOX_SIZE + BOX_SIZE;
				dpx = BOX_SIZE;
			}
			else
			{
				Bpx = ((int) (g->pos.px / BOX_SIZE)) * BOX_SIZE - 1;
				dpx = -BOX_SIZE;
			}
			Bpy = g->pos.py + (g->pos.px - Bpx) * tan(ai * PI / 180.0);
			dpy = BOX_SIZE * tan(ai * PI / 180.0);
			if (ai * dpy > 0)
				dpy = -dpy;
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
			g->pos.Bx = Bx;
			g->pos.By = By;
		}
		//else if (ai == 90.0)
		else if ((90.0 - tol_h < ai && ai < 90.0 + tol_h) || (-90.0 - tol_h < ai && ai < -90.0 + tol_h))
		{
			if (ai > 90.0 - tol_h)
			{
				Apy = ((int) (g->pos.py / BOX_SIZE)) * BOX_SIZE - 1;
				dpy = -BOX_SIZE;
			}
			else
			{
				Apy = ((int) (g->pos.py / BOX_SIZE)) * BOX_SIZE + BOX_SIZE;
				dpy = BOX_SIZE;
			}
			Apx = g->pos.px + (g->pos.py - Apy) * cos(ai * PI / 180.0) / sin(ai * PI / 180.0);
			dpx = BOX_SIZE * cos(ai * PI / 180.0) / sin(ai * PI / 180.0);
			if (ai < 0)
				dpx = -dpx;
			//printf("First Apx = %f, dpx = %.20e\n", Apx, dpx);
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
			g->pos.Ax = Ax;
			g->pos.Ay = Ay;
		}
		else
		{
			// CHECKING HORIZONTAL INTERSECTIONS
			//Find A
			if (ai > 0.0)
			{
				Apy = ((int) (g->pos.py / BOX_SIZE)) * BOX_SIZE - 1;
				dpy = -BOX_SIZE;
			}
			else
			{
				Apy = ((int) (g->pos.py / BOX_SIZE)) * BOX_SIZE + BOX_SIZE;
				dpy = BOX_SIZE;
			}
			Apx = g->pos.px + (g->pos.py - Apy) / tan(ai * PI / 180.0);
			dpx = BOX_SIZE / tan(ai * PI / 180.0);
			if (ai < 0)
				dpx = -dpx;
			//printf("First Apx = %f, dpx = %.20e\n", Apx, dpx);
			if (Apx < 0 && Apx >= g->map.pl)
				dA = INFINI;
			else
			{
				Ax = Apx / BOX_SIZE;
				Ay = Apy / BOX_SIZE;
				while (Apx >= 0 && Apx < g->map.pl && !g->map.v[Ay][Ax])
				{
					Apx += dpx;
					Apy += dpy;
					Ax = Apx / BOX_SIZE;
					Ay = Apy / BOX_SIZE;
				}
				if (Apx < 0 || Apx >= g->map.pl)
					dA = INFINI;
				else
				{
					dA = (g->pos.py - Apy) / sin(ai * PI / 180);
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
				Bpx = ((int) (g->pos.px / BOX_SIZE)) * BOX_SIZE - 1;
				dpx = -BOX_SIZE;
			}
			Bpy = g->pos.py + (g->pos.px - Bpx) * tan(ai * PI / 180.0);
			dpy = BOX_SIZE * tan(ai * PI / 180.0);
			if (ai * dpy > 0)
				dpy = -dpy;
			if (Bpy < 0 || Bpy >= g->map.ph)
				dB = INFINI;
			else
			{
				Bx = Bpx / BOX_SIZE;
				By = Bpy / BOX_SIZE;
				while (Bpy >= 0 && Bpy < g->map.ph && !g->map.v[By][Bx])
				{
					Bpx += dpx;
					Bpy += dpy;
					Bx = Bpx / BOX_SIZE;
					By = Bpy / BOX_SIZE;
				}
				if (Bpy < 0 || Bpy >= g->map.ph)
					dB = INFINI;
				else
				{
					dB = (Bpx - g->pos.px) / cos(ai * PI / 180.0);
					g->pos.Bx = Bx;
					g->pos.By = By;
				}
			}
		}
		int	x;
		int	y;
		int	tx;
		int	ty;
		int	h_slide;
		double	h;
		double	p;
		double	d;
		if (dA > dB)
		{
			d = dB * cos(ai0 * PI / 180.0);
			x = Bx;
			y = By;
			tx = (int) (Bpy - BOX_SIZE * (double) By);
		}
		else
		{
			d = dA * cos(ai0 * PI / 180.0);
			x = Ax;
			y = Ay;
			tx = (int) (Apx - BOX_SIZE * (double) Ax);
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
		addr_t = (int *)g->tex_n.addr;
		addr += ix;
		int	start = HEIGHT / 2 - h_slide / 2;
		addr += start * WIDTH;
		yp = -1;
		while (++yp < h_slide)
		{
			ty = (int) (((h - (double) h_slide) / 2.0 + (double) yp) / p);
			if (ty > BOX_SIZE - 1)
				printf("ty = %d\n", ty);
			//*addr = g->tex_n + tx + BOX_SIZE * ty;
			*addr = *(addr_t + tx + ty * g->tex_n.l);
			//if (g->map.v[y][x] == 1)
			//	*addr = create_trgb(1, 255, 0, 0);
			//if (g->map.v[y][x] == 2)
			//	*addr = create_trgb(1, 0, 255, 0);
			//if (g->map.v[y][x] == 3)
			//	*addr = create_trgb(1, 0, 0, 255);
			//if (g->map.v[y][x] == 4)
			//	*addr = create_trgb(1, 255, 255, 0);
			//if (g->map.v[y][x] == 5)
			//	*addr = create_trgb(1, 0, 255, 255);
			//if (g->map.v[y][x] == 6)
			//	*addr = create_trgb(1, 255, 0, 255);
			//if (g->map.v[y][x] == 7)
			//	*addr = create_trgb(1, 255, 255, 255);
			addr += WIDTH;
		}
	}
	//int	i = -1;
	//int	j = -1;

	//int	*addr_t;
	////printf("h = %d, l = %d\n", g->tex_n.h, g->tex_n.l);
	//addr = (int *)g->mlx.addr;
	//addr_t = (int *)g->tex_n.addr;
	//while (++i < g->tex_n.h)
	//{
	//	j = -1;
	//	while (++j < g->tex_n.l)
	//	{
	//		//*(addr + i + WIDTH * j) = *(addr_t + i * g->tex_n.bpp / 8 + g->tex_n.ll*j);
	//		*(addr + i + WIDTH * j) = *(addr_t + i + j * g->tex_n.l);
	//		//*addr = *((int *) (g->tex_n + i + BOX_SIZE * j));
	//	}
	//}
	mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->mlx.img, 0, 0);
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
		{
			if (i == g->pos.y && j == g->pos.x)
				printf(COLOR_BOLD_SLOW_BLINKING_RED "x" COLOR_OFF);
			else if (i == g->pos.Ay && j == g->pos.Ax && i == g->pos.By && j == g->pos.Bx)
				printf(COLOR_BOLD_SLOW_BLINKING_CYAN "%d" COLOR_OFF, g->map.v[i][j]);
			else if (i == g->pos.Ay && j == g->pos.Ax)
				printf(COLOR_BOLD_SLOW_BLINKING_BLUE "%d" COLOR_OFF, g->map.v[i][j]);
			else if (i == g->pos.By && j == g->pos.Bx)
				printf(COLOR_BOLD_SLOW_BLINKING_GREEN "%d" COLOR_OFF, g->map.v[i][j]);
			else
				printf("%d", g->map.v[i][j]);
			printf(" ");
		}
		printf("\n");
	}
}

void	draw(t_game *g)
{
	/*
	int	xp;
	int	yp;
	int	*addr;

	addr = (int *)g->mlx.addr;
	addr += 200;
	addr += 50 * WIDTH;
	yp = -1;
	while (++yp < 100)
	{
		*addr = create_trgb(1, 255, 0, 0);
		addr += WIDTH;
		//xp = -1;
		//while (++xp < WIDTH)
		//	*(addr++) = create_trgb(1, 255, 0, 0);
	}
	mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->mlx.img, 0, 0);
	*/

	draw_wall(g);
	//draw_map(g);
	draw_mini_map(g);
	//end_game(g, 0, 0);
	//printf("g.h = %d, g.l = %d, g.x = %d, g.y = %d, g.dx = %d, g.dy = %d\n", g.h , g.l , g.x , g.y , g.dx , g.dy);
}
