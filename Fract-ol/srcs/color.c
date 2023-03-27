/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/27 21:43:53 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

VAR_TYPE	color_julia1(t_vars *vars, int xp, int yp)
{
	t_coor		p;
	t_coor		p2;

	p.x = vars->xn[xp][yp];
	p.y = vars->yn[xp][yp];
	p2.x = p.x * p.x;
	p2.y = p.y * p.y;
	return (sqrt(p2.x + p2.y));
}

VAR_TYPE	color_julia(t_vars *vars, int xp, int yp, int R2)
{
	int			j;
	t_coor_d	p;
	t_coor_d	p2;
	VAR_TYPE	xtemp;
	VAR_TYPE	s;

	p.x = vars->xn[xp][yp];
	p.y = vars->yn[xp][yp];
	p2.x = p.x * p.x;
	p2.y = p.y * p.y;
	s = exp(-sqrt(p2.x + p2.y));
	j = -1;
	while (++j < vars->max_iter && p2.x + p2.y <= R2)
	{
		xtemp = p.x;
		p.x = vars->cx + p2.x - p2.y;
		p.y = vars->cy + xtemp * p.y * 2.0;
		p2.x = p.x * p.x;
		p2.y = p.y * p.y;
		s += exp(-sqrt(p2.x + p2.y));
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
		return ((VAR_TYPE) vars->iters[xp][yp] + 1.0
			- log(log(sqrt(x * x + y * y)) * vars->log_r) * vars->log_2);
	return ((VAR_TYPE) vars->iters[xp][yp]);
}

void	colors(t_vars *vars, int xp, int yp, int R2)
{
	VAR_TYPE	s;

	if (vars->smooth == 1 && vars->type == e_julia)
		s = color_mandel(vars, xp, yp);
	else if (vars->smooth == 2 && vars->type == e_julia)
		s = color_julia(vars, xp, yp, R2);
	else if (vars->smooth && (vars->type == e_mandelbrot || vars->type == e_burn))
		s = color_mandel(vars, xp, yp);
	else
		s = (VAR_TYPE) vars->iters[xp][yp];
	vars->colors[xp][yp] = s / (VAR_TYPE) vars->max_iter;
}

void	colors_v(t_vars *vars, int start_x, int end_x)
{
	int			xp;
	int			yp;
	VAR_TYPE	r2;

	r2 = RADIUS * RADIUS;
	xp = start_x - 1;
	while (++xp < end_x)
	{
		yp = -1;
		while (++yp < HEIGHT)
			colors(vars, xp, yp, r2);
	}
}
