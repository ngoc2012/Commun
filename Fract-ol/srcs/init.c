/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/26 10:36:56 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_data(t_vars *vars)
{
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
	if (!vars->iters || !vars->xn ||  !vars->yn || !vars->colors || !vars->iters0 || !vars->img0)
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
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//ft_printf("img.bits_per_pixel = %d\n", img.bits_per_pixel);
	//ft_printf("img.line_length = %d\n", img.line_length);
	//ft_printf("WIDTH = %d\n", WIDTH);
	vars->img = &img;
	cal_v(vars, 0, WIDTH);
	colors_v(vars, 0, WIDTH);
	draw(vars, &img);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	vars->xp = 0;
	vars->yp = 0;
	//mlx_loop_hook(vars->mlx, &render, vars);
	mlx_loop(vars->mlx);
}

void	init_julia(t_vars *vars)
{
	vars->type = e_julia;
	vars->cx = 0.285;
	vars->cy = 0.01;
	vars->left = -1.5;
	vars->right = 1.5;
}

void	init_mandel(t_vars *vars)
{
	vars->type = e_mandelbrot;
	vars->left = -2.0;
	vars->right = 1.0;
}
