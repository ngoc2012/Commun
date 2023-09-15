/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/15 11:44:40 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

void	free_map(t_prog *p)
{
	int	i;

	i = -1;
	while (++i < p->h)
		free(p->map[i]);
	free(p->map);
}

void	end_prog(t_prog *p, int exit_code, char *s)
{
	mlx_destroy_image(p->mlx, p->img);
	mlx_destroy_window(p->mlx, p->win);
	mlx_destroy_display(p->mlx);
	free(p->mlx);
	free_map(p);
	if (s)
		ft_putstr_fd(s, 2);
	exit(exit_code);
}

int	create_trgb(unsigned char t, unsigned char r,
		unsigned char g, unsigned char b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
 
int	key_hook(int keycode, t_prog *p)
 {
 	if (keycode == XK_Up || keycode == XK_Down)
		printf("Key Up Down\n");
	if (keycode == XK_Right || keycode == XK_Left)
	{
	}
	if (keycode == XK_q || keycode == XK_Escape)
		end_prog(p, 0, 0);
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

void	get_map(t_game *g, char *fn)
{
	int	fd;
	char	*s;
	int	i;
	int	j;

	g->map.h = 0;
	g->map.l = 0;
	g->pos.x = 0;
	g->pos.y = 0;
	g->pos.dx = 0;
	g->pos.dy = 0;
	fd = open(fn, O_RDONLY);
	s = get_next_line(fd);
	while (s)
	{
		m->map.h++;
		if ((int) ft_strlen(s) > m->map.l)
			m->map.l = (int) ft_strlen(s);
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
	g->map.v = malloc(sizeof(int *) * g->map.h);
	fd = open(fn, O_RDONLY);
	j = -1;
	s = get_next_line(fd);
	while (s)
	{
		m->map[++j] = malloc(sizeof(int) * m->map.l);
		i = 0;
		while (i < m->l)
			m->map.v[j][i++] = 0;
		i = -1;
		while (s[++i])
		{
			if (s[i] == '1')
				m->map[j][i] = 1;
			else if (s[i] == '2')
				m->map[j][i] = 2;
			else if (s[i] == '3')
				m->map[j][i] = 3;
			else if (s[i] == '4')
				m->map[j][i] = 4;
			else if (s[i] == '5')
				m->map[j][i] = 5;
			else if (s[i] == '6')
				m->map[j][i] = 6;
			else if (s[i] == '7')
				m->map[j][i] = 7;
			else if (ft_strchr("NSWE", s[i]))
			{
				m->x = i;
				m->y = j;
				if (s[i] == 'N')
					m->dy = 1;
				else if (s[i] == 'S')
					m->dy = -1;
				else if (s[i] == 'W')
					m->dx = 1;
				else if (s[i] == 'E')
					m->dx = -1;
			}
		}
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
	if ((!m->dx && !m->dy) || m->map.h < 5 || m->map.l < 5)
		end_prog(p, 1, "Invalid map");
}

int	main()
{
	t_game	g;

	g.mlx.mlx = mlx_init();
	g.mlx.win = mlx_new_window(g.mlx.mlx, WIDTH, HEIGHT, "Cub3D");
	if (!g.mlx.mlx || !g.mlx.win)
		exit(EXIT_FAILURE);
	mlx_key_hook(g.mlx.win, key_hook, &p);
	//mlx_mouse_hook(g.win, mouse_hook, p);
	//mlx_loop_hook(g.mlx, loop_hook, p);
	//mlx_hook(g.win, ClientMessage, LeaveWindowMask, &end_prog, p);
	g.mlx.img = mlx_new_image(g.mlx.mlx, WIDTH, HEIGHT);
	g.mlx.addr = mlx_get_data_addr(g.mlx.img, &g.mlx.bpp, &g.mlx.ll, &g.mlx.ed);
	get_map(&g, "maps/3.cub");
	//printf("g.h = %d, g.l = %d, g.x = %d, g.y = %d, g.dx = %d, g.dy = %d\n", g.h , g.l , g.x , g.y , g.dx , g.dy);

/*
	double posX = 22, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane


	int	x;
	//int	y;
	int	*addr;
	addr = (int *)p.addr;
	x = -1;
	while (++x < WIDTH)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//which box of the map we're in
		int mapX = int(posX);
		int mapY = int(posY);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		//these are derived as:
		//deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
		//deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
		//which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
		//where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
		//unlike (dirX, dirY) is not 1, however this does not matter, only the
		//ratio between deltaDistX and deltaDistY matters, due to the way the DDA
		//stepping further below works. So the values can be computed as below.
		// Division through zero is prevented, even though technically that's not
		// needed in C++ with IEEE 754 floating point values.
		double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);

		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
			  //calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		//perform DDA
		while(hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if(worldMap[mapX][mapY] > 0) hit = 1;
		}
		//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
		//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
		//This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
		//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
		//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
		//steps, but we subtract deltaDist once because one step more into the wall was taken above.
		if(side == 0) perpWallDist = (sideDistX - deltaDistX);
		else          perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(h / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h) drawEnd = h - 1;

		//choose wall color
		ColorRGB color;
		switch(worldMap[mapX][mapY])
		{
			case 1:  color = RGB_Red;    break; //red
			case 2:  color = RGB_Green;  break; //green
			case 3:  color = RGB_Blue;   break; //blue
			case 4:  color = RGB_White;  break; //white
			default: color = RGB_Yellow; break; //yellow
		}

		//give x and y sides different brightness
		if(side == 1) {color = color / 2;}

		*(addr++) = create_trgb(1,255,0,0);
	}
	//yp = -1;
	//while (++yp < HEIGHT)
	//{
	//}
	*/
	mlx_put_image_to_window(g.mlx.mlx, g.mlx.win, g.mlx.img, 0, 0);
	mlx_loop(g.mlx.mlx);
}
