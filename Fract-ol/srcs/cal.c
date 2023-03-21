/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/20 16:57:19 by minh-ngu         ###   ########.fr       */
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


void	*render_th_v(void *th0)
{
	int	xp;
	int	yp;
	int	R2;
	int	width;
	t_thread	*th;
	t_vars		*vars;

	th = (t_thread *)th0;
	vars = th->vars;
	width = WIDTH / THREADS;
	R2 = RADIUS * RADIUS;
	xp = width * th->id - 1;
	while (++xp < (width * (th->id + 1)))
	{
		yp = th->start - 1;
		while (++yp < th->end)
		{
			if (vars->type == JULIA)
				julia(vars, xp, yp, R2);
			else if (vars->type == MANDELBROT)
				mandel(vars, xp, yp, R2);
		}
	}
	return (NULL);
}

void	*render_th_h(void *th0)
{
	int	xp;
	int	yp;
	int	R2;
	int	height;
	t_thread	*th;
	t_vars		*vars;

	th = (t_thread *)th0;
	vars = th->vars;
	height = HEIGHT / THREADS;
	R2 = RADIUS * RADIUS;
	yp = height * th->id - 1;
	while (++yp < (height * (th->id + 1)))
	{
		xp = th->start - 1;
		while (++xp < th->end)
		{
			if (vars->type == JULIA)
				julia(vars, xp, yp, R2);
			else if (vars->type == MANDELBROT)
				mandel(vars, xp, yp, R2);
		}
	}
	return (NULL);
}

void	cal_th(t_vars *vars, int start, int end, char direction)
{
	int	i;
	t_thread	threads[THREADS];
	pthread_t	th[THREADS];

	i = -1;
	while (++i < THREADS)
	{
		threads[i].vars = vars;
		threads[i].id = i;
		threads[i].start = start;
		threads[i].end = end;
		if (direction == 'v')
			pthread_create(&th[i], NULL, render_th_v, &(threads[i]));}
	i = -1;
	while (++i < THREADS)
		pthread_join(th[i], NULL);
}

void	cal(t_vars *vars)
{
	int	xp;
	int	yp;
	int	R2;

	R2 = RADIUS * RADIUS;
	xp = -1;
	while (++xp < WIDTH)
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
