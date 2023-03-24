/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/24 07:06:45 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

int	key_hook(int keycode, t_vars *vars)
{
	int		i;
	int		j;
	int		dp;
	VAR_TYPE	d;
	VAR_TYPE	zoom;

	//ft_printf("keycode: %d\n", keycode);
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
		//cal_th(vars, 0, HEIGHT, 'v');
		cal_v(vars, 0, WIDTH);
		colors_v(vars, 0, WIDTH);
		draw(vars, vars->img);
	}
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
	if (keycode == XK_q || keycode == XK_Escape)
		end_prog(vars);
	if (keycode == 61 || keycode == XK_minus)
	{
		if (keycode == 61)
			zoom = 1 / ZOOM;
		else
			zoom = ZOOM;
		d = (vars->right - vars->left) * zoom;
		vars->left = vars->right * 0.5 + vars->left * 0.5 - d * 0.5;
		vars->right = vars->left + d;
		d = (vars->top - vars->bottom) * zoom;
		vars->top = vars->bottom * 0.5 + vars->top * 0.5 + d * 0.5;
		vars->bottom = vars->top - d;
		vars->scale *= zoom;
		vars->left = vars->left;
		vars->right = vars->right;
		vars->top = vars->top;
		vars->bottom = vars->bottom;
		vars->scale *= zoom;
		cal_v(vars, 0, WIDTH);
		colors_v(vars, 0, WIDTH);
		draw(vars, vars->img);
	}
	if (keycode == XK_Right || keycode == XK_Left)
	{
		d = (vars->right - vars->left) * MOVE;
		dp = (int) (d / vars->scale);
		d = dp * vars->scale;
		if (keycode == XK_Left)
			d = -d;
		vars->left += d;
		vars->right += d;
		if (keycode == XK_Right)
		{
			i = -1;
			while (++i < WIDTH - dp)
			{
				j = -1;
				while (++j < HEIGHT)
				{
					vars->iters[i][j] = vars->iters[i + dp][j];
					vars->xn[i][j] = vars->xn[i + dp][j];
					vars->yn[i][j] = vars->yn[i + dp][j];
					vars->colors[i][j] = vars->colors[i + dp][j];
					vars->update[j * WIDTH + i] = vars->update[j * WIDTH + i + dp];
				}
			}
			
			j = -1;
			while (++j < HEIGHT)
				ft_memmove(vars->img->addr + j * vars->img->line_length, vars->img->addr + j * vars->img->line_length + dp * (vars->img->bits_per_pixel / 8), (WIDTH - dp) * (vars->img->bits_per_pixel / 8));
			//i = WIDTH - dp - 1;
			//while (++i < WIDTH)
			//{
			//	j = -1;
			//	while (++j < HEIGHT)
			//		vars->update[j * WIDTH + i] = 1;
			//}
			//vars->xp = WIDTH - dp;
			//vars->yp = 0;
		}
		else
		{
			i = WIDTH;
			while (--i >= dp)
			{
				j = -1;
				while (++j < HEIGHT)
				{
					//vars->iters[i][j] = vars->iters[i - dp][j];
					//vars->xn[i][j] = vars->xn[i - dp][j];
					//vars->yn[i][j] = vars->yn[i - dp][j];
					vars->colors[i][j] = vars->colors[i - dp][j];
					//vars->update[j * WIDTH + i] = vars->update[j * WIDTH + i - dp];
				}
			}
			//i = -1;
			//while (++i < dp)
			//{
			//	j = -1;
			//	while (++j < HEIGHT)
			//		vars->update[j * WIDTH + i] = 1;
			//}
			//vars->xp = 0;
			//vars->yp = 0;
		}
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	}
	else if (keycode == XK_Up || keycode == XK_Down)
	{
		d = (vars->top - vars->bottom) * MOVE;
		dp = (int) (d / vars->scale);
		d = dp * vars->scale;
		if (keycode == XK_Down)
			d = -d;
		vars->top += d;
		vars->bottom += d;
		if (keycode == XK_Down)
		{
			j = -1;
			while (++j < HEIGHT - dp)
			{
				i = -1;
				while (++i < WIDTH)
				{
					vars->iters[i][j] = vars->iters[i][j + dp];
					vars->xn[i][j] = vars->xn[i][j + dp];
					vars->yn[i][j] = vars->yn[i][j + dp];
					vars->colors[i][j] = vars->colors[i][j + dp];
				}
			}
			cal_h(vars, HEIGHT - dp, HEIGHT);
			colors_h(vars, HEIGHT - dp, HEIGHT);
		}
		else
		{
			j = HEIGHT;
			while (--j >= dp)
			{
				i = -1;
				while (++i < WIDTH)
				{
					vars->iters[i][j] = vars->iters[i][j - dp];
					vars->xn[i][j] = vars->xn[i][j - dp];
					vars->yn[i][j] = vars->yn[i][j - dp];
					vars->colors[i][j] = vars->colors[i][j - dp];
				}
			}
			cal_h(vars, 0, dp);
			colors_h(vars, 0, dp);
		}
		draw(vars, vars->img);
	}
	else if (keycode == XK_r)
	{
	}
	return (0);
}
