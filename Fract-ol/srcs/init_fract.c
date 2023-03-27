/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/27 21:53:10 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
