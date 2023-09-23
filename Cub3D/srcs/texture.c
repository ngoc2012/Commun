/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:38:38 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/23 18:03:59 by ngoc             ###   ########.fr       */
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
	fd = open(fn, O_RDONLY);
	if (fd == -1)
		return (0);
}
