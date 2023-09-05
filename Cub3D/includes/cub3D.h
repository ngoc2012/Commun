/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/05 07:10:00 by ngoc             ###   ########.fr       */
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

# ifndef WIDTH
#  define WIDTH 1400
# endif
# ifndef HEIGHT
#  define HEIGHT 1000
# endif

typedef struct s_prog {
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
	char	*addr;
}	t_prog;

#endif
