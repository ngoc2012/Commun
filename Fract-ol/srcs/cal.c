/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/27 21:51:03 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	julia(t_vars *vars, int xp, int yp, int R2)
{
	t_coor_d	p;
	t_coor_d	p0;
	t_coor_d	p2;
	int			i;

	p0.x = vars->left + vars->scale * xp;
	p0.y = vars->top - vars->scale * yp;
	p.x = p0.x;
	p.y = p0.y;
	p2.x = p.x * p.x;
	p2.y = p.y * p.y;
	i = 0;
	while (p2.x + p2.y < R2 && ++i < vars->max_iter)
	{
		p.y = 2 * p.x * p.y + vars->cy;
		p.x = p2.x - p2.y + vars->cx;
		p2.x = p.x * p.x;
		p2.y = p.y * p.y;
	}
	vars->iters[xp][yp] = i;
	vars->xn[xp][yp] = p.x;
	vars->yn[xp][yp] = p.y;
}

void	mandel(t_vars *vars, int xp, int yp, int R2)
{
	t_coor_d	p;
	t_coor_d	p0;
	t_coor_d	p2;
	int			i;

	p0.x = vars->left + vars->scale * xp;
	p0.y = vars->top - vars->scale * yp;
	p.x = 0.0;
	p.y = 0.0;
	p2.x = 0.0;
	p2.y = 0.0;
	i = 0;
	while (p2.x + p2.y < R2 && ++i < vars->max_iter)
	{
		p.y = 2 * p.x * p.y + p0.y;
		p.x = p2.x - p2.y + p0.x;
		p2.x = p.x * p.x;
		p2.y = p.y * p.y;
	}
	vars->iters[xp][yp] = i;
	vars->xn[xp][yp] = p.x;
	vars->yn[xp][yp] = p.y;
}

void	burn(t_vars *vars, int xp, int yp, int R2)
{
	t_coor_d	p;
	t_coor_d	z;
	t_coor_d	z2;
	int			i;

	p.x = vars->left + vars->scale * xp;
	p.y = vars->top - vars->scale * yp;
	z.x = p.x;
	z.y = p.y;
	z2.x = z.x * z.x;
	z2.y = z.y * z.y;
	i = 0;
	while (z2.x + z2.y < R2 && ++i < vars->max_iter)
	{
		z.y = fabs(2 * z.x * z.y) + p.y;
		z.x = z2.x - z2.y + p.x;
		z2.x = z.x * z.x;
		z2.y = z.y * z.y;
	}
	vars->iters[xp][yp] = i;
	vars->xn[xp][yp] = z.x;
	vars->yn[xp][yp] = z.y;
}

void	cal(t_vars *vars, int xp, int yp, int R2)
{
	if (vars->type == e_julia)
		julia(vars, xp, yp, R2);
	else if (vars->type == e_mandelbrot)
		mandel(vars, xp, yp, R2);
	else if (vars->type == e_burn)
		burn(vars, xp, yp, R2);
}

void	cal_v(t_vars *vars, int start_x, int end_x)
{
	int	xp;
	int	yp;
	int	r2;

	r2 = RADIUS * RADIUS;
	xp = start_x - 1;
	while (++xp < end_x)
	{
		yp = -1;
		while (++yp < HEIGHT)
		{
			if (vars->type == e_julia)
				julia(vars, xp, yp, r2);
			else if (vars->type == e_mandelbrot)
				mandel(vars, xp, yp, r2);
			else if (vars->type == e_burn)
				burn(vars, xp, yp, r2);
		}
	}
}
