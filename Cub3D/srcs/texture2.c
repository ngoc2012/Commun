/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:38:38 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/16 16:07:20 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	g_t(t_game *g, t_tex *t, char *path, enum e_tex et)
{
	if (t->img)
		return (0);
	t->img = mlx_xpm_file_to_image(g->mlx.mlx, path, &t->l, &t->h);
	if (!t->img)
		return (0);
	if (et < 5 && (t->l != 64 || t->h != 64))
		return (0);
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->ll, &t->ed);
	return (1);
}

int	suite_g_t2(t_game *g, char **ss)
{
	if (!ft_strncmp("FL", ss[0], 3))
	{
		if (!g_t(g, &g->tex[t_fl], ss[1], t_fl))
			return (0);
		g->fl_color = 0;
	}
	if (!ft_strncmp("CL", ss[0], 3))
	{
		if (!g_t(g, &g->tex[t_cl], ss[1], t_cl))
			return (0);
		g->cl_color = 0;
	}
	return (1);
}

int	suite_g_t1(t_game *g, char **ss)
{
	if (!ft_strncmp("NO", ss[0], 3) && !g_t(g, &g->tex[t_no], ss[1], t_no))
		return (0);
	if (!ft_strncmp("SO", ss[0], 3) && !g_t(g, &g->tex[t_so], ss[1], t_so))
		return (0);
	if (!ft_strncmp("WE", ss[0], 3) && !g_t(g, &g->tex[t_we], ss[1], t_we))
		return (0);
	if (!ft_strncmp("EA", ss[0], 3) && !g_t(g, &g->tex[t_ea], ss[1], t_ea))
		return (0);
	if (!ft_strncmp("DO", ss[0], 3) && !g_t(g, &g->tex[t_do], ss[1], t_do))
		return (0);
	if (!ft_strncmp("D3", ss[0], 3) && !g_t(g, &g->tex[t_d3], ss[1], t_d3))
		return (0);
	if (!ft_strncmp("D4", ss[0], 3) && !g_t(g, &g->tex[t_d4], ss[1], t_d4))
		return (0);
	if (!ft_strncmp("D5", ss[0], 3) && !g_t(g, &g->tex[t_d5], ss[1], t_d5))
		return (0);
	if (!ft_strncmp("D6", ss[0], 3) && !g_t(g, &g->tex[t_d6], ss[1], t_d6))
		return (0);
	return (1);
}

int	get_texture2(t_game *g, char **ss)
{
	if (!suite_g_t1(g, ss))
		return (0);
	if (!suite_g_t2(g, ss))
		return (0);
	if (!ft_strncmp("F", ss[0], 2))
	{
		g->fl_color = get_color(ss[1]);
		if (!g->fl_color)
			return (0);
	}
	else if (!ft_strncmp("C", ss[0], 2))
	{
		g->cl_color = get_color(ss[1]);
		if (!g->cl_color)
			return (0);
	}
	return (1);
}

/*
   g_t(g, &g->tex[t_no], "./walls/beamskin3.xpm");
   g_t(g, &g->tex[t_so], "./walls/tile32.xpm");
   g_t(g, &g->tex[t_we], "./walls/tile105.xpm");
   g_t(g, &g->tex[t_ea], "./walls/steelwall6.xpm");
   g_t(g, &g->tex[t_do], "./walls/bigdoor.xpm");
   g_t(g, &g->tex[t_fl], "./walls/floorsteel.xpm");
   g_t(g, &g->tex[t_cl], "./walls/floorskin.xpm");
*/
void	order(t_game *g)
{
	g_t(g, &g->sp_tex[0], "./sprites/cobra0.xpm", -1);
	g_t(g, &g->sp_tex[1], "./sprites/cobra1.xpm", -1);
	g_t(g, &g->sp_tex[2], "./sprites/cobra2.xpm", -1);
	g_t(g, &g->sp_att[0], "./sprites/cobraatt0.xpm", -1);
	g_t(g, &g->sp_att[1], "./sprites/cobraatt1.xpm", -1);
	g_t(g, &g->sp_att[2], "./sprites/cobraatt2.xpm", -1);
	g_t(g, &g->sp_hit[0], "./sprites/cobrahit0.xpm", -1);
	g_t(g, &g->sp_hit[1], "./sprites/cobrahit1.xpm", -1);
	g_t(g, &g->sp_hit[2], "./sprites/cobrahit2.xpm", -1);
	g_t(g, &g->sp_hit[3], "./sprites/cobrahit3.xpm", -1);
	g_t(g, &g->sp_hit[4], "./sprites/cobrahit4.xpm", -1);
	g_t(g, &g->gun[0], "./guns/gun1a.xpm", -1);
	g_t(g, &g->gun[1], "./guns/gun1b.xpm", -1);
	g_t(g, &g->gun[2], "./guns/gun1c.xpm", -1);
	g_t(g, &g->tex[t_d3], "./sprites/crate.xpm", -1);
	g_t(g, &g->tex[t_d4], "./sprites/d_table.xpm", -1);
	g_t(g, &g->tex[t_d5], "./sprites/d_tree.xpm", -1);
	g_t(g, &g->tex[t_d6], "./sprites/i_health.xpm", -1);
}
