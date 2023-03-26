/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/26 23:40:51 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	key_hook1(int keycode, t_vars *vars)
{
	VAR_TYPE	zoom;

	if (keycode == 61 || keycode == XK_minus)
	{
		if (keycode == 61)
			zoom = 1 / ZOOM;
		else
			zoom = ZOOM;
		set_env(zoom, 0, 0, vars);
		set_zoom(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	}
	if (keycode == XK_p)
	{
		vars->pallet++;
		vars->pallet %= N_PALLETS;
		draw(vars, vars->img);
	}
	if (keycode == XK_s)
	{
		if (vars->smooth)
			vars->smooth = 0;
		else
			vars->smooth = 1;
		colors_v(vars, 0, WIDTH);
		draw(vars, vars->img);
	}
}

void	key_hook2(int keycode, t_vars *vars)
{
	if (keycode == XK_q || keycode == XK_Escape)
		end_prog(vars);
	if (keycode == XK_i && vars->max_iter + STEP_ITER <= MAX_ITER)
	{
		vars->max_iter += STEP_ITER;
		ft_printf("MAX_ITER = %d\n", vars->max_iter);
		cal_v(vars, 0, WIDTH);
		colors_v(vars, 0, WIDTH);
		draw(vars, vars->img);
	}
	if (keycode == XK_u && vars->max_iter - STEP_ITER >= MIN_ITER)
	{
		vars->max_iter -= STEP_ITER;
		ft_printf("MAX_ITER = %d\n", vars->max_iter);
		cal_v(vars, 0, WIDTH);
		colors_v(vars, 0, WIDTH);
		draw(vars, vars->img);
	}
}

void	key_hook3(int keycode, t_vars *vars)
{
	int			dp;
	VAR_TYPE	d;

	if (keycode == XK_Right || keycode == XK_Left)
	{
		d = (vars->right - vars->left) * MOVE;
		dp = (int)(d / vars->scale);
		d = dp * vars->scale;
		if (keycode == XK_Left)
			d = -d;
		vars->left += d;
		vars->right += d;
		if (keycode == XK_Left)
			move_left(dp, vars);
		else
			move_right(dp, vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	}
	if (keycode == XK_Up || keycode == XK_Down)
	{
		d = (vars->top - vars->bottom) * MOVE;
		dp = (int)(d / vars->scale);
		d = dp * vars->scale;
		if (keycode == XK_Down)
			d = -d;
		vars->top += d;
		vars->bottom += d;
		if (keycode == XK_Up)
			move_up(dp, vars);
		else
			move_down(dp, vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	}
}

int	key_hook(int keycode, t_vars *vars)
{
	key_hook1(keycode, vars);
	key_hook2(keycode, vars);
	key_hook3(keycode, vars);
	if (keycode == XK_r)
	{
	}
	return (0);
}
