/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:38:38 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/23 19:07:07 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_texture(t_game *g, enum e_tex it, char *path)
{
	if (g->tex[it].img)
		mlx_destroy_image(g->mlx.mlx, g->tex[it].img);
	g->tex[it].img = mlx_xpm_file_to_image(g->mlx.mlx, path, &g->tex[it].l, &g->tex[it].h);
	if (!g->tex[it].img)
		return (0);
	g->tex[it].addr = mlx_get_data_addr(g->tex[it].img, &g->tex[it].bpp, &g->tex[it].ll, &g->tex[it].ed);
	return (1);
}

int	get_textures(t_game *g, char *fn)
{
	get_texture(g, NO, "./walls/beamskin3.xpm");
	get_texture(g, SO, "./walls/tile32.xpm");
	get_texture(g, WE, "./walls/tile105.xpm");
	get_texture(g, EA, "./walls/steelwall6.xpm");
	get_texture(g, DO, "./walls/bigdoor.xpm");
	get_texture(g, FL, "./walls/floorsteel.xpm");
	get_texture(g, CL, "./walls/floorskin.xpm");
	get_texture(g, D3, "./sprites/crate.xpm");
	get_texture(g, D4, "./sprites/d_table.xpm");
	get_texture(g, D5, "./sprites/d_tree.xpm");
	get_texture(g, D6, "./sprites/i_health.xpm");
	fd = open(fn, O_RDONLY);
	if (fd == -1)
		return (0);
	s = get_next_line(fd);
	while (s)
	{
		if (ft_strlen(s) > 1)
		{
			s[ft_strlen(s) - 2] = 0;
			ss = ft_split(s, ' ');
			if (ft_strncmp("NO", ss[0], 3))
				get_texture(g, NO, "./walls/beamskin3.xpm");
		}
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
}
