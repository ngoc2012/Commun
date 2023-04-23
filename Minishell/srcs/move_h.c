/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_h.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/26 12:37:01 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	move_left(int dp, t_vars *vars)
{
	t_coor	p;
	int		r2;
	int		*addr;

	r2 = RADIUS * RADIUS;
	p.y = -1;
	while (++p.y < HEIGHT)
	{
		addr = (int *) vars->img->addr + p.y * WIDTH;
		ft_memmove(addr + dp, addr, (WIDTH - dp) * 4);
		addr += dp;
		p.x = WIDTH;
		while (--p.x >= dp)
			move_val(vars, &p, -dp, 0);
		p.x++;
		while (--p.x >= 0)
			draw_p(vars, &p, addr--, r2);
	}
}

void	move_right(int dp, t_vars *vars)
{
	t_coor	p;
	int		r2;
	int		*addr;

	r2 = RADIUS * RADIUS;
	p.y = -1;
	while (++p.y < HEIGHT)
	{
		addr = (int *) vars->img->addr + p.y * WIDTH;
		ft_memmove(addr, addr + dp, (WIDTH - dp) * 4);
		addr += WIDTH - dp;
		p.x = -1;
		while (++p.x < WIDTH - dp)
			move_val(vars, &p, dp, 0);
		p.x--;
		while (++p.x < WIDTH)
			draw_p(vars, &p, addr++, r2);
	}
}
