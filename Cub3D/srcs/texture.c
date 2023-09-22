/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:38:38 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/22 09:25:47 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_textures(t_game *g)
{
	int	bpp;
	int	ll;
	int	ed;

	g->tex_n_p = mlx_xpm_file_to_image(g->mlx.mlx, "colorstone.xpm", &g->texWidth, &g->texHeight);
	if (!g->tex_n_p)
		printf("Fails\n");
	g->tex_n = mlx_get_data_addr(g->tex_n_p, bpp, ll, ed);
}
