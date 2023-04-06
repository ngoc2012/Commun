/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/30 14:01:35 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	end_prog(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	del_vp(vars->iters, WIDTH);
	del_vp_d(vars->xn, WIDTH);
	del_vp_d(vars->yn, WIDTH);
	del_vp_d(vars->colors, WIDTH);
	free(vars->img0);
	exit(EXIT_SUCCESS);
}

void	help(void)
{
	ft_printf("./fract-ol Julia\n");
	ft_printf("./fract-ol Mandelbrot\n");
	ft_printf("./fract-ol Burn\n");
	ft_printf("./fract-ol Sier\n");
}

// https://en.m.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set
int	main(int argc, char **argv)
{
	t_vars	vars;

	help();
	if (argc != 2)
		exit(EXIT_SUCCESS);
	if (ft_strncmp(argv[1], "Julia", 6) == 0)
		vars.type = e_julia;
	else if (ft_strncmp(argv[1], "Mandelbrot", 11) == 0)
		vars.type = e_mandelbrot;
	else if (ft_strncmp(argv[1], "Burn", 5) == 0)
		vars.type = e_burn;
	else if (ft_strncmp(argv[1], "Sier", 5) == 0)
		vars.type = e_sier;
	else
	{
		ft_printf("Fractal %s unknown???\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	init_data(&vars);
	secure_data(&vars);
	init_pallets(&vars);
	init_graph(&vars, argv[1]);
}
