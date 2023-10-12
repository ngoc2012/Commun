/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/12 21:36:27 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	finish(char *s, int fd, t_game *g)
{
	free(s);
	close(fd);
	end_game(g, 1, "Error: Invalid Map\n");
}

void	call(t_game *g, char *fn)
{
	init_boxsize(g);
	for_check_map(g, fn);
	verif_wall(g);
}

void	check_cub(char *fn, t_game *g)
{
	int	p;

	p = 0;
	while (fn[p])
	{
		if (fn[p] == '.')
		{
			if (fn[p + 1] == 'c' && fn[p + 2]
				== 'u' && fn[p + 3] == 'b' && fn[p + 4] == '\0')
				return ;
			else
				end_game(g, 1, "Invalid .cub\n");
		}
		p++;
	}
}

void	final_check(t_game *g)
{
	if (g->map.h < 3 || g->map.l < 3)
		end_game(g, 1, "Error: map too small\n");
	if (!g->fl_color && !g->tex[t_fl].img)
		end_game(g, 1, "Error: No floor texture found\n");
	if (!g->cl_color && !g->tex[t_cl].img)
		end_game(g, 1, "Error: No ceiling texture found\n");

}

int	get_map(t_game *g, char *fn)
{
	int		fd;
	char	*s;

	fd = open(fn, O_RDONLY);
	if (fd == -1)
		return (0);
	check_cub(fn, g);
	s = get_next_line(fd);
	while (s)
	{
		if (check_map(s))
		{
			g->map.h++;
			if ((int) ft_strlen(s) - 1 > g->map.l)
				g->map.l = (int) ft_strlen(s) - 1;
		}
		free(s);
		s = get_next_line(fd);
	}
	close(fd);
	final_check(g);
	call(g, fn);
	return (1);
}
