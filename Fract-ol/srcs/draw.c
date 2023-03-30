/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/30 21:08:48 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	create_trgb(unsigned char t, unsigned char r,
		unsigned char g, unsigned char b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_color(t_vars *vars, VAR_TYPE value)
{
	t_pallet	p;
	t_coor		c;
	VAR_TYPE	n;
	VAR_TYPE	*a;
	VAR_TYPE	*u;

	p = vars->pallets[vars->pallet];
	if (value == 0.0)
		return (create_trgb(1.0, p.val[0][0], p.val[0][1], p.val[0][2]));
	if (value == 1.0)
		return (create_trgb(1.0, p.val[p.d - 1][0],
			p.val[p.d - 1][1], p.val[p.d - 1][2]));
	c.x = (int)(value * (VAR_TYPE) p.d);
	if (c.x == p.d)
		c.x = p.d - 1;
	if (c.x == 0)
		c.x = 1;
	c.y = c.x - 1;
	n = value * ((VAR_TYPE) p.d - 1.0) - (VAR_TYPE) c.y;
	a = &p.val[c.x][0];
	u = &p.val[c.y][0];
	return (create_trgb(1, (unsigned char)(u[0] + n * (a[0] - u[0])),
		(unsigned char)(u[1] + n * (a[1] - u[1])),
		(unsigned char)(u[2] + n * (a[2] - u[2]))));
}

void	draw_p(t_vars *vars, t_coor *p, int *addr, int r2)
{
	cal(vars, p->x, p->y, r2);
	colors(vars, p->x, p->y, r2);
	*addr = get_color(vars, vars->colors[p->x][p->y]);
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
			*(addr++) = get_color(vars, vars->colors[xp][yp]);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}
