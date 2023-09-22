/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:38:38 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/22 18:16:43 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_textures(t_game *g)
{
	g->tex_n.img = mlx_xpm_file_to_image(g->mlx.mlx, "colorstone.xpm", &g->tex_n.l, &g->tex_n.h);
	if (!g->tex_n.img)
		return (0);
	g->tex_n.addr = mlx_get_data_addr(g->tex_n.img, &g->tex_n.bpp, &g->tex_n.ll, &g->tex_n.ed);
	g->tex_s.img = mlx_xpm_file_to_image(g->mlx.mlx, "bluestone.xpm", &g->tex_s.l, &g->tex_s.h);
	if (!g->tex_s.img)
		return (0);
	g->tex_s.addr = mlx_get_data_addr(g->tex_s.img, &g->tex_s.bpp, &g->tex_s.ll, &g->tex_s.ed);
	g->tex_w.img = mlx_xpm_file_to_image(g->mlx.mlx, "greystone.xpm", &g->tex_w.l, &g->tex_w.h);
	if (!g->tex_w.img)
		return (0);
	g->tex_w.addr = mlx_get_data_addr(g->tex_w.img, &g->tex_w.bpp, &g->tex_w.ll, &g->tex_w.ed);
	g->tex_e.img = mlx_xpm_file_to_image(g->mlx.mlx, "eagle.xpm", &g->tex_e.l, &g->tex_e.h);
	if (!g->tex_e.img)
		return (0);
	g->tex_e.addr = mlx_get_data_addr(g->tex_e.img, &g->tex_e.bpp, &g->tex_e.ll, &g->tex_e.ed);
	g->tex_f.img = mlx_xpm_file_to_image(g->mlx.mlx, "Tile.xpm", &g->tex_f.l, &g->tex_f.h);
	if (!g->tex_f.img)
		return (0);
	g->tex_f.addr = mlx_get_data_addr(g->tex_f.img, &g->tex_f.bpp, &g->tex_f.ll, &g->tex_f.ed);
	g->tex_c.img = mlx_xpm_file_to_image(g->mlx.mlx, "Elements.xpm", &g->tex_c.l, &g->tex_c.h);
	if (!g->tex_c.img)
		return (0);
	g->tex_c.addr = mlx_get_data_addr(g->tex_c.img, &g->tex_c.bpp, &g->tex_c.ll, &g->tex_c.ed);
}
