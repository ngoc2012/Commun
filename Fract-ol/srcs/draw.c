/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/26 10:37:16 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	create_trgb(unsigned char t, unsigned char r,
		unsigned char g, unsigned char b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

VAR_TYPE	get_pallets(int n, int x, int y)
{
 	VAR_TYPE	pallet[N_PALLETS][12][3] =
	{{{  2.,   2.,  10.}, {  5.,  22.,  90.}, {  2.,  61., 177.},
	{215.,  72.,  38.}, {146.,  49.,  26.}, { 80.,  27.,  14.},
	{146.,  49.,  26.}, {215.,  72.,  38.}, {  2.,  61., 177.},
	{  5.,  22.,  90.}, {  2.,   2.,  10.}},
	{{255., 235.,   0.}, {252.,   0.,  25.}, {  1., 255.,  79.},
	{255.,   1., 215.}, { 86.,   0., 204.}, {  0., 237., 245.},
	{ 86.,   0., 204.}, {255.,   1., 215.}, {  1., 255.,  79.},
	{252.,   0.,  25.}, {255., 235.,   0.}},
	{{ 20.,   0.,   0.}, {255.,  20.,   0.}, {255., 200.,   0.},
	{255.,  20.,   0.}, { 20.,   0.,   0.}},
	{{  0.,   7., 100.}, { 32., 107., 203.}, {237., 255., 255.},
	{255., 170.,   0.}, {  0.,   2.,   0.}, {  0.,   7., 100.}},
	{{  0.,   0.,   0.}, {255., 255., 255.}, {  0.,   0.,   0.}},
	{{255.,   0.,   0.}, {255., 255.,   0.}, {  0., 255.,   0.},
	{  0., 255., 255.}, {  0.,   0., 255.}, {255.,   0., 255.},
	{255.,   0.,   0.}},
	{{  0.,   0.,   0.}, {  0.,   0., 200.}, {255., 255., 255.},
	{  0.,   0., 200.}, {  0.,   0.,   0.} }};
	return (pallet[n][x][y]);
}

int	get_color(VAR_TYPE value, int i)
{
	int		above;
	int		under;
	int		dims[N_PALLETS] = {11, 11, 5, 6, 3, 7, 5};

	if (value == 0.0)
		return (1 << 24); 
	if (value == 1.0)
		return (create_trgb(1.0, get_pallets(i, dims[i], 0), get_pallets(i, dims[i], 1), get_pallets(i, dims[i], 2))); 
	above = (int) (value * (VAR_TYPE) dims[i]);
	if (above == dims[i])
		above = dims[i] - 1;
	if (above == 0)
		above = 1;
	under = above - 1;
	VAR_TYPE	p;
	p = value * ((VAR_TYPE) dims[i] - 1.0) - (VAR_TYPE) under;
	return (create_trgb(1,
	(unsigned char) (get_pallets(i, under, 0) + p * (get_pallets(i, above, 0) - get_pallets(i, under, 0))),
	(unsigned char) (get_pallets(i, under, 1) + p * (get_pallets(i, above, 1) - get_pallets(i, under, 1))),
	(unsigned char) (get_pallets(i, under, 2) + p * (get_pallets(i, above, 2) - get_pallets(i, under, 2)))));
}

//bits_per_pixel = 32
void	draw(t_vars *vars, t_img *img)
{
	int	xp;
	int	yp;
	int	*addr;

	addr = (int *)img->addr;
	yp = -1;
	while (++yp < HEIGHT)
	{
		xp = -1;
		while (++xp < WIDTH)
			*(addr++) = get_color(vars->colors[xp][yp], vars->pallet);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}
