/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 05:38:38 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/13 15:44:26 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	return_error(char *s, char **ss)
{
	free_array_str(&ss, 0);
	free(s);
	return (0);
}

int	get_color(char *s)
{
	int		i;
	int		c[3];
	char	**ss;

	ss = ft_split(s, ',');
	i = -1;
	while (ss[++i] && i < 4)
	{
		if (ft_strlen(ss[i]) > 3)
			return (free_array_str(&ss, 0));
		c[i] = ft_atoi(ss[i]);
		if (c[i] > 255 || c[i] < 0)
			return (free_array_str(&ss, 0));
	}
	if (i != 3)
		return (free_array_str(&ss, 0));
	free_array_str(&ss, 0);
	return (create_trgb(1, (unsigned int) c[0],
			(unsigned int) c[1], (unsigned int) c[2]));
}

int	get_texture_norm(char *s, t_game *g)
{
	int		i;
	char	**ss;

	i = -1;
	while (s[++i])
		if (s[i] == '	')
			s[i] = ' ';
	s[ft_strlen(s) - 1] = 0;
	ss = ft_split(s, ' ');
	if (ss && ss[0] && !check_map(s))
	{
		if (!ss[1])
			return (free_array_str(&ss, 0));
		if (ss[2])
			return (free_array_str(&ss, 0));
		if (!get_texture2(g, ss))
			return (free_array_str(&ss, 0));
	}
	return (free_array_str(&ss, 1));
}

void	end_texture(t_game *g)
{
	int	i;

	if (!g->fl_color && !g->tex[t_fl].img)
		end_game(g, 1, "Error: No floor texture found\n");
	if (!g->cl_color && !g->tex[t_cl].img)
		end_game(g, 1, "Error: No ceiling texture found\n");
	i = -1;
	while (++i < 5)
		if (!g->tex[i].img)
			end_game(g, 1, "Error: No wall texture found\n");
}

int	get_textures(t_game *g, char *fn)
{
	int		fd;
	char	*s;
	char	*s0;

	order(g);
	fd = open(fn, O_RDONLY);
	if (fd == -1)
		return (0);
	s = get_next_line(fd);
	while (s)
	{
		s0 = s;
		while (ft_strchr(" 	\n", *s))
			s++;
		if (ft_strlen(s) > 1 && !get_texture_norm(s, g))
		{
			free(s0);
			return (0);
		}
		free(s0);
		s = get_next_line(fd);
	}
	close(fd);
	end_texture(g);
	return (1);
}
