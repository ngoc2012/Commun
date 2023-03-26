/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/03/26 12:30:30 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	**creat_vp(int h, int w)
{
	int	**vp;
	int	i;
	int	j;

	vp = malloc(sizeof(int*) * w);
	if (!vp)
		return (0);
	i = -1;
	while (++i < w)
	{
		vp[i] = malloc(sizeof(int) * h);
		if (!vp[i])
		{
			j = -1;
			while (++j < i)
				free(vp[i]);
			free(vp);
			return (0);
		}
	}
	return (vp);
}

void	del_vp(int **vp, int w)
{
	int	i;

	i = -1;
	while (++i < w)
		free(vp[i]);
	free(vp);
}

VAR_TYPE	**creat_vp_d(VAR_TYPE h, int w)
{
	VAR_TYPE	**vp;
	int	i;
	int	j;

	vp = malloc(sizeof(VAR_TYPE*) * w);
	if (!vp)
		return (0);
	i = -1;
	while (++i < w)
	{
		vp[i] = malloc(sizeof(VAR_TYPE) * h);
		if (!vp[i])
		{
			j = -1;
			while (++j < i)
				free(vp[i]);
			free(vp);
			return (0);
		}
	}
	return (vp);
}

void	del_vp_d(VAR_TYPE **vp, int w)
{
	int	i;

	i = -1;
	while (++i < w)
		free(vp[i]);
	free(vp);
}

void	help()
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
	else
	{
		ft_printf("Fractal %s unknown???\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	init_data(&vars);
	init_graph(&vars, argv[1]);
	while (1)
	{
		ft_printf("Update");
		sleep(1);
	}
}
