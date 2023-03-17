/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/17 12:22:21 by minh-ngu         ###   ########.fr       */
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

# define WIDTH 399
# define HEIGHT 401
# define MAX_ITER 1000
# define MIN_ITER 100
# define ZOOM 1.2
# define RADIUS 4

enum	e_fractal {JULIA, MANDELBROT};

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef	struct	s_viewport {
	double	left;
	double	right;
	double	top;
	double	bottom;
	double	scale;
	int	**iters;
	double	**xn;
	double	**yn;
}	t_viewport;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	t_img	*img;
	enum e_fractal	type;
	int	max_iter;
	int	in_process;
	double	left;
	double	right;
	double	top;
	double	bottom;
	double	scale;
	t_viewport	vp0;
	//t_viewport	vp1;
}	t_vars;

void	draw(t_vars *vars, t_img *img);
int	**creat_vp(int h, int w);
void	del_vp(int **vp, int w);
double	**creat_vp_d(double h, int w);
void	del_vp_d(double **vp, int w);
void	cal(t_vars *vars, t_viewport *vp);

#endif
