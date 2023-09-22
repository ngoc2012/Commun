/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/22 10:16:52 by ngoc             ###   ########.fr       */
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
		double	x;
		double	y;

		dx = (int) (TRANS_SPEED * cos(g->pos.alpha * PI / 180.0));
		dy = (int) (TRANS_SPEED * sin(g->pos.alpha * PI / 180.0));

		//printf("Key Up Down\n");
		if (keycode == XK_Up)
		{
			dx = -dx;
			dy = -dy;
		}
		x = g->pos.px - dx;
		y = g->pos.py + dy;
		if (
		;
		redraw(g);
		draw(g);
	}
	if (keycode == XK_Right || keycode == XK_Left)
	{
		if (keycode == XK_Right)
			g->pos.alpha -= ROT_SPEED;
		else
			g->pos.alpha += ROT_SPEED;
		g->pos.alpha = angle_convert(g->pos.alpha);
		redraw(g);
		draw(g);
	}
	if (keycode == XK_q || keycode == XK_Escape)
	{
		printf("end game\n");
		end_game(g, 0, 0);
	}
	return (0);
}
