/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/24 21:51:17 by ngoc             ###   ########.fr       */
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
			(keycode == XK_Down && g->frames - g->fr_down > TRANS_SPEED)) &&
				(x > 0 && y > 0 && x < g->map.l && y < g->map.h && !g->map.v[y][x]))
		{
			g->pos.px -= dx;
			g->pos.py += dy;
			g->pos.x = x;
			g->pos.y = y;
			if (keycode == XK_Up)
				g->fr_up = g->frames;
			else
				g->fr_down = g->frames;
		}
	}
	if (keycode == XK_Right || keycode == XK_Left)
	{
		if ((keycode == XK_Right && g->frames - g->fr_right > ROT_SPEED) ||
			(keycode == XK_Left && g->frames - g->fr_left > ROT_SPEED))
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
				g->fr_right = g->frames;
			else
				g->fr_left = g->frames;
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
		g->fr_gun = g->frames;
	}
	if (keycode == XK_q || keycode == XK_Escape)
	{
		printf("end game\n");
		end_game(g, 0, 0);
	}
	return (1);
}
