/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/19 14:45:00 by minh-ngu         ###   ########.fr       */
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
	double	dx;
	double	dy;

	g->pos.alpha = 149;
	ix = -1;
	while (++ix < 1)
	{
		Xp = WIDTH / 2 - ix;
		printf("Xp = %d\n", Xp);
		ai0 = atan((double) Xp / g->dpp) * 180 / PI; 
		printf("ai0 = %f\n", ai0);
		ai = g->pos.alpha + ai0;
		printf("1 - ai = %f\n", ai );
		ai = angle_convert(ai);
		printf("2 - ai = %f\n", ai );
		// CHECKING HORIZONTAL INTERSECTIONS
		//Find A
		if (ai == 90)
		{
			Apy = (g->pos.py / BOX_SIZE) * BOX_SIZE - 1;
			dy = BOX_SIZE;
			dx = 0;
		}
		else if (ai == -90)
		{
			Apy = (g->pos.py / BOX_SIZE) * BOX_SIZE + BOX_SIZE;
			dy = BOX_SIZE;
			dx = 0;
		}
		if (ai > 0.0 && ai < 180.0)
			Apy = (g->pos.py / BOX_SIZE) * BOX_SIZE - 1;
		else
			Apy = (g->pos.py / BOX_SIZE) * BOX_SIZE + BOX_SIZE;
		Apx = g->pos.px + (g->pos.py - Apy) / tan(ai * PI / 180.0);
		Ax = Apx / BOX_SIZE;
		Ay = Apy / BOX_SIZE;
		if (Ax >= 0 && Ax <= g->map.l - 1)
		{
			printf("px = %d, Apx = %d, x = %d, Ax = %d\n", g->pos.px, Apx, g->pos.x, Ax);
			printf("py = %d, Apy = %d, y = %d, Ay = %d\n", g->pos.py, Apy, g->pos.y, Ay);
			dx = BOX_SIZE / tan(ai * PI / 180.0);
			if (dx < 0)
				dx *= -1;
			dy = BOX_SIZE;
			while (!g->map.v[Ay][Ax])
			{
				Apy -= dy;
				if (ai >= -90.0 && ai <= 90.0)
					Apx += dx;
				else
					Apx -= dx;
				Ax = Apx / BOX_SIZE;
				Ay = Apy / BOX_SIZE;
				printf("px = %d, Apx = %d, x = %d, Ax = %d\n", g->pos.px, Apx, g->pos.x, Ax);
				printf("py = %d, Apy = %d, y = %d, Ay = %d\n", g->pos.py, Apy, g->pos.y, Ay);
			}
			printf("value = %d\n", g->map.v[Ay][Ax]);
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

	addr = (int *)g->mlx.addr;
	yp = -1;
	while (++yp < HEIGHT)
	{
		xp = -1;
		while (++xp < WIDTH)
			*(addr++) = create_trgb(1, 255, 0, 0);
	}
	mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->mlx.img, 0, 0);

	draw_wall(g);
	draw_map(g);
	draw_mini_map(g);
	//printf("g.h = %d, g.l = %d, g.x = %d, g.y = %d, g.dx = %d, g.dy = %d\n", g.h , g.l , g.x , g.y , g.dx , g.dy);
}
