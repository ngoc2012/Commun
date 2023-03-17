/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/17 23:41:22 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	end_prog(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	del_vp(vars->vp0.iters, WIDTH);
	del_vp_d(vars->vp0.xn, WIDTH);
	del_vp_d(vars->vp0.yn, WIDTH);
	del_vp_d(vars->vp0.colors, WIDTH);
	exit(EXIT_SUCCESS);
}

void	print_viewport(t_viewport *vp)
{
	printf("Top = %.10f, bottom = %.10f, left = %.10f, right = %.10f\n", vp->top, vp->bottom, vp->left, vp->right);
}

int	key_hook(int keycode, t_vars *vars)
{
	double	d;

	//ft_printf("keycode: %d\n", keycode);
	if (keycode == XK_q || keycode == 65507 || keycode == XK_Escape)
		end_prog(vars);
	if (keycode == XK_Right || keycode == XK_Left)
	{
		d = (vars->right - vars->left) * MOVE;
		if (keycode == XK_Left)
			d = -d;
		vars->left += d;
		vars->right += d;
		vars->vp0.left += d;
		vars->vp0.right += d;
		//print_viewport(&vars->vp0);
		cal(vars, &vars->vp0);
		colors(vars, &vars->vp0);
		draw(vars, vars->img);
	}
	else if (keycode == XK_Up || keycode == XK_Down)
	{
		d = (vars->top - vars->bottom) * MOVE;
		if (keycode == XK_Down)
			d = -d;
		vars->top += d;
		vars->bottom += d;
		vars->vp0.top += d;
		vars->vp0.bottom += d;
		//print_viewport(&vars->vp0);
		cal(vars, &vars->vp0);
		colors(vars, &vars->vp0);
		draw(vars, vars->img);
	}
	else if (keycode == XK_r)
	{
	}
	return (0);
}

int	mouse_hook(int button, int px, int py, t_vars *vars)
{
	//ft_printf("Button: %d, x = %d, y = %d \n", button, px, py);
	//ft_printf("In_process = %d\n", g_process);
	double	zoom;
	double	Lx;
	double	Ly;
	double	dx;
	double	dy;
	//double	x0, y0;
	if (vars->in_process)
		return (0);
	if (button == 4 || button == 5)
	{
		if (button == 4)
			zoom = 1 / ZOOM;
		if (button == 5)
			zoom = ZOOM;
		dx = px * vars->scale * (1 - zoom);
		dy = py * vars->scale * (zoom - 1);
		Lx = vars->right -  vars->left;
		Ly = vars->top -  vars->bottom;
		vars->left += dx;
		vars->right = Lx * zoom + vars->left;
		vars->top += dy;
		vars->bottom = vars->top - Ly * zoom;
		vars->scale *= zoom;
		vars->vp0.left += dx;
		vars->vp0.right = Lx * zoom + vars->vp0.left;
		vars->vp0.top += dy;
		vars->vp0.bottom = vars->vp0.top - Ly * zoom;
		vars->vp0.scale *= zoom;
		//print_viewport(&vars->vp0);
		cal(vars, &vars->vp0);
		colors(vars, &vars->vp0);
		draw(vars, vars->img);
	}
	return (0);
}

int	**creat_vp(int h, int w)
{
	int	**vp;
	int	i;
	int	j;

	vp = malloc(sizeof(int*) * w);
	if (!vp)
		return (0);
	i = -1;
	while (++i < w)
	{
		vp[i] = malloc(sizeof(int) * h);
		if (!vp[i])
		{
			j = -1;
			while (++j < i)
				free(vp[i]);
			free(vp);
			return (0);
		}
	}
	return (vp);
}

void	del_vp(int **vp, int w)
{
	int	i;

	i = -1;
	while (++i < w)
		free(vp[i]);
	free(vp);
}

double	**creat_vp_d(double h, int w)
{
	double	**vp;
	int	i;
	int	j;

	vp = malloc(sizeof(double*) * w);
	if (!vp)
		return (0);
	i = -1;
	while (++i < w)
	{
		vp[i] = malloc(sizeof(double) * h);
		if (!vp[i])
		{
			j = -1;
			while (++j < i)
				free(vp[i]);
			free(vp);
			return (0);
		}
	}
	return (vp);
}

