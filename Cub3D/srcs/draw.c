/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/09 07:45:19 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	create_trgb(unsigned char t, unsigned char r,
		unsigned char g, unsigned char b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	render_object(t_tex *t, int *bg, int x0, int y0)
{
	int	x;
	int	y;

	x0 -= t->l / 2;
	y0 -= t->h;
	y = -1;
	while (++y < t->h)
	{
		x = -1;
		while (++x < t->l)
		{
			int	color = *((int*) t->addr + x + y * t->l);
			if (color > 0)
				*((int*) bg + x + x0 + (y + y0) * WIDTH) = color;
		}
	}
}

void	render_backgroud(t_game *g)
{
	int		ix;
	float	d;

	g->pos.Ax = -1;
	g->pos.Ay = -1;
	g->pos.Bx = -1;
	g->pos.By = -1;
	t_sprite	*sp = 0;
	ix = -1;
	while (++ix < WIDTH)
	{
		d = render_box(g, ix);
		render_sprites(g, ix, d, &sp);
	}
	if (g->shoot && sp)
	{
		sp->health--;
		if (!sp->health)
		{
			sp->state = DIE;
			sp->i_tex = 0;
		}
	}
	g->shoot = 0;
}

void	scale_window(t_game *g)
{
	if (SCALE > 1)
	{
		int	x;
		int	y;
		y = HEIGHT * SCALE;
		while (--y >= 0)
		{

			x = WIDTH * SCALE;
			while (--x >= 0)
				*((int*) g->mlx.addr_scale + x + y * WIDTH * SCALE) = *((int*) g->mlx.addr + x / SCALE + y / SCALE * WIDTH);
		}
		mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->mlx.img_scale, 0, 0);
	}
	else
		mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->mlx.img, 0, 0);
}

int	draw(t_game *g)
{
	frames(g);
	render_backgroud(g);
	render_object(g->gun_tex, (int *) g->mlx.addr, WIDTH / 2, HEIGHT);
	draw_mini_map(g);
	scale_window(g);
	return (1);
}
