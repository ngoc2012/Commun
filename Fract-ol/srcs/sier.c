/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sier.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/30 00:22:42 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	children(t_vars *vars, t_sier *r)
{
	t_coor	p;
	t_sier	cr;

	p.x = -1;
	while (++p.x < 3)
	{
		p.y = -1;
		while (++p.y < 3)
		{
			if (p.x != 1 || p.y != 1)
			{
				cr.a = r->a / 3;
				cr.p.x = p.x;
				cr.p.y = p.y;
				cr.c.x = r->c.x - r->a + p.x * r->a;
				cr.c.y = r->c.y - r->a + p.y * r->a;
				cr.l = r->l + 1;
				if (!((cr.c.x - 1.5 * cr.a) > WIDTH
						|| (cr.c.x + 1.5 * cr.a) < 0
						|| (cr.c.y - 1.5 * cr.a) > HEIGHT
						|| (cr.c.y + 1.5 * cr.a) < 0))
					sier(vars, &cr);
			}
		}
	}
}

void	sier(t_vars *vars, t_sier *r)
{
	t_coor	p;
	t_coor	p0;
	int		*addr;
	int		*addr0;
	int		d;

	d = vars->pallets[vars->pallet].d;
	addr0 = (int *)vars->img->addr;
	p0.x = r->c.x - r->a * 0.5;
	p0.y = r->c.y - r->a * 0.5;
	p.y = (int)(p0.y) - 1;
	if (p.y < -1)
		p.y = -1;
	while (++p.y < (int)((p0.y + r->a)) && p.y < HEIGHT)
	{
		p.x = p0.x - 1;
		if (p.x < -1)
			p.x = -1;
		addr = addr0 + p.y * WIDTH + p.x + 1;
		while (++p.x < (int)((p0.x + r->a)) && p.x < WIDTH)
			*(addr++) = get_color(vars, (VAR_TYPE)(r->l % d) / d);
	}
	if (r->a / 3 < 1)
		return ;
	children(vars, r);
}

void	draw_sier(t_vars *vars)
{
	int	xp;
	int	yp;
	int	*addr;

	addr = (int *)vars->img->addr;
	yp = -1;
	while (++yp < HEIGHT)
	{
		xp = -1;
		while (++xp < WIDTH)
			*(addr++) = 0;
	}
	sier(vars, &vars->start);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}
