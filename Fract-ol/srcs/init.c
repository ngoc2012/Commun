/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/27 17:44:12 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_data(t_vars *vars)
{
	vars->log_2 = 1.0 / log(2.0);
	vars->log_r = 1.0 / log(RADIUS);
	vars->max_iter = MIN_ITER;
	vars->smooth = 0;
	vars->pallet = 0;
	vars->scale = (vars->right - vars->left) / WIDTH;
	vars->top = vars->scale * HEIGHT * 0.5;
	vars->bottom = -vars->scale * HEIGHT * 0.5;
	vars->iters = creat_vp(HEIGHT, WIDTH);
	vars->iters0 = creat_vp(HEIGHT, WIDTH);
	vars->xn = creat_vp_d(HEIGHT, WIDTH);
	vars->yn = creat_vp_d(HEIGHT, WIDTH);
	vars->colors = creat_vp_d(HEIGHT, WIDTH);
	vars->img0 = malloc(sizeof(int) * WIDTH * HEIGHT);
}

void	secure_data(t_vars *vars)
{
	if (!vars->iters || !vars->xn || !vars->yn
		|| !vars->colors || !vars->iters0 || !vars->img0)
	{
		if (vars->iters)
			free(vars->iters);
		if (vars->xn)
			free(vars->xn);
		if (vars->yn)
			free(vars->yn);
		if (vars->colors)
			free(vars->colors);
		if (vars->iters0)
			free(vars->iters0);
		if (vars->img0)
			free(vars->img0);
		exit(EXIT_FAILURE);
	}
}

void	init_pallets(t_vars *vars)
{
	vars->pallets[0] = (t_pallet){.d = 11,
		.val = {{2., 2., 10.}, {5., 22., 90.}, {2., 61., 177.},
	{215., 72., 38.}, {146., 49., 26.}, {80., 27., 14.},
	{146., 49., 26.}, {215., 72., 38.}, {2., 61., 177.},
	{5., 22., 90.}, {2., 2., 10.}}};
	vars->pallets[1] = (t_pallet){.d = 11,
		.val = {{255., 235., 0.}, {252., 0., 25.}, {1., 255., 79.},
	{255., 1., 215.}, {86., 0., 204.}, {0., 237., 245.},
	{86., 0., 204.}, {255., 1., 215.}, {1., 255., 79.},
	{252., 0., 25.}, {255., 235., 0.}}};
	vars->pallets[2] = (t_pallet){.d = 5,
		.val = {{20., 0., 0.}, {255., 20., 0.}, {255., 200., 0.},
	{255., 20., 0.}, {20., 0., 0.}}};
	vars->pallets[3] = (t_pallet){.d = 6,
		.val = {{0., 7., 100.}, {32., 107., 203.}, {237., 255., 255.},
	{255., 170., 0.}, {0., 2., 0.}, {0., 7., 100.}}};
	vars->pallets[4] = (t_pallet){.d = 3,
		.val = {{0., 0., 0.}, {255., 255., 255.}, {0., 0., 0.}}};
	vars->pallets[5] = (t_pallet){.d = 7,
		.val = {{255., 0., 0.}, {255., 255., 0.}, {0., 255., 0.},
	{0., 255., 255.}, {0., 0., 255.}, {255., 0., 255.}, {255., 0., 0.}}};
	vars->pallets[6] = (t_pallet){.d = 5,
		.val = {{0., 0., 0.}, {0., 0., 200.}, {255., 255., 255.},
	{0., 0., 200.}, {0., 0., 0.}}};
}

void	init_graph(t_vars *vars, char *w_name)
{
	t_img	img;

	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, w_name);
	if (!vars->mlx || !vars->win)
		exit(EXIT_FAILURE);
	mlx_key_hook(vars->win, key_hook, vars);
	mlx_mouse_hook(vars->win, mouse_hook, vars);
	mlx_hook(vars->win, ClientMessage, LeaveWindowMask, &end_prog, vars);
	img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.endian);
	vars->img = &img;
	cal_v(vars, 0, WIDTH);
	colors_v(vars, 0, WIDTH);
	draw(vars, &img);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	vars->xp = 0;
	vars->yp = 0;
	mlx_loop(vars->mlx);
}
