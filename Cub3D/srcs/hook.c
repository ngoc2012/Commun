/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/24 11:39:53 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

int	key_hook(int keycode, t_game *g)
 {
 	if (keycode == XK_Up || keycode == XK_Down)
	{
		double	dx;
		double	dy;
		int	x;
		int	y;

		dx = (int) (TRANS_SPEED * cos(g->pos.rot * ROT_SPEED * PI / 180.0));
		dy = (int) (TRANS_SPEED * sin(g->pos.rot * ROT_SPEED * PI / 180.0));

		//printf("Key Up Down\n");
		if (keycode == XK_Up)
		{
			dx = -dx;
			dy = -dy;
		}
		x = (int) ((g->pos.px - dx) / BOX_SIZE);
		y = (int) ((g->pos.py + dy) / BOX_SIZE);
		if (x > 0 && y > 0 && x < g->map.l && y < g->map.h && !g->map.v[y][x])
		{
			g->pos.px -= dx;
			g->pos.py += dy;
			g->pos.x = x;
			g->pos.y = y;
			//printf("x = %f, y = %f\n", g->pos.px, g->pos.py);
			draw(g);
		}
	}
	if (keycode == XK_Right || keycode == XK_Left)
	{
		if (keycode == XK_Right)
			g->pos.rot--;
		else
			g->pos.rot++;
		if (g->pos.rot < 0)
			g->pos.rot += 360 / ROT_SPEED;
		else if (g->pos.rot >= 360 / ROT_SPEED)
			g->pos.rot = 0;
		draw(g);
	}
	if (keycode == XK_space)
	{
		printf("Space\n");
	}
	if (keycode == XK_Control_L)
	{
		//render_backgroud(g);
		render_object(&g->gun[1], (int *) g->mlx.addr, WIDTH / 2 - g->gun[1].l / 2, HEIGHT - g->gun[1].h);
		scale_window(g);
		usleep(10000);
		//render_backgroud(g);
		render_object(&g->gun[2], (int *) g->mlx.addr, WIDTH / 2 - g->gun[2].l / 2, HEIGHT - g->gun[2].h);
		scale_window(g);
		//usleep(10000);
		printf("Ctrl\n");
		//draw(g);
	}
	if (keycode == XK_q || keycode == XK_Escape)
	{
		printf("end game\n");
		end_game(g, 0, 0);
	}
	return (0);
}
