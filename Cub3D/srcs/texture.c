/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:38:38 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/22 09:57:50 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_textures(t_game *g)
{
	int	bpp;
	int	ll;
	int	ed;

	g->tex_n.img = mlx_xpm_file_to_image(g->mlx.mlx, "colorstone.xpm", g->tex_n.l, g->tex_n.h);
	if (!g->tex_n.img)
		printf("Fails\n");
	g->tex_n.addr = mlx_get_data_addr(g->tex_n.img, &g->tex_n.bpp, &g->tex_n.ll, &g->tex_n.ed);
}
