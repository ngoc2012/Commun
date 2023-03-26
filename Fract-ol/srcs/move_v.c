/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_v.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/26 12:29:39 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	move_val(t_vars *vars, t_coor *p, int dx, int dy)
{
	vars->iters[p->x][p->y] = vars->iters[p->x + dx][p->y + dy];
	vars->xn[p->x][p->y] = vars->xn[p->x + dx][p->y + dy];
	vars->yn[p->x][p->y] = vars->yn[p->x + dx][p->y + dy];
	vars->colors[p->x][p->y] = vars->colors[p->x + dx][p->y + dy];
}

void	draw_p(t_vars *vars, t_coor *p, int *addr, int r2)
{
	cal(vars, p->x, p->y, r2);
	colors(vars, p->x, p->y, r2);
	*addr = get_color(vars->colors[p->x][p->y], vars->pallet);
}

void	move_up(int dp, t_vars *vars)
{
	t_coor	p;
	int		r2;
	int		*addr;

	r2 = RADIUS * RADIUS;
	addr = (int *) vars->img->addr;
	ft_memmove(addr + dp * WIDTH, addr, (WIDTH * (HEIGHT - dp)) * 4);
	p.y = HEIGHT;
	while (--p.y >= dp)
	{
		p.x = -1;
		while (++p.x < WIDTH)
			move_val(vars, &p, 0, -dp);
	}
	addr = (int *) vars->img->addr + dp * WIDTH;
	p.y++;
	while (--p.y >= 0)
	{
		p.x = WIDTH;
		while (--p.x >= 0)
			draw_p(vars, &p, addr--, r2);
	}
}

void	move_down(int dp, t_vars *vars)
{
	t_coor	p;
	int		r2;
	int		*addr;

	r2 = RADIUS * RADIUS;
	addr = (int *) vars->img->addr;
	ft_memmove(addr, addr + dp * WIDTH, (WIDTH * (HEIGHT - dp)) * 4);
	p.y = -1;
	while (++p.y < HEIGHT - dp)
	{
		p.x = -1;
		while (++p.x < WIDTH)
			move_val(vars, &p, 0, dp);
	}
	addr += (HEIGHT - dp) * WIDTH;
	p.y--;
	while (++p.y < HEIGHT)
	{
		p.x = -1;
		while (++p.x < WIDTH)
			draw_p(vars, &p, addr++, r2);
	}
}

void	move_h(int keycode, int dp, t_vars *vars)
{
	int	i;
	int	j;
	int	r2;
	int	*addr;

	r2 = RADIUS * RADIUS;
	if (keycode == XK_Right)
	{
		j = -1;
		while (++j < HEIGHT)
		{
			addr = (int *) vars->img->addr + j * WIDTH;
			ft_memmove(addr, addr + dp, (WIDTH - dp) * 4);
			addr += WIDTH - dp;
			i = -1;
			while (++i < WIDTH - dp)
			{
				vars->iters[i][j] = vars->iters[i + dp][j];
				vars->xn[i][j] = vars->xn[i + dp][j];
				vars->yn[i][j] = vars->yn[i + dp][j];
				vars->colors[i][j] = vars->colors[i + dp][j];
			}
			i--;
			while (++i < WIDTH)
			{
				cal(vars, i, j, r2);
				colors(vars, i, j, r2);
				*(addr++) = get_color(vars->colors[i][j], vars->pallet);
			}
		}
	}
	else
	{
		j = -1;
		while (++j < HEIGHT)
		{
			addr = (int *) vars->img->addr + j * WIDTH;
			ft_memmove(addr + dp, addr, (WIDTH - dp) * 4);
			addr += dp;
			i = WIDTH;
			while (--i >= dp)
			{
				vars->iters[i][j] = vars->iters[i - dp][j];
				vars->xn[i][j] = vars->xn[i - dp][j];
				vars->yn[i][j] = vars->yn[i - dp][j];
				vars->colors[i][j] = vars->colors[i - dp][j];
			}
			i++;
			while (--i >= 0)
			{
				cal(vars, i, j, r2);
				colors(vars, i, j, r2);
				*(addr--) = get_color(vars->colors[i][j], vars->pallet);
			}
		}
	}
}
