/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/13 09:59:38 by ngoc             ###   ########.fr       */
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
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# define WIDTH 1400
# define HEIGHT 1000
# define FOV 60

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
	int		bpp;
	int		ll;
	int		endian;
	int		dpp;
	char	*addr;
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
	int		dx;
	int		dy;
}	t_pos;

/*
mlx:
- bpp: bits par pixel
- ll: ...
- endian: ...
*/
typedef struct s_map {
	int		**v;
	int		h;
	int		l;
	int		bpp;
	int		ll;
	int		endian;
	int		dpp;
	char	*addr;
}	t_map;

/*
main:
- dpp : distance to Projection Plan
*/

typedef struct s_main {
	void	*mlx;
	void	*win;
	void	*img;
	int		**map;
	int		h;
	int		l;
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		bpp;
	int		ll;
	int		endian;
	int		dpp;
	char	*addr;
}	t_main;

#endif
