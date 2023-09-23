/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:38:38 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/23 18:09:41 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_texture(t_game *g, e_tex it, char *path)
{
	g->tex[it].img = mlx_xpm_file_to_image(g->mlx.mlx, path, &g->tex[it].l, &g->tex[it].h);
	if (!g->tex[it].img)
		return (0);
	g->tex[it].addr = mlx_get_data_addr(g->tex[it].img, &g->tex[it].bpp, &g->tex[it].ll, &g->tex[it].ed);
	return (1);
}

int	get_textures(t_game *g, char *fn)
{
	get_texture(g, NO, "./walls/holeskin1695480474.xpm");
	get_texture(g, SO, "./walls/floorskin1695480473.xpm");
	get_texture(g, WE, "./walls/floorskin1695480473.xpm");
	get_texture(g, EA, "./walls/floorskin1695480473.xpm");
	get_texture(g, DO, "./walls/floorskin1695480473.xpm");
	get_texture(g, SO, "./walls/floorskin1695480473.xpm");
	get_texture(g, SO, "./walls/floorskin1695480473.xpm");
	get_texture(g, SO, "./walls/floorskin1695480473.xpm");
	get_texture(g, SO, "./walls/floorskin1695480473.xpm");
	get_texture(g, SO, "./walls/floorskin1695480473.xpm");
	get_texture(g, SO, "./walls/floorskin1695480473.xpm");
	get_texture(g, SO, "./walls/floorskin1695480473.xpm");
	//fd = open(fn, O_RDONLY);
	//if (fd == -1)
	//	return (0);
}
