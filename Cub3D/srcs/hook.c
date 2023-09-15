/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/15 13:55:15 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

int	key_hook(int keycode, t_game *g)
 {
 	if (keycode == XK_Up || keycode == XK_Down)
		printf("Key Up Down\n");
	if (keycode == XK_Right || keycode == XK_Left)
	{
	}
	if (keycode == XK_q || keycode == XK_Escape)
		end_game(g, 0, 0);
	/*
	if (keycode == XK_Up)
    //{
    //  if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
    //  if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
    //}
    ////move backwards if no wall behind you
    //if(keyDown(SDLK_DOWN))
    //{
    //  if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
    //  if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
    //}
    ////rotate to the right
    //if(keyDown(SDLK_RIGHT))
    //{
    //  //both camera direction and camera plane must be rotated
    //  double oldDirX = dirX;
    //  dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
    //  dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
    //  double oldPlaneX = planeX;
    //  planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
    //  planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    //}
    ////rotate to the left
    //if(keyDown(SDLK_LEFT))
    //{
    //  //both camera direction and camera plane must be rotated
    //  double oldDirX = dirX;
    //  dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
    //  dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
    //  double oldPlaneX = planeX;
    //  planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
    //  planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    //}
*/
	return (0);
}
