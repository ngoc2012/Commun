/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/20 08:35:26 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>



# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include <pthread.h>
# include "mlx.h"
# include "ft_printf.h"
# include "libft.h"

# ifndef WIDTH
#  define WIDTH 600
# endif
# ifndef HEIGHT
#  define HEIGHT 400
# endif
# define MAX_ITER 1000
# define MIN_ITER 50
# define STEP_ITER 50
# ifndef ZOOM
#  define ZOOM 1.2
# endif
# ifndef MOVE
#  define MOVE 0.05
# endif
# ifndef RADIUS
#  define RADIUS 4
# endif
# ifndef THREADS
#  define THREADS 10
# endif
# define N_PALLETS 7
# define VAR_TYPE float
# ifndef CX
#  define CX 0.285
# endif
# ifndef CY
#  define CY 0.01
# endif

enum	e_fractal {JULIA, MANDELBROT};

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef	struct	s_viewport {
	VAR_TYPE	left;
	VAR_TYPE	right;
	VAR_TYPE	top;
	VAR_TYPE	bottom;
	VAR_TYPE	scale;
	int	**iters;
	VAR_TYPE	**xn;
	VAR_TYPE	**yn;
	VAR_TYPE	**colors;
}	t_viewport;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	t_img	*img;
	enum e_fractal	type;
	int	max_iter;
	int	in_process;
	VAR_TYPE	cx;
	VAR_TYPE	cy;
	VAR_TYPE	left;
	VAR_TYPE	right;
	VAR_TYPE	top;
	VAR_TYPE	bottom;
	VAR_TYPE	scale;
	int	pallet;
	int	smooth;
	t_viewport	vp0;
	//t_viewport	vp1;
}	t_vars;

typedef struct	s_thread
{
	unsigned char	id;
	t_vars		*vars;
	t_viewport	*vp;
}	t_thread;

void	draw(t_vars *vars, t_img *img);
int	**creat_vp(int h, int w);
void	del_vp(int **vp, int w);
VAR_TYPE	**creat_vp_d(VAR_TYPE h, int w);
void	del_vp_d(VAR_TYPE **vp, int w);
void	cal(t_vars *vars, t_viewport *vp);
void	cal2(t_vars *vars, t_viewport *vp);
void	colors(t_vars *vars, t_viewport *vp);

#endif
