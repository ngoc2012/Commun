/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/19 18:30:40 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

void	colors(t_vars *vars, t_viewport *vp)
{
	int	xp;
	int	yp;
	int	i;
	int	j;
	VAR_TYPE	x;
	VAR_TYPE	y;
	VAR_TYPE	xtemp;
	VAR_TYPE	len;
	VAR_TYPE	smooth;
	VAR_TYPE	R2;

	R2 = RADIUS * RADIUS;
	xp = -1;
	while (++xp < WIDTH)
	{
		yp = -1;
		while (++yp < HEIGHT)
		{
			i = vp->iters[xp][yp];
			if (vars->smooth)
			{
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
						smooth += exp(-sqrt(x * x + y * y));
					}
				}
				else if (vars->type == MANDELBROT)
				{
					if (i < vars->max_iter)
						smooth = (VAR_TYPE) i + 1.0 - log(log(len) / log(RADIUS)) / log(2.0);
					else
						smooth = (VAR_TYPE) i;
				}
				else
					vp->colors[xp][yp] = (VAR_TYPE) i ;
				vp->colors[xp][yp] = smooth / (VAR_TYPE) vars->max_iter;
			}
			else
				vp->colors[xp][yp] = (VAR_TYPE) i / (VAR_TYPE) vars->max_iter;
		}
	}
}
