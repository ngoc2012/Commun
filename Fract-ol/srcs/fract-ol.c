/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/27 21:32:46 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	help(void)
{
	ft_printf("./fract-ol Julia\n");
	ft_printf("./fract-ol Mandelbrot\n");
}

// https://en.m.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set
int	main(int argc, char **argv)
{
	t_vars	vars;

	help();
	if (argc != 2)
		exit(EXIT_SUCCESS);
	if (ft_strncmp(argv[1], "Julia", 6) == 0)
		init_julia(&vars);
	else if (ft_strncmp(argv[1], "Mandelbrot", 11) == 0)
		init_mandel(&vars);
	else if (ft_strncmp(argv[1], "Burn", 5) == 0)
		init_burn(&vars);
	else
	{
		ft_printf("Fractal %s unknown???\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	init_data(&vars);
	secure_data(&vars);
	init_pallets(&vars);
	init_graph(&vars, argv[1]);
	while (1)
	{
		ft_printf("Update");
		sleep(1);
	}
}
