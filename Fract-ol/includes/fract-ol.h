/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/14 11:38:51 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTO_H

# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include "mlx.h"
# include "ft_printf.h"
# include "libft.h"

# define MAX_ITER 200

enum	e_fractal {JULIA, MANDELBROT};

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	t_img	*img;
	enum e_fractal	type;
	int	w;
	int	h;
	int	max_iter;
	int	min_iter;
	int	in_process;
	double	scale;
	double	left;
	double	top;
	double	cx;
	double	cy;
}	t_vars;

void	draw(t_vars *vars, t_img *img);

#endif
