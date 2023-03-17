/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/17 12:03:38 by minh-ngu         ###   ########.fr       */
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

void	draw(t_vars *vars, t_img *img, t_viewport *vp)
{
	//double	x;
	//double	y;
	int	xp;
	int	yp;
	int	i;
	//double	smooth;

	xp = -1;
	while (++xp < WIDTH)
	{
		yp = -1;
		while (++yp < HEIGHT)
		{
			//x0 = vp->left + vp->scale * xp;
			//y0 = vp->top  - vp->scale * yp;
			i = vp->iters[xp][yp];
			//x = vp->xn[xp][yp];
			//y = vp->yn[xp][yp];
			//if (vars->type == JULIA)
			//{
			//	smooth = exp(i);
			//	i = smooth;
			//}
			//else if (vars->type == MANDELBROT)
			//{
			//	if (i < vars->max_iter)
			//		i = i + 1 - log(log(sqrt(x * x + y * y)) / log(RADIUS)) / log(2);
			//}
			my_mlx_pixel_put(img, xp + 1, yp + 1, get_color((float) i / vars->max_iter));
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
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
}
