/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/19 18:31:05 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

void	*render(void *th0)
{
	VAR_TYPE   x;
	VAR_TYPE   y;
	VAR_TYPE   x0;
	VAR_TYPE   y0;
	VAR_TYPE   x2;
	VAR_TYPE   y2;
	int	xp;
	int	yp;
	int	i;
	int	R2;
	int	width;
	t_thread	*th;
	t_vars		*vars;
       	t_viewport	*vp;

	th = (t_thread *)th0;
	vars = th->vars;
	vp = th->vp;
	width = WIDTH / THREADS;
	R2 = RADIUS * RADIUS;
	xp = width * th->id - 1;
	//ft_printf("width = %d\n", width);
	//ft_printf("id = %d\n", th->id);
	//ft_printf("x_start = %d, x_end = %d\n", xp + 1, width * (th->id + 1));
	while (++xp < (width * (th->id + 1)))
	{
		//ft_printf("x = %d\n", xp);
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
				x2 = x * x;
				y2 = y * y;
				while (x2 + y2 < R2 && ++i < vars->max_iter)
				{
					y = 2 * x * y + vars->cy;
					x = x2 - y2 + vars->cx;
					x2 = x * x;
					y2 = y * y;
				}
				vp->iters[xp][yp] = i;
				vp->xn[xp][yp] = x;
				vp->yn[xp][yp] = y;
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
	return (NULL);
}

void	cal(t_vars *vars, t_viewport *vp)
{
	int	i;
	//int	xp;
	//int	yp;
	t_thread	threads[THREADS];
	//pthread_t	th[THREADS];

	i = -1;
	while (++i < THREADS)
	{
		threads[i].vars = vars;
		threads[i].vp = vp;
		threads[i].id = i;
		//pthread_create(&th[i], NULL, render, &(threads[i]));
		render(&threads[i]);
	}
	//i = -1;
	//while (++i < THREADS)
	//	pthread_join(th[i], NULL);
	//ft_printf("max iter = \n", vars->max_iter);
	//sleep(1);
	/*
	xp = -1;
	//ft_printf("width = %d\n", width);
	//ft_printf("id = %d\n", th->id);
	while (++xp < WIDTH)
	{
		//ft_printf("x = %d\n", xp);
		yp = -1;
		while (++yp < HEIGHT)
		{
			vp->iters[xp][yp] = 0;
			vp->xn[xp][yp] = 0;
			vp->yn[xp][yp] = 0;
		}
	}
	*/
}

void	cal2(t_vars *vars, t_viewport *vp)
{
	int	i;
	t_thread	threads[THREADS];
	pthread_t	th[THREADS];

	i = -1;
	while (++i < THREADS)
	{
		threads[i].vars = vars;
		threads[i].vp = vp;
		threads[i].id = i;
		pthread_create(&th[i], NULL, render, &(threads[i]));
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(th[i], NULL);
}

void	cal1(t_vars *vars, t_viewport *vp)
{
	VAR_TYPE   x;
	VAR_TYPE   y;
	VAR_TYPE   x0;
	VAR_TYPE   y0;
	VAR_TYPE   x2;
	VAR_TYPE   y2;
	int	xp;
	int	yp;
	int	i;
	int	R2;

	R2 = RADIUS * RADIUS;
	xp = -1;
	//ft_printf("width = %d\n", width);
	//ft_printf("id = %d\n", th->id);
	while (++xp < WIDTH)
	{
		//ft_printf("x = %d\n", xp);
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
				x2 = x * x;
				y2 = y * y;
				while (x2 + y2 < R2 && ++i < vars->max_iter)
				{
					y = 2 * x * y + vars->cy;
					x = x2 - y2 + vars->cx;
					x2 = x * x;
					y2 = y * y;
				}
				vp->iters[xp][yp] = i;
				vp->xn[xp][yp] = x;
				vp->yn[xp][yp] = y;
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
