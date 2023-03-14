/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/14 11:21:28 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_color(float value)
{
	int		above;
	int		under;
	int		dim = 6;
 	float	pallet[6][4] = {
		{  0.,   7., 100., 1.},
		{ 32., 107., 203., 1.},
		{237., 255., 255., 1.},
		{255., 170.,   0., 1.},
		{  0.,   2.,   0., 1.},
		{  0.,   7., 100., 1.}
	};
//		{ 20.,   0.,   0., 1.},
//		{255.,  20.,   0., 1.},
//		{255., 200.,   0., 1.},
//		{255.,  20.,   0., 1.},
//		{ 20.,   0.,   0., 1.}
//	};
//{  0.,   0.,   0., 1.},
//{  0.,   0., 200., 1.},
//{255., 255., 255., 1.},
//{  0.,   0., 200., 1.},
//{  0.,   0.,   0., 1.}
//	};

	above = (int) (value * (float) dim);
	if (above == dim)
		above = dim - 1;
	under = above - 1;
	float	p;
	p = value * (float) dim - (float) under;
	return (create_trgb((int) pallet[under][0] + p * (pallet[above][0] - pallet[under][0]),
	(int) pallet[under][1] + p * (pallet[above][1] - pallet[under][1]),
	(int) pallet[under][2] + p * (pallet[above][2] - pallet[under][2]),
	(int) pallet[under][3] + p * (pallet[above][3] - pallet[under][3])));
}

void	draw(t_vars *vars, t_img *img)
{
	double   x;
	double   y;
	double   x0;
	double   y0;
	double   xtemp;
	int	xp;
	int	yp;
	int	i;
	int	max_i;
	int	min_i;

	if (vars->in_process)
	       return ;
	max_i = 0;
	min_i = MAX_ITER;
	xp = 0;
	while (++xp < vars->w)
	{
		yp = 0;
		while (++yp < vars->h)
		{
			x0 = vars->scale * xp - vars->left - vars->cx;
			y0 = vars->scale * yp - vars->top - vars->cy;
			i = -1;
			if (vars->type == JULIA)
			{
				x = x0;
				y = y0;
				while (x * x + y * y < 4 && ++i < vars->max_iter)
				{
					xtemp = x;
					x = x * x - y * y - 1;
					y = 2 * xtemp * y;
				}
			}
			else if (vars->type == MANDELBROT)
			{
				x = 0.0;
				y = 0.0;
				while (x * x + y * y < 4 && ++i < vars->max_iter)
				{
					xtemp = x * x - y * y + x0;
					y = 2 * x * y + y0;
					x = xtemp;
				}
			}
			//v = math.pow(math.pow(i/max_iter, S) * N, 1.5) % N;
			//v = i / max_iter;
			//my_mlx_pixel_put(&img-> xp, yp, create_trgb(0, v * 255, v * 255, v * 255));
			//ft_printf("i = %d\n", i);
			if (i < min_i)
				min_i = i;
			if (i > max_i)
				max_i = i;
			my_mlx_pixel_put(img, xp, yp, get_color((float) (i - vars->min_iter) / (vars->max_iter- vars->min_iter)));
		}
	}
	vars->in_process = 0;
	vars->min_iter = min_i;
	if (max_i <= MAX_ITER)
		vars->max_iter = max_i;
	ft_printf("max_iter = %d, min_iter = %d\n", vars->max_iter, vars->min_iter);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
}
