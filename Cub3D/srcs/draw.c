/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/21 12:14:01 by ngoc             ###   ########.fr       */
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
	//mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->mlx.img, 0, 0);
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
	double	tol_h;
	double	tol_l;

	g->pos.Ax = -1;
	g->pos.Ay = -1;
	g->pos.Bx = -1;
	g->pos.By = -1;
	// Angle tolerance 1 pixel / size
	tol_h= 1.0 / (double) g->map.h / BOX_SIZE;
	tol_l = 1.0 / (double) g->map.l / BOX_SIZE;
	//printf("tol_h = %f, tol_l = %f\n", tol_h, tol_l);
	//g->pos.alpha = 135;
	int	deli = 0;
	//ix = WIDTH / 2 - 1 + deli;
	//while (++ix < WIDTH / 2 + 1 + deli)
	ix = -1;
	while (++ix < WIDTH)
	{
		dA = 0.0;
		dB = 0.0;
		Xp = WIDTH / 2 - ix;
		//printf("Xp = %d\n", Xp);
		ai0 = atan((double) Xp / g->dpp) * 180 / PI; 
		//printf("ai0 = %f\n", ai0);
		ai = g->pos.alpha + ai0;
		//printf("1 - ai = %f\n", ai);
		ai = angle_convert(ai);
		//printf("2 - ai = %f\n", ai);
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
			//printf("First Bpy = %f, dpy = %.20e\n", Bpy, dpy);
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
			//printf("v = %d, px = %f, Bpx = %f, x = %d, Bx = %d, dB = %f\n", g->map.v[By][Bx], g->pos.px, Bpx, g->pos.x, Bx, dB);
			//printf("v = %d, py = %f, Bpy = %f, y = %d, By = %d, dB = %f\n", g->map.v[By][Bx], g->pos.py, Bpy, g->pos.y, By, dB);
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
			//printf("v = %d, px = %f, Apx = %f, x = %d, Ax = %d, dA = %f\n", g->map.v[Ay][Ax], g->pos.px, Apx, g->pos.x, Ax, dA);
			//printf("v = %d, py = %f, Apy = %f, y = %d, Ay = %d, dA = %f\n", g->map.v[Ay][Ax], g->pos.py, Apy, g->pos.y, Ay, dA);
		}
		else
		{
			// CHECKING HORIZONTAL INTERSECTIONS
			//Find A
			if (ai > 0.0)
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
					//printf("v = %d, px = %f, Apx = %f, x = %d, Ax = %d, dA = %f\n", g->map.v[Ay][Ax], g->pos.px, Apx, g->pos.x, Ax, dA);
					//printf("v = %d, py = %f, Apy = %f, y = %d, Ay = %d, dA = %f\n", g->map.v[Ay][Ax], g->pos.py, Apy, g->pos.y, Ay, dA);
				}
			}
			//Find B
			if (ai > -90.0 && ai < 90.0)
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
			//printf("First Bpy = %f, dpy = %.20e, ph = %d\n", Bpy, dpy, g->map.ph);
			if (Bpy < 0 || Bpy >= g->map.ph)
				dB = INFINI;
			else
			{
				Bx = Bpx / BOX_SIZE;
				By = Bpy / BOX_SIZE;
				while (Bpy >= 0 && Bpy < g->map.ph && !g->map.v[By][Bx])
				{
					//printf("Bpy = %f, By = %d, Bx = %d, v = %d\n", Bpy, By, Bx, g->map.v[By][Bx]);
					Bpx += dpx;
					Bpy += dpy;
					Bx = Bpx / BOX_SIZE;
					By = Bpy / BOX_SIZE;
				}
				//printf("Second Bpy = %f, dpy = %.20e, ph = %d\n", Bpy, dpy, g->map.ph);
				if (Bpy < 0 || Bpy >= g->map.ph)
					dB = INFINI;
				else
				{
					dB = (Bpx - g->pos.px) / cos(ai * PI / 180.0);
					g->pos.Bx = Bx;
					g->pos.By = By;
					//printf("v = %d, px = %f, Bpx = %f, x = %d, Bx = %d, dB = %f\n", g->map.v[By][Bx], g->pos.px, Bpx, g->pos.x, Bx, dB);
					//printf("v = %d, py = %f, Bpy = %f, y = %d, By = %d, dB = %f\n", g->map.v[By][Bx], g->pos.py, Bpy, g->pos.y, By, dB);
				}
			}
		}
		int	x;
		int	y;
		int	h_slide;
		double	d;
		if (dA > dB)
		{
			d = dB * cos(ai0 * PI / 180.0);
			x = Bx;
			y = By;
		}
		else
		{
			d = dA * cos(ai0 * PI / 180.0);
			x = Ax;
			y = Ay;
		}
		if (d < 0)
			d = -d;
		h_slide = (int) (BOX_SIZE / d * g->dpp);
		if (h_slide > HEIGHT)
			h_slide = HEIGHT;
		int	xp;
		int	yp;
		int	*addr;
		addr = (int *)g->mlx.addr;
		addr += ix;
		int	start = HEIGHT / 2 - (int) h_slide / 2;
		int	end = HEIGHT / 2 + (int) h_slide / 2;
		//printf("%d dA = %f, dB = %f, d = %f, h_slide = %d, start = %d, end = %d\n", ix, dA, dB, d, h_slide, start, end);
		addr += start * WIDTH;
		yp = -1;
		while (++yp < end - start)
		{
			if (g->map.v[y][x] == 1)
				*addr = create_trgb(1, 255, 0, 0);
			if (g->map.v[y][x] == 2)
				*addr = create_trgb(1, 0, 255, 0);
			if (g->map.v[y][x] == 3)
				*addr = create_trgb(1, 0, 0, 255);
			if (g->map.v[y][x] == 4)
				*addr = create_trgb(1, 255, 255, 0);
			if (g->map.v[y][x] == 5)
				*addr = create_trgb(1, 0, 255, 255);
			if (g->map.v[y][x] == 6)
				*addr = create_trgb(1, 255, 0, 255);
			if (g->map.v[y][x] == 7)
				*addr = create_trgb(1, 255, 255, 255);
			addr += WIDTH;
		}
		mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->mlx.img, 0, 0);
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
		{
			if (i == g->pos.y && j == g->pos.x)
				printf(COLOR_BOLD_SLOW_BLINKING_RED "x" COLOR_OFF);
			else if (i == g->pos.Ay && j == g->pos.Ax && i == g->pos.By && j == g->pos.Bx)
				printf(COLOR_BOLD_SLOW_BLINKING_CYAN "%d" COLOR_OFF, g->map.v[i][j]);
			else if (i == g->pos.Ay && j == g->pos.Ax)
				printf(COLOR_BOLD_SLOW_BLINKING_BLUE "%d" COLOR_OFF, g->map.v[i][j]);
				//printf(COLOR_BOLD_SLOW_BLINKING_BLUE "A" COLOR_OFF);
			else if (i == g->pos.By && j == g->pos.Bx)
				printf(COLOR_BOLD_SLOW_BLINKING_GREEN "%d" COLOR_OFF, g->map.v[i][j]);
				//printf(COLOR_BOLD_SLOW_BLINKING_GREEN "B" COLOR_OFF);
			else
				printf("%d", g->map.v[i][j]);
			printf(" ");
			//ft_putchar_fd(' ', 1);
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
