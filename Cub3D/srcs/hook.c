/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/25 08:55:43 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

int	convert_frames(int fr, int sp)
{
}

int	key_press(int keycode, t_game *g)
{
 	if (keycode == XK_Up || keycode == XK_Down)
	{
		double	dx;
		double	dy;
		int	x;
		int	y;

		dx = (int) (TRANS_STEP * cos(g->pos.rot * ROT_STEP * PI / 180.0));
		dy = (int) (TRANS_STEP * sin(g->pos.rot * ROT_STEP * PI / 180.0));

		//printf("Key Up Down\n");
		if (keycode == XK_Up)
		{
			dx = -dx;
			dy = -dy;
		}
		x = (int) ((g->pos.px - dx) / BOX_SIZE);
		y = (int) ((g->pos.py + dy) / BOX_SIZE);
		if (((keycode == XK_Up && !g->frames[FR_UP]) ||
			(keycode == XK_Down && !g->frames[FR_DOWN])) &&
				(x > 0 && y > 0 && x < g->map.l && y < g->map.h && !g->map.v[y][x] &&
				!g->map.v[y][(int) ((g->pos.px - dx + WALL_COLISION) / BOX_SIZE)] &&
				!g->map.v[y][(int) ((g->pos.px - dx - WALL_COLISION) / BOX_SIZE)] &&
				!g->map.v[(int) ((g->pos.py + dy + WALL_COLISION) / BOX_SIZE)][x] &&
				!g->map.v[(int) ((g->pos.py + dy - WALL_COLISION) / BOX_SIZE)][x]))
		{
			g->pos.px -= dx;
			g->pos.py += dy;
			g->pos.x = x;
			g->pos.y = y;
			if (keycode == XK_Up)
				g->frames[FR_UP] = 1;
			else
				g->frames[FR_DOWN] = 1;
		}
	}
	if (keycode == XK_Right || keycode == XK_Left)
	{
		if ((keycode == XK_Right && !g->frames[FR_RIGHT]) ||
			(keycode == XK_Left && !g->frames[FR_LEFT]))
		{
			if (keycode == XK_Right)
				g->pos.rot--;
			else
				g->pos.rot++;
			if (g->pos.rot < 0)
				g->pos.rot += 360 / ROT_STEP;
			else if (g->pos.rot >= 360 / ROT_STEP)
				g->pos.rot = 0;
			if (keycode == XK_Right)
				g->frames[FR_RIGHT] = 1;
			else
				g->frames[FR_LEFT] = 1;
		}
	}
	return (1);
}

int	key_release(int keycode, t_game *g)
{
	if (keycode == XK_space)
	{
		printf("Space\n");
	}
	if (keycode == XK_Control_L)
	{
		if (!g->frames[FR_GUN])
			g->frames[FR_GUN] = 1;
	}
	if (keycode == XK_q || keycode == XK_Escape)
	{
		printf("end game\n");
		end_game(g, 0, 0);
	}
	return (1);
}

int	mouse_hook(int button, int x, int y, t_game *g)
{
	printf("%d %d %d %d\n", button, x, y, g->pos.rot);
	double	alpha;
	alpha = atan((x / SCALE - WIDTH) / g->dpp) * 180.0 / PI; 
	printf("%d %d %d %f\n", button, x, y, alpha);
	g->pos.rot += (int)  alpha / ROT_STEP;
	printf("%d %d %d %d\n", button, x, y, g->pos.rot);
	if (g->pos.rot < 0)
		g->pos.rot += 360 / ROT_STEP;
	else if (g->pos.rot >= 360 / ROT_STEP)
		g->pos.rot = 0;
}
