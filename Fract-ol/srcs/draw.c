/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/17 09:05:32 by minh-ngu         ###   ########.fr       */
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
		// Fire
//		{ 20.,   0.,   0., 1.},
//		{255.,  20.,   0., 1.},
//		{255., 200.,   0., 1.},
//		{255.,  20.,   0., 1.},
//		{ 20.,   0.,   0., 1.}
//	};
		{  0.,   7., 100., 1.},
		{ 32., 107., 203., 1.},
		{237., 255., 255., 1.},
		{255., 170.,   0., 1.},
		{  0.,   2.,   0., 1.},
		{  0.,   7., 100., 1.}
	};

//		{0., 0.,   0., 1.},
//		{255.,  255.,   255., 1.},
//		{ 0.,   0.,   0., 1.}
//	};



//		{255.,   0.,   0., 1.},
//		{255., 255.,   0., 1.},
//		{  0., 255.,   0., 1.},
//		{  0., 255., 255., 1.},
//		{  0.,   0., 255., 1.},
//		{255.,   0., 255., 1.},
//		{255.,   0.,   0., 1.}
//	};
//{  0.,   0.,   0., 1.},
//{  0.,   0., 200., 1.},
//{255., 255., 255., 1.},
//{  0.,   0., 200., 1.},
//{  0.,   0.,   0., 1.}
//	};

	//if (value > 1.0)
	//	value = 1.0;
	above = (int) (value * (float) dim);
	if (above == dim)
		above = dim - 1;
	if (above == 0)
		above = 1;
	under = above - 1;
	float	p;
	p = value * ((float) dim - 1.0) - (float) under;
	if (value > 1.0)
		printf("value = %f, p = %f, above = %d, under = %d, RGB =  %d, %d, %d\n", value, p, above, under,
		(int) (pallet[under][0] + p * (pallet[above][0] - pallet[under][0])),
		(int) (pallet[under][1] + p * (pallet[above][1] - pallet[under][1])),
		(int) (pallet[under][2] + p * (pallet[above][2] - pallet[under][2])));
	return (create_trgb(1.0,
	(int) pallet[under][0] + p * (pallet[above][0] - pallet[under][0]),
	(int) pallet[under][1] + p * (pallet[above][1] - pallet[under][1]),
	(int) pallet[under][2] + p * (pallet[above][2] - pallet[under][2])));
}

void	draw(t_vars *vars, t_img *img)
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
	int	max_i;
	int	min_i;
	//int	total;
	int	NumIterationsPerPixel[MAX_ITER];
	int	**IterationCounts;
	//double	**hue;
	//double	max_hue;

	if (vars->in_process)
	       return ;
	vars->in_process++;
	//g_process++;
	i = -1;
	while (++i < MAX_ITER)
		NumIterationsPerPixel[i] = 0;
	IterationCounts = creat_vp(vars->h, vars->w);
	//hue = creat_vp_d(vars->h, vars->w);
	max_i = 0;
	min_i = vars->max_iter;
	xp = 0;
	while (++xp < vars->w)
	{
		yp = 0;
		while (++yp < vars->h)
		{
			x0 = vars->scale * xp - vars->left - vars->cx;
			y0 = vars->scale * yp - vars->top - vars->cy;
			i = 0;
			if (vars->type == JULIA)
			{
				x = x0;
				y = y0;
				while (x * x + y * y < 1600 && ++i < vars->max_iter)
				{
					xtemp = x;
					x = x * x - y * y + 0.285;
					y = 2 * xtemp * y + 0.01;
				}
				IterationCounts[xp][yp] = i;
				NumIterationsPerPixel[i]++;
			}
			else if (vars->type == MANDELBROT)
			{
				x = 0.0;
				y = 0.0;
				x2 = 0.0;
				y2 = 0.0;
				while (x2 + y2 < 1600 && ++i < vars->max_iter)
				{
					y = 2 * x * y +y0;
					x = x2 - y2 + x0;
					x2 = x * x;
					y2 = y * y;
					//xtemp = x * x - y * y + x0;
					//y = 2 * x * y + y0;
					//x = xtemp;
				}
				IterationCounts[xp][yp] = i;
				NumIterationsPerPixel[i]++;
			}
			//v = math.pow(math.pow(i/max_iter, S) * N, 1.5) % N;
			//v = i / max_iter;
			//my_mlx_pixel_put(&img-> xp, yp, create_trgb(0, v * 255, v * 255, v * 255));
			//ft_printf("i = %d\n", i);

			//double logzn;
			//double nu;
			if (i < vars->max_iter)
			{
				//logzn = log(x * x + y * y) / 2;
				//nu = log(logzn) / log(2);
				i = i + 1 - log(log(sqrt(x * x + y * y)) / log(40)) / log(2);
			}

			//my_mlx_pixel_put(img, xp, yp, get_color((float) IterationCounts[xp][yp] / vars->max_iter));
			my_mlx_pixel_put(img, xp, yp, get_color((float) i / vars->max_iter));
			if (i < min_i)
				min_i = i;
			if (i > max_i)
				max_i = i;
		}
	}
	/*
	total = 0;
	i = -1;
	while (++i < vars->max_iter)
		total += NumIterationsPerPixel[i];
	max_hue = 0.0;
	xp = 0;
	while (++xp < vars->w)
	{
		yp = 0;
		while (++yp < vars->h)
		{
			hue[xp][yp] = 0.0;
			i = -1;
			while(++i <= IterationCounts[xp][yp])
				hue[xp][yp] += NumIterationsPerPixel[i] / total;
			if (hue[xp][yp] > max_hue)
				max_hue = hue[xp][yp];
		}
	}
	xp = 0;
	while (++xp < vars->w)
	{
		yp = 0;
		while (++yp < vars->h)
		{
			//my_mlx_pixel_put(img, xp, yp, get_color((float) hue[xp][yp]));
			my_mlx_pixel_put(img, xp, yp, get_color((float) IterationCounts[xp][yp] / vars->max_iter));
			//printf("%f\n", hue[xp][yp]);
		}
	}
	*/
	vars->in_process--;
	//g_process--;
	vars->min_iter = min_i;
	if (max_i <= MAX_ITER)
		vars->max_iter = max_i;
	del_vp(IterationCounts, vars->w);
	//del_vp_d(hue, vars->w);
	//ft_printf("max_iter = %d, min_iter = %d\n", vars->max_iter, vars->min_iter);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
}
