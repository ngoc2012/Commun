/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/17 22:18:10 by ngoc             ###   ########.fr       */
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
	if (value == 0.0)
		return (create_trgb(1.0, pallet[0][0], pallet[0][1], pallet[0][2])); 
	if (value == 1.0)
		return (create_trgb(1.0, pallet[dim][0], pallet[dim][1], pallet[dim][2])); 
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
	(int) (pallet[under][0] + p * (pallet[above][0] - pallet[under][0])),
	(int) (pallet[under][1] + p * (pallet[above][1] - pallet[under][1])),
	(int) (pallet[under][2] + p * (pallet[above][2] - pallet[under][2]))));
}

void	draw(t_vars *vars, t_img *img)
{
	double	x;
	double	y;
	int	xp;
	int	yp;
	int	xp0;
	int	yp0;
	t_viewport	*vp0;

	vp0 = &vars->vp0; 
	xp = -1;
	while (++xp < WIDTH)
	{
		yp = -1;
		while (++yp < HEIGHT)
		{
			x = vars->left + vars->scale * (double) xp;
			y = vars->top  - vars->scale * (double) yp;
			if (x <= vp0->left || x >= vp0->right
				|| y <= vp0->bottom || y >= vp0->top )
				my_mlx_pixel_put(img, xp + 1, yp + 1, 0.0);
			else
			{
				xp0 = (int) ((x - vp0->left) / vp0->scale); 
				yp0 = (int) ((vp0->top - y) / vp0->scale); 
				if (xp0 == WIDTH)
					xp0--;
				if (yp0 == HEIGHT)
					yp0--;
				my_mlx_pixel_put(img, xp, yp, get_color((float) vp0->colors[xp0][yp0]));
			}
		}
	}
	//printf("vars->scale = %f, vp0->scale = %f\n", vars->scale, vp0->scale);
	//printf("vars->left = %f, vp0->left = %f\n", vars->left, vp0->left);
	//printf("vars->top = %f, vp0->top = %f\n", vars->top, vp0->top);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
}
