/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/30 00:24:49 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_data(t_vars *vars)
{
	vars->fractals = (t_fractal)
	{.f = {e_julia, e_mandelbrot, e_burn, e_sier}};
	vars->log_2 = 1.0 / log(2.0);
	vars->log_r = 1.0 / log(RADIUS);
	vars->max_iter = MIN_ITER;
	vars->smooth = 0;
	vars->pallet = 0;
	vars->iters = creat_vp(HEIGHT, WIDTH);
	vars->xn = creat_vp_d(HEIGHT, WIDTH);
	vars->yn = creat_vp_d(HEIGHT, WIDTH);
	vars->colors = creat_vp_d(HEIGHT, WIDTH);
	vars->img0 = malloc(sizeof(int) * WIDTH * HEIGHT);
}

void	secure_data(t_vars *vars)
{
	if (!vars->iters || !vars->xn || !vars->yn
		|| !vars->colors || !vars->img0)
	{
		if (vars->iters)
			free(vars->iters);
		if (vars->xn)
			free(vars->xn);
		if (vars->yn)
			free(vars->yn);
		if (vars->colors)
			free(vars->colors);
		if (vars->img0)
			free(vars->img0);
		exit(EXIT_FAILURE);
	}
}

void	init_draw2(t_vars *vars)
{
	vars->scale = (vars->right - vars->left) / WIDTH;
	if (vars->type == e_burn)
	{
		vars->top = 2.0;
		vars->bottom = vars->top - vars->scale * HEIGHT;
	}
	else
	{
		vars->top = vars->scale * HEIGHT * 0.5;
		vars->bottom = -vars->scale * HEIGHT * 0.5;
	}
	cal_v(vars, 0, WIDTH);
	colors_v(vars, 0, WIDTH);
	draw(vars, vars->img);
}

void	init_draw(t_vars *vars)
{
	if (vars->type == e_julia)
		init_julia(vars);
	else if (vars->type == e_mandelbrot)
		init_mandel(vars);
	else if (vars->type == e_burn)
		init_burn(vars);
	else if (vars->type == e_sier)
	{
		init_sier(vars);
		draw_sier(vars);
		return ;
	}
	init_draw2(vars);
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
	init_draw(vars);
	mlx_loop(vars->mlx);
}
