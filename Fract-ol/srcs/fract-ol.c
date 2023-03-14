/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/14 11:25:32 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	end_prog(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, t_vars *vars)
{
	//ft_printf("keycode: %d\n", keycode);
	if (keycode == XK_q || keycode == 65507 || keycode == XK_Escape)
		end_prog(vars);
	return (0);
}


int	mouse_hook(int button, int px, int py, t_vars *vars)
{
	//ft_printf("Button: %d, x = %d, y = %d \n", button, px, py);
	ft_printf("In_process = %d\n", vars->in_process);
	if (vars->in_process)
		return (0);
	vars->cx += vars->left - px * vars->scale;
	vars->cy += vars->top - py * vars->scale;
	if (button == 1)
		vars->scale /= 2.0;
	if (button == 3)
		vars->scale *= 2.0;
	vars->left = vars->scale * vars->w / 2;
	vars->top = vars->scale * vars->h / 2;
	draw(vars, vars->img);
	return (0);
}

// https://en.m.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set
int	main(int argc, char **argv)
{
	t_vars	vars;
	t_img	img;

	if (argc != 2)
		exit(EXIT_SUCCESS);
	if (ft_strncmp(argv[1], "JULIA", 6) == 0)
		vars.type = JULIA;
	else if (ft_strncmp(argv[1], "MANDELBROT", 11) == 0)
		vars.type = MANDELBROT;
	else
	{
		ft_printf("Fractal %s unknown???\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	vars.w = 500;
	vars.h = 500;
	vars.max_iter = MAX_ITER;
	vars.min_iter = 0;
	vars.in_process = 0;
	vars.scale = (double) 4 / vars.w;
	vars.left = vars.scale * vars.w / 2;
	vars.top = vars.scale * vars.h / 2;
	vars.cx = 0.0;
	vars.cy = 0.0;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.w, vars.h, argv[1]);
	if (!vars.mlx || !vars.win)
		exit(EXIT_FAILURE);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_hook(vars.win, ClientMessage, LeaveWindowMask, &end_prog, &vars);
	img.img = mlx_new_image(vars.mlx, vars.w, vars.h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	vars.img = &img;
	draw(&vars, &img);
	mlx_loop(vars.mlx);
}
