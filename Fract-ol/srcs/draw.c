/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/19 22:48:57 by ngoc             ###   ########.fr       */
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

int	get_color(float value, int i)
{
	int		above;
	int		under;
	int		dims[N_PALLETS] = {11, 11, 5, 6, 3, 7, 5};
 	float	pallet[N_PALLETS][12][3] =
	{
		{
			{  2.,   2.,  10.},
			{  5.,  22.,  90.},
			{  2.,  61., 177.},
			{215.,  72.,  38.},
			{146.,  49.,  26.},
			{ 80.,  27.,  14.},
			{146.,  49.,  26.},
			{215.,  72.,  38.},
			{  2.,  61., 177.},
			{  5.,  22.,  90.},
			{  2.,   2.,  10.},
		},
		{
			{255., 235.,   0.},
			{252.,   0.,  25.},
			{  1., 255.,  79.},
			{255.,   1., 215.},
			{ 86.,   0., 204.},
			{  0., 237., 245.},
			{ 86.,   0., 204.},
			{255.,   1., 215.},
			{  1., 255.,  79.},
			{252.,   0.,  25.},
			{255., 235.,   0.}
		},
		{
			{ 20.,   0.,   0.},
			{255.,  20.,   0.},
			{255., 200.,   0.},
			{255.,  20.,   0.},
			{ 20.,   0.,   0.}
		},
		{
			{  0.,   7., 100.},
			{ 32., 107., 203.},
			{237., 255., 255.},
			{255., 170.,   0.},
			{  0.,   2.,   0.},
			{  0.,   7., 100.}
		},
		{
			{  0.,   0.,   0.},
			{255., 255., 255.},
			{  0.,   0.,   0.}
		},
		{
			{255.,   0.,   0.},
			{255., 255.,   0.},
			{  0., 255.,   0.},
			{  0., 255., 255.},
			{  0.,   0., 255.},
			{255.,   0., 255.},
			{255.,   0.,   0.}
		},
		{
			{  0.,   0.,   0.},
			{  0.,   0., 200.},
			{255., 255., 255.},
			{  0.,   0., 200.},
			{  0.,   0.,   0.}
		}
	};

	if (value == 0.0)
		return (create_trgb(1.0, pallet[i][0][0], pallet[i][0][1], pallet[i][0][2])); 
	if (value == 1.0)
		return (create_trgb(1.0, pallet[i][dims[i]][0], pallet[i][dims[i]][1], pallet[i][dims[i]][2])); 
	above = (int) (value * (float) dims[i]);
	if (above == dims[i])
		above = dims[i] - 1;
	if (above == 0)
		above = 1;
	under = above - 1;
	float	p;
	p = value * ((float) dims[i] - 1.0) - (float) under;
	if (value > 1.0)
		printf("value = %f, p = %f, above = %d, under = %d, RGB =  %d, %d, %d\n", value, p, above, under,
		(int) (pallet[i][under][0] + p * (pallet[i][above][0] - pallet[i][under][0])),
		(int) (pallet[i][under][1] + p * (pallet[i][above][1] - pallet[i][under][1])),
		(int) (pallet[i][under][2] + p * (pallet[i][above][2] - pallet[i][under][2])));
	return (create_trgb(1.0,
	(int) (pallet[i][under][0] + p * (pallet[i][above][0] - pallet[i][under][0])),
	(int) (pallet[i][under][1] + p * (pallet[i][above][1] - pallet[i][under][1])),
	(int) (pallet[i][under][2] + p * (pallet[i][above][2] - pallet[i][under][2]))));
}

void	draw(t_vars *vars, t_img *img)
{
	VAR_TYPE	x;
	VAR_TYPE	y;
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
			x = vars->left + vars->scale * (VAR_TYPE) xp;
			y = vars->top  - vars->scale * (VAR_TYPE) yp;
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
				my_mlx_pixel_put(img, xp, yp, get_color((float) vp0->colors[xp0][yp0], vars->pallet));
			}
		}
	}
	//printf("vars->scale = %f, vp0->scale = %f\n", vars->scale, vp0->scale);
	//printf("vars->left = %f, vp0->left = %f\n", vars->left, vp0->left);
	//printf("vars->top = %f, vp0->top = %f\n", vars->top, vp0->top);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
}
