/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/09 07:39:41 by ngoc             ###   ########.fr       */
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
	int	ix;
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
	int	i;

	if (g->frames[FR_DOOR])
	{
		if (g->pos.x != g->opened_door_x ||  g->pos.y != g->opened_door_y)
		{
			if (g->opened && g->hidden_door < BOX_SIZE)
				g->hidden_door += DOOR_SPEED;
			else if (g->hidden_door == BOX_SIZE && g->frames[FR_DOOR] < DOOR_IDLE)
			{
				g->map.v[g->opened_door_y][g->opened_door_x] = B_GROUND;
				g->frames[FR_DOOR]++;
			}
			else if (g->hidden_door == BOX_SIZE && g->frames[FR_DOOR] == DOOR_IDLE)
			{
				g->map.v[g->opened_door_y][g->opened_door_x] = B_DOOR;
				g->hidden_door -= DOOR_SPEED;
				g->opened = 0;
			}
			else if (g->hidden_door && g->hidden_door < BOX_SIZE && g->frames[FR_DOOR] == DOOR_IDLE)
				g->hidden_door -= DOOR_SPEED;
			else
				g->frames[FR_DOOR] = 0;
		}
	}
	if (g->frames[FR_UP] > TRANS_SPEED)
		g->frames[FR_UP] = 0;
	if (g->frames[FR_DOWN] > TRANS_SPEED)
		g->frames[FR_DOWN] = 0;
	if (g->frames[FR_LEFT] > TRANS_SPEED)
		g->frames[FR_LEFT] = 0;
	if (g->frames[FR_RIGHT] > TRANS_SPEED)
		g->frames[FR_RIGHT] = 0;
	if (g->frames[FR_ROT_R] > ROT_SPEED)
		g->frames[FR_ROT_R] = 0;
	if (g->frames[FR_ROT_L] > ROT_SPEED)
		g->frames[FR_ROT_L] = 0;
	if (g->frames[FR_GUN] > GUN_SPEED)
		g->frames[FR_GUN] = 0;
	if (g->frames[FR_GUN] == 1)
		g->gun_tex = &g->gun[1];
	else if (g->frames[FR_GUN] == 2)
		g->gun_tex = &g->gun[2];
	else
		g->gun_tex = &g->gun[0];
	i = -1;
	while (++i < N_FRAMES)
		if (i != FR_DOOR && g->frames[i])
			g->frames[i]++;
	i = -1;
	while (++i < g->n_sprites)
	{
		if (g->sprites[i].type == B_SPRITE)
		{
			if (g->sprites[i].state == NORMAL)
			{
				g->sprites[i].tex = &g->sp_tex[g->sprites[i].i_tex / SPRITE_STATE];
				g->sprites[i].i_tex++;
				if (g->sprites[i].i_tex == (SPRITE_STATE * 3))
					g->sprites[i].i_tex = 0;
			}
			else if (g->sprites[i].state == DIE && g->sprites[i].i_tex < (SPRITE_STATE * 5))
			{
				g->sprites[i].tex = &g->sp_hit[g->sprites[i].i_tex / SPRITE_STATE];
				g->sprites[i].i_tex++;
			}
		}

	}
	render_backgroud(g);
	render_object(g->gun_tex, (int *) g->mlx.addr, WIDTH / 2, HEIGHT);
	draw_mini_map(g);
	scale_window(g);
	return (1);
}
