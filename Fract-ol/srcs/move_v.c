/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_v.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/30 21:08:50 by ngoc             ###   ########.fr       */
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
