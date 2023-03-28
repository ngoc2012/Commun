/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/28 22:14:20 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_pallets(t_vars *vars)
{
	vars->pallets[0] = (t_pallet){.d = 11,
		.val = {{2., 2., 10.}, {5., 22., 90.}, {2., 61., 177.},
	{215., 72., 38.}, {146., 49., 26.}, {80., 27., 14.},
	{146., 49., 26.}, {215., 72., 38.}, {2., 61., 177.},
	{5., 22., 90.}, {2., 2., 10.}}};
	vars->pallets[1] = (t_pallet){.d = 11,
		.val = {{255., 235., 0.}, {252., 0., 25.}, {1., 255., 79.},
	{255., 1., 215.}, {86., 0., 204.}, {0., 237., 245.},
	{86., 0., 204.}, {255., 1., 215.}, {1., 255., 79.},
	{252., 0., 25.}, {255., 235., 0.}}};
	vars->pallets[2] = (t_pallet){.d = 5,
		.val = {{20., 0., 0.}, {255., 20., 0.}, {255., 200., 0.},
	{255., 20., 0.}, {20., 0., 0.}}};
	vars->pallets[3] = (t_pallet){.d = 6,
		.val = {{0., 7., 100.}, {32., 107., 203.}, {237., 255., 255.},
	{255., 170., 0.}, {0., 2., 0.}, {0., 7., 100.}}};
	vars->pallets[4] = (t_pallet){.d = 3,
		.val = {{0., 0., 0.}, {255., 255., 255.}, {0., 0., 0.}}};
	vars->pallets[5] = (t_pallet){.d = 7,
		.val = {{255., 0., 0.}, {255., 255., 0.}, {0., 255., 0.},
	{0., 255., 255.}, {0., 0., 255.}, {255., 0., 255.}, {255., 0., 0.}}};
	vars->pallets[6] = (t_pallet){.d = 5,
		.val = {{0., 0., 0.}, {0., 0., 200.}, {255., 255., 255.},
	{0., 0., 200.}, {0., 0., 0.}}};
}

void	init_julia(t_vars *vars)
{
	vars->type = e_julia;
	vars->cx = 0.285;
	vars->cy = 0.01;
	vars->left = -1.5;
	vars->right = 1.5;
}

void	init_mandel(t_vars *vars)
{
	vars->type = e_mandelbrot;
	vars->left = -2.0;
	vars->right = 1.0;
}

void	init_burn(t_vars *vars)
{
	vars->type = e_burn;
	vars->left = -2.5;
	vars->right = 1.5;
}

void	init_sier(t_vars *vars)
{
	VAR_TYPE	a;

	if (HEIGHT > WIDTH)
		a = WIDTH;
	else
		a = HEIGHT;
	vars->top = (HEIGHT - a) * 0.5;
	vars->left = (WIDTH - a) * 0.5;
	vars->bottom = vars->top + a;
	vars->right = vars->left + a;
	vars->scale = 1.0;
	vars->start.a = a / 3;
	vars->start.c.x = vars->left + 0.5 * a;
	vars->start.c.y = vars->top + 0.5 * a;
	vars->start.l = 0;
	vars->start.p.x = 0;
	vars->start.p.y = 0;
}
