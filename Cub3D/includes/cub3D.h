/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/18 17:33:32 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include <stdio.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# define WIDTH 1400
# define HEIGHT 1000
# define FOV 60
# define BOX_SIZE 64
# define SPEED 4

/*
Map:
- v: value 0,1
- h: height of map
- l: length of map
*/
typedef struct s_map {
	int		**v;
	int		h;
	int		l;
}	t_map;

/*
Player position
- x: position x
- y: position y
- dx: direction x
- dy: direction y
*/
typedef struct s_pos {
	int		x;
	int		y;
	int		px;
	int		py;
	double		dx;
	double		dy;
}	t_pos;

/*
mlx:
- bpp: bits par pixel
- ll: ...
- ed: endian
*/
typedef struct s_mlx {
	void	*mlx;
	void	*win;
	void	*img;
	int		bpp;
	int		ll;
	int		ed;
	char	*addr;
}	t_mlx;

/*
main:
- dpp : distance to Projection Plan
*/
typedef struct s_game {
	t_map		map;
	t_pos		pos;
	t_mlx		mlx;
	int		dpp;
}	t_game;

void	free_map(t_map *m);
void	get_map(t_game *g, char *fn);
void	draw(t_game *g);

int	key_hook(int keycode, t_game *g);
void	end_game(t_game *g, int exit_code, char *s);
void	draw_mini_map(t_game *g);

#endif
