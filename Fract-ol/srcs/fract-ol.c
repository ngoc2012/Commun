/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/12 17:34:54 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>
#include "mlx.h"
#include "ft_printf.h"
#include "libft.h"

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

enum	e_fractal {JULIA, MANDELBROT};

/*
float4 get_color(float iterations, float max_iterations, float4* pallet, int colors_nb)
{
    float value = iterations / max_iterations;
    float4 color = (float4)(1.f, 1.f, 1.f, 1.f);

    float min_value;
    float max_value;

    for (int i = 0; i < (int)colors_nb; i++)
    {
        min_value = (float)i / colors_nb;
        max_value = (float)(i + 1) / colors_nb;

        if (value >= min_value && value <= max_value)
        {
            color = mix(pallet[i], pallet[i + 1], (value - min_value) * colors_nb);
            break;
        }
    }

    return color;
}
*/

// https://en.m.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set
int	main(int argc, char **argv)
{
	double   x;
	double   y;
	double   x0;
	double   y0;
	double   xtemp;
	//double   ytemp;
	double	scale;
	//double	v;
	int	xp;
	int	yp;
	int	w;
	int	h;
	int	i;
	int	max_iter;
	t_img	img;
	t_vars	vars;
	enum e_fractal	type;

	if (argc != 2)
		exit(EXIT_SUCCESS);
	if (ft_strncmp(argv[1], "JULIA", 6) == 0)
		type = JULIA;
	else if (ft_strncmp(argv[1], "MANDELBROT", 11) == 0)
		type = MANDELBROT;
	else
	{
		ft_printf("Fractal %s unknown???\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	w = 500;
	h = 500;
	max_iter = 100;
	//S = 10;
	//N = 100;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, w, h, argv[1]);
	if (!vars.mlx || !vars.win)
		exit(EXIT_FAILURE);
	mlx_key_hook(vars.win, key_hook, &vars);
	//mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_hook(vars.win, ClientMessage, LeaveWindowMask, &end_prog, &vars);
	img.img = mlx_new_image(vars.mlx, w, h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	scale = (double) 4 / w;
	xp = 0;
	while (++xp < w)
	{
		yp = 0;
		while (++yp < h)
		{
			x0 = scale * (xp - w / 2);
			y0 = scale * (yp - h / 2);
			i = -1;
			if (type == JULIA)
			{
				x = x0;
				y = y0;
				while (x * x + y * y < 4 && ++i < max_iter)
				{
					xtemp = x;
					x = x * x - y * y - 1;
					y = 2 * xtemp * y;
				}
			}
			else if (type == MANDELBROT)
			{
				x = 0.0;
				y = 0.0;
				while (x * x + y * y < 4 && ++i < max_iter)
				{
					xtemp = x * x - y * y + x0;
					y = 2 * x * y + y0;
					x = xtemp;
				}
			}
			//v = math.pow(math.pow(i/max_iter, S) * N, 1.5) % N;
			//v = i / max_iter;
			//my_mlx_pixel_put(&img, xp, yp, create_trgb(0, v * 255, v * 255, v * 255));
			//ft_printf("i = %d\n", i);
			if (i == max_iter)
				my_mlx_pixel_put(&img, xp, yp, create_trgb(0, 0, 0, 0));
			else
				my_mlx_pixel_put(&img, xp, yp, create_trgb(0, 255, 255, 255));
		}
	}
	ft_printf("Modulos: %.2f\n", sin(2.3));
	ft_printf("Done\n");
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	vars.img = &img;
	mlx_loop(vars.mlx);
}
