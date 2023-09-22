/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:38:38 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/22 07:25:48 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_textures(t_game *g)
{
	//g->tex_n = mlx_xpm_file_to_image(g->mlx.mlx, "maps/redbrick.png", &g->texWidth, &g->texHeight);
	g->tex_n = mlx_new_image(mlx_ptr, image_width, image_height);
	if (!g->tex_n)
		printf("Fails\n");
}
