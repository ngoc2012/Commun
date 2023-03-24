/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/23 20:07:50 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

void	julia(t_vars *vars, int xp, int yp, int R2)
{
	VAR_TYPE   x;
	VAR_TYPE   y;
	VAR_TYPE   x0;
	VAR_TYPE   y0;
	VAR_TYPE   x2;
	VAR_TYPE   y2;
	int	i;

	x0 = vars->left + vars->scale * xp;
	y0 = vars->top  - vars->scale * yp;
	x = x0;
	y = y0;
	x2 = x * x;
	y2 = y * y;
	i = 0;
	while (x2 + y2 < R2 && ++i < vars->max_iter)
	{
		y = 2 * x * y + vars->cy;
		x = x2 - y2 + vars->cx;
		x2 = x * x;
		y2 = y * y;
	}
	vars->iters[xp][yp] = i;
	vars->xn[xp][yp] = x;
	vars->yn[xp][yp] = y;
}

void	mandel(t_vars *vars, int xp, int yp, int R2)
{
	VAR_TYPE   x;
	VAR_TYPE   y;
	VAR_TYPE   x0;
	VAR_TYPE   y0;
	VAR_TYPE   x2;
	VAR_TYPE   y2;
	int	i;

	x0 = vars->left + vars->scale * xp;
	y0 = vars->top  - vars->scale * yp;
	x = 0.0;
	y = 0.0;
	x2 = 0.0;
	y2 = 0.0;
	i = 0;
	while (x2 + y2 < R2 && ++i < vars->max_iter)
	{
		y = 2 * x * y + y0;
		x = x2 - y2 + x0;
		x2 = x * x;
		y2 = y * y;
	}
	vars->iters[xp][yp] = i;
	vars->xn[xp][yp] = x;
	vars->yn[xp][yp] = y;
}

void	cal_v(t_vars *vars, int start_x, int end_x)
{
	int	xp;
	int	yp;
	int	R2;

	R2 = RADIUS * RADIUS;
	xp = start_x - 1;
	while (++xp < end_x)
	{
		yp = -1;
		while (++yp < HEIGHT)
		{
			if (vars->type == JULIA)
				julia(vars, xp, yp, R2);
			else if (vars->type == MANDELBROT)
				mandel(vars, xp, yp, R2);
		}
	}
}

void	cal_h(t_vars *vars, int start_y, int end_y)
{
	int	xp;
	int	yp;
	int	R2;

	R2 = RADIUS * RADIUS;
	yp = start_y - 1;
	while (++yp < end_y)
	{
		xp = -1;
		while (++xp < WIDTH)
		{
			if (vars->type == JULIA)
				julia(vars, xp, yp, R2);
			else if (vars->type == MANDELBROT)
				mandel(vars, xp, yp, R2);
		}
	}
}
