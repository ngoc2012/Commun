/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/21 10:19:09 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

int	key_hook(int keycode, t_game *g)
 {
 	if (keycode == XK_Up || keycode == XK_Down)
	{
		printf("Key Up Down\n");
		g->pos.alpha = angle_convert(g->pos.alpha);
		draw(g);
	}
	if (keycode == XK_Right || keycode == XK_Left)
	{
	}
	if (keycode == XK_q || keycode == XK_Escape)
	{
		printf("end game\n");
		end_game(g, 0, 0);
	}
	return (0);
}
