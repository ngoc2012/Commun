/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/26 23:40:08 by ngoc             ###   ########.fr       */
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
	del_vp(vars->iters0, WIDTH);
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

//void	set_zoom(VAR_TYPE zoom, int px, int py, t_vars *vars)
void	set_zoom(t_vars *vars)
{
	t_coor	p;
	//int	x0;
	//int	y0;
	int	r2;
	int	*addr;
	//int	calculated;
	//VAR_TYPE	last_scale;
	//VAR_TYPE	tolerance;

	r2 = RADIUS * RADIUS;
	addr = (int *) vars->img->addr;
	//vars->img0 = ft_memcpy(vars->img0, addr, WIDTH * HEIGHT * 4);
	//last_scale = vars->scale / zoom;
	//tolerance = 0.25 * last_scale;
	p.y = -1;
	while (++p.y < HEIGHT)
	{
		p.x = -1;
		while (++p.x < WIDTH)
		{
			//calculated = 0;
			//x0 = (p.x - px) / zoom + px;
			//y0 = (p.y - py) / zoom + py;
			//if (x0 >= 0 && x0 < WIDTH && y0 >= 0 && y0 < HEIGHT)
			//{
			//	if ((VAR_TYPE) p.x * vars->scale - (VAR_TYPE) x0 * last_scale < tolerance
			//		&& (VAR_TYPE) p.y * vars->scale - (VAR_TYPE) y0 *last_scale < tolerance)
			//	{
			//		move_val(vars, &p, x0 - p.x, y0 - p.y);
			//		ft_memcpy(addr, &vars->img0[y0 * WIDTH + x0], 4);
			//		calculated = 1;
			//	}
			//}
			//if (!calculated)
				//draw_p(vars, &p, (int*) vars->img->addr, r2);
				draw_p(vars, &p, addr, r2);
			addr++;
		}
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
		set_env(zoom, px, py, vars);
		set_zoom(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	}
	if (button == 3 && vars->type == e_julia)
	{
		vars->cx = (vars->left + px * vars->scale) * 0.1;
		vars->cy = (vars->top - py * vars->scale) * 0.1;
		printf("cx: %f, cy = %f\n", vars->cx, vars->cy);
		cal_v(vars, 0, WIDTH);
		colors_v(vars, 0, WIDTH);
		draw(vars, vars->img);
	}
	return (0);
}
