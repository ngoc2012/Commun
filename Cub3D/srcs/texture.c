/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:38:38 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/05 21:11:08 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_texture(t_game *g, t_tex *t, char *path)
{
	if (t->img)
		mlx_destroy_image(g->mlx.mlx, t->img);
	t->img = mlx_xpm_file_to_image(g->mlx.mlx, path, &t->l, &t->h);
	if (!t->img)
		return (0);
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->ll, &t->ed);
	return (1);
}

int	return_error(char *s, char **ss)
{
	free_array_str(&ss, 0);
	free(s);
	return (0);
}

int	get_color(char *s)
{
	int	i;
	int	len;
	int	c[3];
	char	**ss;

	ss = ft_split(s, ',');
	i = -1;	
	while (ss[++i] && i < 4)
	{
		c[i] = ft_atoi(ss[i]);
		if (c[i] > 255 || c[i] < 0)
			return (free_array_str(&ss, 0));
	}
	free_array_str(&ss, 0);
	return (create_trgb(1, (unsigned int) c[0], (unsigned int) c[1], (unsigned int) c[2]));
}

int	get_textures(t_game *g, char *fn)
{
	int		fd;
	char	*s;
	char	*s0;
	char	**ss;

	get_texture(g, &g->sp_tex[0], "./sprites/cobra0.xpm");
	get_texture(g, &g->sp_tex[1], "./sprites/cobra1.xpm");
	get_texture(g, &g->sp_tex[2], "./sprites/cobra2.xpm");
	get_texture(g, &g->sp_att[0], "./sprites/cobraatt0.xpm");
	get_texture(g, &g->sp_att[1], "./sprites/cobraatt1.xpm");
	get_texture(g, &g->sp_att[2], "./sprites/cobraatt2.xpm");
	get_texture(g, &g->sp_hit[0], "./sprites/cobrahit0.xpm");
	get_texture(g, &g->sp_hit[1], "./sprites/cobrahit1.xpm");
	get_texture(g, &g->sp_hit[2], "./sprites/cobrahit2.xpm");
	get_texture(g, &g->sp_hit[3], "./sprites/cobrahit3.xpm");
	get_texture(g, &g->sp_hit[4], "./sprites/cobrahit4.xpm");
	get_texture(g, &g->gun[0], "./guns/gun1a.xpm");
	get_texture(g, &g->gun[1], "./guns/gun1b.xpm");
	get_texture(g, &g->gun[2], "./guns/gun1c.xpm");
	get_texture(g, &g->tex[NO], "./walls/beamskin3.xpm");
	get_texture(g, &g->tex[SO], "./walls/tile32.xpm");
	get_texture(g, &g->tex[WE], "./walls/tile105.xpm");
	get_texture(g, &g->tex[EA], "./walls/steelwall6.xpm");
	get_texture(g, &g->tex[DO], "./walls/bigdoor.xpm");
	get_texture(g, &g->tex[FL], "./walls/floorsteel.xpm");
	get_texture(g, &g->tex[CL], "./walls/floorskin.xpm");
	get_texture(g, &g->tex[D3], "./sprites/crate.xpm");
	get_texture(g, &g->tex[D4], "./sprites/d_table.xpm");
	get_texture(g, &g->tex[D5], "./sprites/d_tree.xpm");
	get_texture(g, &g->tex[D6], "./sprites/i_health.xpm");
	fd = open(fn, O_RDONLY);
	if (fd == -1)
		return (0);
	s = get_next_line(fd);
	while (s)
	{
		s0 = s;
		while (ft_strchr(" 	\n", *s))
			s++;
		if (ft_strlen(s) > 1)
		{
			s[ft_strlen(s) - 1] = 0;
			ss = ft_split(s, ' ');
			if (astr_len(ss) > 1)
			{
				if (!ft_strncmp("NO", ss[0], 3) && !get_texture(g, &g->tex[NO], ss[1]))
					return (return_error(s, ss));
				if (!ft_strncmp("SO", ss[0], 3) && !get_texture(g, &g->tex[SO], ss[1]))
					return (return_error(s, ss));
				if (!ft_strncmp("WE", ss[0], 3) && !get_texture(g, &g->tex[WE], ss[1]))
					return (return_error(s, ss));
				if (!ft_strncmp("EA", ss[0], 3) && !get_texture(g, &g->tex[EA], ss[1]))
					return (return_error(s, ss));
				if (!ft_strncmp("DO", ss[0], 3) && !get_texture(g, &g->tex[DO], ss[1]))
					return (return_error(s, ss));
				if (!ft_strncmp("FL", ss[0], 3) && !get_texture(g, &g->tex[FL], ss[1]))
					return (return_error(s, ss));
				if (!ft_strncmp("CL", ss[0], 3) && !get_texture(g, &g->tex[CL], ss[1]))
					return (return_error(s, ss));
				if (!ft_strncmp("D3", ss[0], 3) && !get_texture(g, &g->tex[D3], ss[1]))
					return (return_error(s, ss));
				if (!ft_strncmp("D4", ss[0], 3) && !get_texture(g, &g->tex[D4], ss[1]))
					return (return_error(s, ss));
				if (!ft_strncmp("D5", ss[0], 3) && !get_texture(g, &g->tex[D5], ss[1]))
					return (return_error(s, ss));
				if (!ft_strncmp("D6", ss[0], 3) && !get_texture(g, &g->tex[D6], ss[1]))
					return (return_error(s, ss));
				if (!ft_strncmp("F", ss[0], 2))
				{
					g->fl_color = get_color(ss[1]);
					if (!g->fl_color)
						return (return_error(s, ss));
				}
				if (!ft_strncmp("C", ss[0], 2))
				{
					g->cl_color = get_color(ss[1]);
					if (!g->cl_color)
						return (return_error(s, ss));
				}
			}
			free_array_str(&ss, 0);
		}
		free(s0);
		s = get_next_line(fd);
	}
	close(fd);
	return (1);
}
