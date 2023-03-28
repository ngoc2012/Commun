/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/28 22:15:48 by ngoc             ###   ########.fr       */
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

void	sier(t_vars *vars, t_sier *r)
{
	int	xp;
	int	yp;
	VAR_TYPE	xp0;
	VAR_TYPE	yp0;
	int	*addr;
	int	*addr0;
	int	d;
	t_sier	children[8];
	int	i;

	d = vars->pallets[vars->pallet].d;
	addr0 = (int *)vars->img->addr;
	xp0 = vars->left + vars->scale * (r->c.x - r->a * 0.5 - vars->left);
	yp0 = vars->top + vars->scale * (r->c.y - r->a * 0.5 - vars->top);
	yp = (int) yp0 - 1;
	if (yp < -1)
		yp = -1;
	while (++yp < (int) (yp0 + vars->scale * r->a) && yp < HEIGHT)
	{
		xp = xp0 - 1;
		if (xp < -1)
			xp = -1;
		addr = addr0 + yp * WIDTH + xp + 1;
		while (++xp < (int) (xp0 + vars->scale * r->a) && xp < WIDTH)
			*(addr++) = get_color(vars,(VAR_TYPE) (r->l % d) / d);
	}
	if (r->a / 3 < 1)
		return ;
	i = -1;
	xp = -1;
	while (++xp < 3)
	{
		yp = -1;
		while (++yp < 3)
		{
			if (xp != 1 || yp != 1)
			{
				children[++i].a = r->a / 3;
				children[i].p.x = xp;
				children[i].p.y = yp;
				children[i].c.x = r->c.x - r->a + xp * r->a;
				children[i].c.y = r->c.y - r->a + yp * r->a;
				children[i].l = r->l + 1;
				sier(vars, &children[i]);
			}
		}
	}
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
	//printf("scale = %f, left = %f, top = %f, right = %f, bottom = %f\n", vars->scale, vars->left, vars->top, vars->right, vars->bottom);
	sier(vars, &vars->start);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}
