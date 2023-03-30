/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/29 23:43:26 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	end_prog(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	del_vp(vars->iters, WIDTH);
	del_vp_d(vars->xn, WIDTH);
	del_vp_d(vars->yn, WIDTH);
	del_vp_d(vars->colors, WIDTH);
	free(vars->img0);
	exit(EXIT_SUCCESS);
}

void	set_env(VAR_TYPE zoom, int px, int py, t_vars *vars)
{
	VAR_TYPE	l_x;
	VAR_TYPE	l_y;

	l_x = vars->right - vars->left;
	l_y = vars->top - vars->bottom;
	vars->left += px * vars->scale * (1 - zoom);
	vars->right = l_x * zoom + vars->left;
	vars->top += py * vars->scale * (zoom - 1);
	vars->bottom = vars->top - l_y * zoom;
	vars->scale *= zoom;
}

void	set_zoom(t_vars *vars)
{
	t_coor	p;
	int		r2;
	int		*addr;

	r2 = RADIUS * RADIUS;
	addr = (int *) vars->img->addr;
	p.y = -1;
	while (++p.y < HEIGHT)
	{
		p.x = -1;
		while (++p.x < WIDTH)
			draw_p(vars, &p, addr++, r2);
	}
}

void	zoom_fractal(t_vars *vars, int px, int py, VAR_TYPE zoom)
{
	if (vars->type == e_sier)
	{
		if (vars->scale > 4000000)
			return ;
		zoom = 1 / zoom;
		vars->start.c.x = px + (vars->start.c.x - px) * zoom;
		vars->start.c.y = py + (vars->start.c.y - py) * zoom;
		vars->start.a *= zoom;
		vars->scale *= zoom;
		draw_sier(vars);
	}
	else
	{
		set_env(zoom, px, py, vars);
		set_zoom(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	}
}

int	mouse_hook(int button, int px, int py, t_vars *vars)
{
	VAR_TYPE	zoom;

	if (button == 4 || button == 5)
	{
		if (button == 4)
			zoom = 1 / ZOOM;
		if (button == 5)
			zoom = ZOOM;
		zoom_fractal(vars, px, py, zoom);
	}
	if (button == 3 && vars->type == e_julia)
	{
		vars->cx = (vars->left + px * vars->scale);
		vars->cy = (vars->top - py * vars->scale) * 0.1;
		printf("cx: %f, cy = %f\n", vars->cx, vars->cy);
		cal_v(vars, 0, WIDTH);
		colors_v(vars, 0, WIDTH);
		draw(vars, vars->img);
	}
	return (0);
}
