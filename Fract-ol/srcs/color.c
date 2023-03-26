/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/26 10:37:25 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

VAR_TYPE	color_julia(t_vars *vars, int xp, int yp, int R2)
{
	int	j;
	VAR_TYPE	x;
	VAR_TYPE	y;
	VAR_TYPE	x2;
	VAR_TYPE	y2;
	VAR_TYPE	xtemp;
	VAR_TYPE	s;

	x = vars->xn[xp][yp];
	y = vars->yn[xp][yp];
	x2 = x * x;
	y2 = y * y;
	s = exp(-sqrt(x2 + y2));
	j = -1;
	while (++j < vars->max_iter && x2 + y2 <= R2)
	{
		xtemp = x;
		x = vars->cx + x2 - y2;
		y = vars->cy + xtemp * y * 2.0;
		x2 = x * x;
		y2 = y * y;
		s += exp(-sqrt(x2 + y2));
	}
	return (s);
}

VAR_TYPE	color_mandel(t_vars *vars, int xp, int yp)
{
	VAR_TYPE	x;
	VAR_TYPE	y;

	x = vars->xn[xp][yp];
	y = vars->yn[xp][yp];
	if (vars->iters[xp][yp] < vars->max_iter)
		return ((VAR_TYPE) vars->iters[xp][yp] + 1.0 - log(log(sqrt(x * x + y * y)) / log(RADIUS)) / log(2.0));
	return ((VAR_TYPE) vars->iters[xp][yp]);
}

void	colors(t_vars *vars, int xp, int yp, int R2)
{
	VAR_TYPE	s;

	if (vars->smooth && vars->type == e_julia)
		s = color_julia(vars, xp, yp, R2);
	else if (vars->smooth && vars->type == e_mandelbrot)
		s = color_mandel(vars, xp, yp);
	else
		s = (VAR_TYPE) vars->iters[xp][yp];
	vars->colors[xp][yp] = s / (VAR_TYPE) vars->max_iter;
}

void	colors_v(t_vars *vars, int start_x, int end_x)
{
	int	xp;
	int	yp;
	VAR_TYPE	R2;

	R2 = RADIUS * RADIUS;
	xp = start_x - 1;
	while (++xp < end_x)
	{
		yp = -1;
		while (++yp < HEIGHT)
			colors(vars, xp, yp, R2);
	}
}
