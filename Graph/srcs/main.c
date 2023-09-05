/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/02 22:03:02 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

void	end_prog(t_prog *p)
{
	mlx_destroy_image(p->mlx, p->img);
	mlx_destroy_window(p->mlx, p->win);
	mlx_destroy_display(p->mlx);
	free(p->mlx);
	exit(EXIT_SUCCESS);
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
	//if (keycode == XK_Right || keycode == XK_Left)
	//{
	//}
	if (keycode == XK_q || keycode == XK_Escape)
		end_prog(p);

	return (0);
}

int	main()
{
	t_prog	p;

	p.mlx = mlx_init();
	p.win = mlx_new_window(p.mlx, WIDTH, HEIGHT, "Cub3D");
	if (!p.mlx || !p.win)
		exit(EXIT_FAILURE);
	mlx_key_hook(p.win, key_hook, &p);
	//mlx_mouse_hook(p.win, mouse_hook, p);
	//mlx_loop_hook(p.mlx, loop_hook, p);
	//mlx_hook(p.win, ClientMessage, LeaveWindowMask, &end_prog, p);
	p.img = mlx_new_image(p.mlx, WIDTH, HEIGHT);
	p.addr = mlx_get_data_addr(p.img, &p.bpp, &p.ll, &p.endian);

	int	xp;
	int	yp;
	int	*addr;
	addr = (int *)p.addr;
	yp = -1;
	while (++yp < HEIGHT)
	{
		xp = -1;
		while (++xp < WIDTH)
			*(addr++) = create_trgb(1,255,0,0);
	}
	mlx_put_image_to_window(p.mlx, p.win, p.img, 0, 0);
	mlx_loop(p.mlx);
}
