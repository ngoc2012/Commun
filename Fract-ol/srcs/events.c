/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/30 20:48:49 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	loop_hook(t_vars *vars)
{
	int		r2;
	int		*addr;

	r2 = RADIUS * RADIUS;
	if (!vars->updated && vars->type != e_sier)
	{
		if (vars->p.y == HEIGHT)
		{
			mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
			vars->updated = 1;
			return (0);
		}
		r2 = RADIUS * RADIUS;
		addr = (int *) vars->img->addr + vars->p.y * WIDTH;
		vars->p.x = -1;
		while (++vars->p.x < WIDTH)
			draw_p(vars, &vars->p, addr++, r2);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
		vars->p.y++;
	}
	return (0);
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

void	set_zoom(t_vars *vars, VAR_TYPE zoom, int *addr, t_coor *c)
{
	t_coor	p;
	t_coor	p0;
	int		r2;

	r2 = RADIUS * RADIUS;
	p.y = -1;
	while (++p.y < HEIGHT)
	{
		p.x = -1;
		while (++p.x < WIDTH)
		{
			p0.x = (p.x - c->x) * zoom + c->x;
			p0.y = (p.y - c->y) * zoom + c->y;
			if (p0.x < 0 || p0.x >= WIDTH || p0.y < 0 || p0.y >= HEIGHT)
				draw_p(vars, &p, addr, r2);
			else
				*(addr) = *(vars->img0 + p0.y * WIDTH + p0.x);
			addr++;
		}
	}
	vars->updated = 0;
	vars->p.x = 0;
	vars->p.y = 0;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}

void	zoom_fractal(t_vars *vars, int px, int py, VAR_TYPE zoom)
{
	t_coor	c;
	int		*addr;

	if (vars->type == e_sier)
	{
		zoom = 1 / zoom;
		if (vars->scale * zoom > 4000000)
			return ;
		vars->start.c.x = px + (vars->start.c.x - px) * zoom;
		vars->start.c.y = py + (vars->start.c.y - py) * zoom;
		vars->start.a *= zoom;
		vars->scale *= zoom;
		draw_sier(vars);
	}
	else
	{
		addr = (int *)vars->img->addr;
		c.x = px;
		c.y = py;
		set_env(zoom, c.x, c.y, vars);
		ft_memmove(vars->img0, addr, WIDTH * HEIGHT * 4);
		set_zoom(vars, zoom, addr, &c);
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
		cal_v(vars, 0, WIDTH);
		colors_v(vars, 0, WIDTH);
		draw(vars, vars->img);
		ft_printf("Julia changed\n");
	}
	return (0);
}
