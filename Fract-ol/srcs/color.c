/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/17 23:36:44 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

void	colors(t_vars *vars, t_viewport *vp)
{
	int	xp;
	int	yp;
	int	i;
	int	j;
	double	x;
	double	y;
	double	xtemp;
	double	len;
	double	smooth;
	double	R2;

	R2 = RADIUS * RADIUS;
	xp = -1;
	while (++xp < WIDTH)
	{
		yp = -1;
		while (++yp < HEIGHT)
		{
			i = vp->iters[xp][yp];
			x = vp->xn[xp][yp];
			y = vp->yn[xp][yp];
			len = sqrt(x * x + y * y);
			if (vars->type == JULIA)
			{
				smooth = exp(-len);
				j = -1;
				while (++j < vars->max_iter && x * x + y * y <= R2)
				{
					xtemp = x;
					x = vars->cx + x * x - y * y;
					y = vars->cy + xtemp * y * 2.0;
					smooth = exp(-sqrt(x * x + y * y));
				}
			}
			else if (vars->type == MANDELBROT)
			{
				if (i < vars->max_iter)
					smooth = (double) i + 1.0 - log(log(len) / log(RADIUS)) / log(2.0);
				else
					smooth = (double) i;
			}
			else
				vp->colors[xp][yp] = (double) i ;
			vp->colors[xp][yp] = smooth / (double) vars->max_iter;
		}
	}
}
