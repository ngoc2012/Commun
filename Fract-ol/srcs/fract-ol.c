/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/14 07:10:41 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>
#include "mlx.h"
#include "ft_printf.h"
#include "libft.h"

#include <stdio.h>


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
	double	scale;
	double	left;
	double	top;
}	t_vars;

int	end_prog(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, t_vars *vars)
{
	//ft_printf("keycode: %d\n", keycode);
	if (keycode == XK_q || keycode == 65507 || keycode == XK_Escape)
		end_prog(vars);
	return (0);
}

/*
int	mouse_hook(int button, int, int, t_vars *)
{
	//ft_printf("Button: %d\n", button);
	return (0);
}
*/

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}


/*
typedef struct	s_color	t_color;

struct	s_color
{
	float	r;
	float	g;
	float	b;
	float	t;
	void	(*set)(t_color *, float r, float g, float b, float t);
	int	(*convert_bits)(t_color *);
};

void	set_color(t_color *c, float r, float g, float b, float t);
{
	c.r = r;
	c.g = g;
	c.b = b;
	c.t = t;
}

int	(*convert_bits)(t_color *);
t_color	*new_color(float r, float g, float b, float t)
{
	new = malloc(sizeof(t_color));
	if (!new)
		return (0);
	new->set = set_color;
	new->convert_bits = convert_bits;
}
*/


int	get_color(int iterations, int max_iterations)
{
	int		above;
	int		under;
	int		dim = 6;
	float	value = (float) iterations / max_iterations;
 	float	pallet[6][4] = {
		{  0.,   7., 100., 1.},
		{ 32., 107., 203., 1.},
		{237., 255., 255., 1.},
		{255., 170.,   0., 1.},
		{  0.,   2.,   0., 1.},
		{  0.,   7., 100., 1.}
	};
//		{ 20.,   0.,   0., 1.},
//		{255.,  20.,   0., 1.},
//		{255., 200.,   0., 1.},
//		{255.,  20.,   0., 1.},
//		{ 20.,   0.,   0., 1.}
//	};
//{  0.,   0.,   0., 1.},
//{  0.,   0., 200., 1.},
//{255., 255., 255., 1.},
//{  0.,   0., 200., 1.},
//{  0.,   0.,   0., 1.}
//	};

	above = (int) (value * (float) dim);
	if (above == dim)
		above = dim - 1;
	under = above - 1;
	float	p;
	p = value * (float) dim - (float) under;
	return (create_trgb((int) pallet[under][0] + p * (pallet[above][0] - pallet[under][0]),
	(int) pallet[under][1] + p * (pallet[above][1] - pallet[under][1]),
	(int) pallet[under][2] + p * (pallet[above][2] - pallet[under][2]),
	(int) pallet[under][3] + p * (pallet[above][3] - pallet[under][3])));
}

void	draw(t_vars *vars, t_img *img, double cx, double cy)
{
	double   x;
	double   y;
	double   x0;
	double   y0;
	double   xtemp;
	int	xp;
	int	yp;
	int	i;

	xp = 0;
	while (++xp < vars->w)
	{
		yp = 0;
		while (++yp < vars->h)
		{
			x0 = vars->scale * xp - vars->left + cx;
			y0 = vars->scale * yp - vars->top + cy;
			i = -1;
			if (vars->type == JULIA)
			{
				x = x0;
				y = y0;
				while (x * x + y * y < 4 && ++i < vars->max_iter)
				{
					xtemp = x;
					x = x * x - y * y - 1;
					y = 2 * xtemp * y;
				}
			}
			else if (vars->type == MANDELBROT)
			{
				x = 0.0;
				y = 0.0;
				while (x * x + y * y < 4 && ++i < vars->max_iter)
				{
					xtemp = x * x - y * y + x0;
					y = 2 * x * y + y0;
					x = xtemp;
				}
			}
			//v = math.pow(math.pow(i/max_iter, S) * N, 1.5) % N;
			//v = i / max_iter;
			//my_mlx_pixel_put(&img-> xp, yp, create_trgb(0, v * 255, v * 255, v * 255));
			//ft_printf("i = %d\n", i);
			if (i == vars->max_iter)
				my_mlx_pixel_put(img, xp, yp, get_color(i, vars->max_iter));
			else
				my_mlx_pixel_put(img, xp, yp, get_color(i, vars->max_iter));
		}
	}
	ft_printf("Done\n");
}

// https://en.m.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set
int	main(int argc, char **argv)
{
	t_vars	vars;
	t_img	img;

	if (argc != 2)
		exit(EXIT_SUCCESS);
	if (ft_strncmp(argv[1], "JULIA", 6) == 0)
		vars.type = JULIA;
	else if (ft_strncmp(argv[1], "MANDELBROT", 11) == 0)
		vars.type = MANDELBROT;
	else
	{
		ft_printf("Fractal %s unknown???\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	vars.w = 500;
	vars.h = 500;
	vars.max_iter = 100;
	vars.scale = (double) 4 / vars.w;
	vars.left = vars.scale * vars.w / 2;
	vars.top = vars.scale * vars.h / 2;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.w, vars.h, argv[1]);
	if (!vars.mlx || !vars.win)
		exit(EXIT_FAILURE);
	mlx_key_hook(vars.win, key_hook, &vars);
	//mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_hook(vars.win, ClientMessage, LeaveWindowMask, &end_prog, &vars);
	img.img = mlx_new_image(vars.mlx, vars.w, vars.h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw(&vars, &img, 0.0, 0.0);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	vars.img = &img;
	mlx_loop(vars.mlx);
}
