/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/17 11:53:22 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

void	cal(t_vars *vars, t_viewport *vp)
{
	double   x;
	double   y;
	double   x0;
	double   y0;
	double   x2;
	double   y2;
	double   xtemp;
	int	xp;
	int	yp;
	int	i;
	int	R2;

	R2 = RADIUS * RADIUS;
	xp = -1;
	while (++xp < WIDTH)
	{
		yp = -1;
		while (++yp < HEIGHT)
		{
			x0 = vp->left + vp->scale * xp;
			y0 = vp->top  - vp->scale * yp;
			i = 0;
			if (vars->type == JULIA)
			{
				x = x0;
				y = y0;
				while (x * x + y * y < R2 && ++i < vars->max_iter)
				{
					xtemp = x;
					x = x * x - y * y + 0.285;
					y = 2 * xtemp * y + 0.01;
				}
				vp->iters[xp][yp] = i;
			}
			else if (vars->type == MANDELBROT)
			{
				x = 0.0;
				y = 0.0;
				x2 = 0.0;
				y2 = 0.0;
				while (x2 + y2 < R2 && ++i < vars->max_iter)
				{
					y = 2 * x * y + y0;
					x = x2 - y2 + x0;
					x2 = x * x;
					y2 = y * y;
				}
				vp->iters[xp][yp] = i;
				vp->xn[xp][yp] = x;
				vp->yn[xp][yp] = y;
			}
		}
	}
}
