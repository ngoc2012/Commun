/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/24 06:40:47 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	end_prog(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	del_vp(vars->iters, WIDTH);
	del_vp(vars->colors_p, WIDTH);
	del_vp_d(vars->xn, WIDTH);
	del_vp_d(vars->yn, WIDTH);
	del_vp_d(vars->colors, WIDTH);
	free(vars->update);
	exit(EXIT_SUCCESS);
}

int	mouse_hook(int button, int px, int py, t_vars *vars)
{
	//ft_printf("Button: %d, x = %d, y = %d \n", button, px, py);
	//ft_printf("In_process = %d\n", g_process);
	VAR_TYPE	zoom;
	VAR_TYPE	Lx;
	VAR_TYPE	Ly;
	VAR_TYPE	dx;
	VAR_TYPE	dy;
	//VAR_TYPE	x0, y0;
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
		vars->left += dx;
		vars->right = Lx * zoom + vars->left;
		vars->top += dy;
		vars->bottom = vars->top - Ly * zoom;
		vars->scale *= zoom;
		//cal_th(vars, 0, HEIGHT, 'v');
		cal_v(vars, 0, WIDTH);
		colors_v(vars, 0, WIDTH);
		draw(vars, vars->img);
	}
	if (button == 3 && vars->type == JULIA)
	{
		vars->cx = (vars->left + px * vars->scale) * 0.5;
		vars->cy = (vars->top - py * vars->scale) * 0.5;
		printf("cx: %f, cy = %f\n", vars->cx, vars->cy);
		cal_v(vars, 0, WIDTH);
		colors_v(vars, 0, WIDTH);
		draw(vars, vars->img);
	}
	return (0);
}
