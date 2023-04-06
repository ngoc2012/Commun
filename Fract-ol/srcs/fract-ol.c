/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 09:21:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/04/06 15:47:34 by minh-ngu         ###   ########.fr       */
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
	ft_printf("./fract-ol Mandelbrot\n");
	ft_printf("./fract-ol Mandelbrot 50\n");
	ft_printf("./fract-ol Burn\n");
	ft_printf("./fract-ol Burn 50\n");
	ft_printf("./fract-ol Sier\n");
	ft_printf("./fract-ol Julia\n");
	ft_printf("./fract-ol Julia 7269 1889\n");
	ft_printf("./fract-ol Julia 7269 1889 100\n");
	ft_printf("Julia parametres will be devided by 10000\n");
}

char	*get_str(char *s)
{
	char	*s0;
	char	sign;

	sign = 0;
	if (*s == '+' || *s == '-')
		sign = *s++;
	if (*s == 0)
		exit(EXIT_FAILURE);
	while (*s == '0' && s[1] != 0)
		s++;
	s0 = s;
	while (*s)
		if (!ft_isdigit(*s++))
			exit(EXIT_FAILURE);
	if (sign == '-' && ft_strncmp(s0, "0", 2) != 0)
		*(--s0) = sign;
	return (s0);
}

void	get_args(int argc, char **argv, t_vars *vars)
{
	if (vars->type == e_julia)
	{
		if (argc == 4 || argc == 5)
		{
			vars->cx = (VAR_TYPE) ft_atoi(get_str(argv[2])) / 10000.0;
			vars->cy = (VAR_TYPE) ft_atoi(get_str(argv[3])) / 10000.0;
			if (argc == 5)
				vars->max_iter = ft_atoi(get_str(argv[4]));
		}
	}
	else if (argc == 3)
		vars->max_iter = ft_atoi(get_str(argv[2]));
	if (vars->max_iter < MIN_ITER || vars->max_iter > MAX_ITER)
		exit(EXIT_FAILURE);
}

// https://en.m.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set
int	main(int argc, char **argv)
{
	t_vars	vars;

	help();
	if (argc < 2)
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
		exit(EXIT_FAILURE);
	vars.cx = CX;
	vars.cy = CY;
	vars.max_iter = MIN_ITER;
	get_args(argc, argv, &vars);
	init_data(&vars);
	secure_data(&vars);
	init_pallets(&vars);
	init_graph(&vars, argv[1]);
}
