/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/24 06:52:09 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

void	init_data(t_vars *vars)
{
	vars->max_iter = MIN_ITER;
	vars->smooth = 0;
	vars->pallet = 0;
	vars->scale = (vars->right - vars->left) / WIDTH;
	vars->top = vars->scale * HEIGHT * 0.5;
	vars->bottom = -vars->scale * HEIGHT * 0.5;
	vars->iters = creat_vp(HEIGHT, WIDTH);
	vars->update = ft_calloc(HEIGHT * WIDTH, sizeof(unsigned char));
	vars->xn = creat_vp_d(HEIGHT, WIDTH);
	vars->yn = creat_vp_d(HEIGHT, WIDTH);
	vars->colors = creat_vp_d(HEIGHT, WIDTH);
	vars->colors_p = creat_vp(HEIGHT, WIDTH);
	if (!vars->iters || !vars->xn ||  !vars->yn || !vars->colors || !vars->colors_p || !vars->update)
	{
		if (vars->iters)
			free(vars->iters);
		if (vars->xn)
			free(vars->xn);
		if (vars->yn)
			free(vars->yn);
		if (vars->colors)
			free(vars->colors);
		if (vars->colors_p)
			free(vars->colors_p);
		if (vars->update)
			free(vars->update);
		exit(EXIT_FAILURE);
	}
}

//int	render(t_vars *vars)
int	render()
{
	/*
	VAR_TYPE	s;

	//ft_printf("xp = %d, yp = %d\n", vars->xp, vars->yp);
	if (vars->update[vars->yp * WIDTH + vars->xp])
	{
		//ft_printf("xp = %d, yp = %d\n", xp, yp);
		if (vars->type == JULIA)
			julia(vars, vars->xp, vars->yp, RADIUS * RADIUS);
		else if (vars->type == MANDELBROT)
			mandel(vars, vars->xp, vars->yp, RADIUS * RADIUS);
		if (vars->smooth && vars->type == JULIA)
			s = color_julia(vars, vars->xp, vars->yp, RADIUS * RADIUS);
		else if (vars->smooth && vars->type == MANDELBROT)
			s = color_mandel(vars, vars->xp, vars->yp);
		else
			s = (VAR_TYPE) vars->iters[vars->xp][vars->yp];
		vars->colors[vars->xp][vars->yp] = s / (VAR_TYPE) vars->max_iter;
		vars->update[vars->yp * WIDTH + vars->xp] = 1;
	}
	if (vars->xp == WIDTH - 1)
	{
		vars->xp = 0;
		if (vars->yp == HEIGHT - 1)
		{
			vars->yp = 0;
			draw(vars, vars->img);
		}
		else
			vars->yp++;
	}
	else
		vars->xp++;
		*/
	return (1);
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
	ft_printf("img.bits_per_pixel = %d\n", img.bits_per_pixel);
	ft_printf("img.line_length = %d\n", img.line_length);
	ft_printf("WIDTH = %d\n", WIDTH);
	vars->img = &img;
	cal_v(vars, 0, WIDTH);
	colors_v(vars, 0, WIDTH);
	draw(vars, &img);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	vars->xp = 0;
	vars->yp = 0;
	mlx_loop_hook(vars->mlx, &render, vars);
	mlx_loop(vars->mlx);
}

void	init_julia(t_vars *vars)
{
	vars->type = JULIA;
	vars->cx = 0.285;
	vars->cy = 0.01;
	vars->left = -1.5;
	vars->right = 1.5;
}

void	init_mandel(t_vars *vars)
{
	vars->type = MANDELBROT;
	vars->left = -2.0;
	vars->right = 1.0;
}
