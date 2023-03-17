/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/17 08:33:16 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>



# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include "mlx.h"
# include "ft_printf.h"
# include "libft.h"

# define MAX_ITER 100
# define ZOOM 1.2

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
	double	vp1_tl_x;
	double	vp1_tl_y;
	double	vp1_br_x;
	double	vp1_br_y;
	int	**vp0;
	int	**vp1;
}	t_vars;

void	draw(t_vars *vars, t_img *img);
int	**creat_vp(int h, int w);
void	del_vp(int **vp, int w);
double	**creat_vp_d(double h, int w);
void	del_vp_d(double **vp, int w);

#endif
