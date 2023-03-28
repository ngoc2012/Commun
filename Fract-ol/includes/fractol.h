/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/28 22:00:49 by ngoc             ###   ########.fr       */
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

# ifndef WIDTH
#  define WIDTH 700
# endif
# ifndef HEIGHT
#  define HEIGHT 500
# endif
# define MAX_ITER 1000
# define MIN_ITER 50
# define STEP_ITER 50
# ifndef ZOOM
#  define ZOOM 1.1
# endif
# ifndef MOVE
#  define MOVE 0.05
# endif
# ifndef RADIUS
#  define RADIUS 4
# endif
# ifndef THREADS
#  define THREADS 8
# endif
# define N_PALLETS 7
# define VAR_TYPE float
# ifndef CX
#  define CX 0.285
# endif
# ifndef CY
#  define CY 0.01
# endif
# define N_FRACTALS 4

enum	e_fractal {e_julia, e_mandelbrot, e_burn, e_sier};

typedef struct s_coor_d {
	VAR_TYPE	x;
	VAR_TYPE	y;
}	t_coor_d;

typedef struct s_coor {
	int	x;
	int	y;
}	t_coor;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}	t_img;

typedef struct s_sier
{
	VAR_TYPE	a;
	int	l;
	t_coor_d	c;
	t_coor_d	p;
}	t_sier;

typedef struct s_pallet {
	int			d;
	VAR_TYPE	val[12][3];
}	t_pallet;

typedef struct s_fractal {
	enum e_fractal	f[N_FRACTALS];
}	t_fractal;

typedef struct s_vars {
	void			*mlx;
	void			*win;
	t_img			*img;
	int				*img0;
	enum e_fractal	type;
	int				max_iter;
	VAR_TYPE		cx;
	VAR_TYPE		cy;
	VAR_TYPE		left;
	VAR_TYPE		right;
	VAR_TYPE		top;
	VAR_TYPE		bottom;
	VAR_TYPE		scale;
	int				smooth;
	int				**iters;
	VAR_TYPE		**xn;
	VAR_TYPE		**yn;
	VAR_TYPE		**colors;
	int				pallet;
	t_pallet		pallets[N_PALLETS];
	t_fractal	fractals;
	VAR_TYPE		log_2;
	VAR_TYPE		log_r;
	t_sier		start;
}	t_vars;

void		init_data(t_vars *vars);
void		secure_data(t_vars *vars);
void		init_graph(t_vars *vars, char *w_name);
void		init_pallets(t_vars *vars);
void		init_julia(t_vars *vars);
void		init_mandel(t_vars *vars);
void		init_burn(t_vars *vars);
void		init_sier(t_vars *vars);
void		init_draw(t_vars *vars);
int			key_hook(int keycode, t_vars *vars);
int			mouse_hook(int button, int px, int py, t_vars *vars);
int			end_prog(t_vars *vars);
void		draw(t_vars *vars, t_img *img);
void		draw_sier(t_vars *vars);
int			**creat_vp(int h, int w);
void		del_vp(int **vp, int w);
VAR_TYPE	**creat_vp_d(VAR_TYPE h, int w);
void		del_vp_d(VAR_TYPE **vp, int w);
int			get_color(t_vars *vars, VAR_TYPE value);
void		colors(t_vars *vars, int xp, int yp, int R2);
void		colors_v(t_vars *vars, int start_x, int end_x);
void		colors_h(t_vars *vars, int start_y, int end_y);
void		cal(t_vars *vars, int xp, int yp, int R2);
void		cal_v(t_vars *vars, int start_x, int end_x);
void		cal_h(t_vars *vars, int start_y, int end_y);
void		julia(t_vars *vars, int xp, int yp, int R2);
void		mandel(t_vars *vars, int xp, int yp, int R2);
void		set_env(VAR_TYPE zoom, int px, int py, t_vars *vars);
void		set_zoom(t_vars *vars);
void		move_up(int dp, t_vars *vars);
void		move_down(int dp, t_vars *vars);
void		move_left(int dp, t_vars *vars);
void		move_right(int dp, t_vars *vars);
void		move_val(t_vars *vars, t_coor *p, int dx, int dy);
void		draw_p(t_vars *vars, t_coor *p, int *addr, int r2);
void		sier(t_vars *vars, t_sier *r);
VAR_TYPE	color_julia(t_vars *vars, int xp, int yp, int R2);
VAR_TYPE	color_mandel(t_vars *vars, int xp, int yp);

#endif