void	del_vp_d(double **vp, int w)
{
	int	i;

	i = -1;
	while (++i < w)
		free(vp[i]);
	free(vp);
}

void	help()
{
	ft_printf("./fract-ol Julia\n");
	ft_printf("./fract-ol Mandelbrot\n");
}

// https://en.m.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set
int	main(int argc, char **argv)
{
	t_vars	vars;
	t_img	img;

	help();
	if (argc != 2)
		exit(EXIT_SUCCESS);
	vars.max_iter = MIN_ITER;
	vars.in_process = 0;
	if (ft_strncmp(argv[1], "Julia", 6) == 0)
	{
		vars.type = JULIA;
		vars.cx = 0.285;
		vars.cy = 0.01;
		vars.left = -2.0;
		vars.right = 1.0;
		vars.scale = (vars.right - vars.left) / WIDTH;
		vars.top = vars.scale * HEIGHT * 0.5;
		vars.bottom = -vars.scale * HEIGHT * 0.5;

		vars.vp0.left = vars.left;
		vars.vp0.right = vars.right;
		vars.vp0.scale = vars.scale;
		vars.vp0.top = vars.top;
		vars.vp0.bottom = vars.bottom;
		vars.vp0.iters = creat_vp(HEIGHT, WIDTH);
		vars.vp0.xn = creat_vp_d(HEIGHT, WIDTH);
		vars.vp0.yn = creat_vp_d(HEIGHT, WIDTH);
		vars.vp0.colors = creat_vp_d(HEIGHT, WIDTH);
		if (!vars.vp0.iters || !vars.vp0.xn ||  !vars.vp0.yn ||  !vars.vp0.colors)
		{
			if (vars.vp0.iters)
				free(vars.vp0.iters);
			if (vars.vp0.xn)
				free(vars.vp0.xn);
			if (vars.vp0.yn)
				free(vars.vp0.yn);
			if (vars.vp0.colors)
				free(vars.vp0.yn);
			exit(EXIT_FAILURE);
		}
	}
	else if (ft_strncmp(argv[1], "Mandelbrot", 11) == 0)
	{
		vars.type = MANDELBROT;

		vars.left = -2.0;
		vars.right = 1.0;
		vars.scale = (vars.right - vars.left) / WIDTH;
		vars.top = vars.scale * HEIGHT * 0.5;
		vars.bottom = -vars.scale * HEIGHT * 0.5;

		//vars.left = -1.253537;
		//vars.right = -1.253142;
		//vars.scale = (vars.right - vars.left) / WIDTH;
		//vars.top = -0.378073;
		//vars.bottom = vars.top - vars.scale * HEIGHT;

		vars.vp0.left = vars.left;
		vars.vp0.right = vars.right;
		vars.vp0.scale = vars.scale;
		vars.vp0.top = vars.top;
		vars.vp0.bottom = vars.bottom;
		vars.vp0.iters = creat_vp(HEIGHT, WIDTH);
		vars.vp0.xn = creat_vp_d(HEIGHT, WIDTH);
		vars.vp0.yn = creat_vp_d(HEIGHT, WIDTH);
		vars.vp0.colors = creat_vp_d(HEIGHT, WIDTH);
		if (!vars.vp0.iters || !vars.vp0.xn ||  !vars.vp0.yn ||  !vars.vp0.colors)
		{
			if (vars.vp0.iters)
				free(vars.vp0.iters);
			if (vars.vp0.xn)
				free(vars.vp0.xn);
			if (vars.vp0.yn)
				free(vars.vp0.yn);
			if (vars.vp0.colors)
				free(vars.vp0.yn);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		ft_printf("Fractal %s unknown???\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	//print_viewport(&vars.vp0);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, argv[1]);
	if (!vars.mlx || !vars.win)
		exit(EXIT_FAILURE);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_hook(vars.win, ClientMessage, LeaveWindowMask, &end_prog, &vars);
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	vars.img = &img;
	cal(&vars, &vars.vp0);
	colors(&vars, &vars.vp0);
	draw(&vars, &img);
	mlx_loop(vars.mlx);
}
