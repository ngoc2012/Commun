/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/23 11:01:34 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_array(double **a, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(a[i]);
	free(a);
}

int	end_game(t_game *g, int exit_code, char *s)
{
	if (g->tex_n.img)
		mlx_destroy_image(g->mlx.mlx, g->tex_n.img);
	if (g->tex_s.img)
		mlx_destroy_image(g->mlx.mlx, g->tex_s.img);
	if (g->tex_w.img)
		mlx_destroy_image(g->mlx.mlx, g->tex_w.img);
	if (g->tex_e.img)
		mlx_destroy_image(g->mlx.mlx, g->tex_e.img);
	if (g->tex_f.img)
		mlx_destroy_image(g->mlx.mlx, g->tex_f.img);
	if (g->tex_c.img)
		mlx_destroy_image(g->mlx.mlx, g->tex_c.img);
	if (g->mlx.img)
		mlx_destroy_image(g->mlx.mlx, g->mlx.img);
	mlx_destroy_window(g->mlx.mlx, g->mlx.win);
	mlx_destroy_display(g->mlx.mlx);
	free(g->mlx.mlx);
	free_map(&g->map);
	if (s)
		perror(s);
		//ft_putstr_fd(s, 2);
	if (g->ai0)
		free(g->ai0);
	if (g->cos_ai0)
		free(g->cos_ai0);
	if (g->ai)
		free_array(g->ai, WIDTH);
	if (g->tan_ai)
		free_array(g->tan_ai, WIDTH);
	if (g->cos_ai)
		free_array(g->cos_ai, WIDTH);
	if (g->sin_ai)
		free_array(g->sin_ai, WIDTH);
	exit(exit_code);
	return (1);
}

void	init(t_game *g)
{
	g->map.h = 0;
	g->map.l = 0;
	g->map.ph = 0;
	g->map.pl = 0;
	g->pos.x = 0;
	g->pos.y = 0;
	g->pos.rot = 0;
	g->dpp = (int) WIDTH / 2 / tan(PI /180 * FOV / 2);
	g->tex_n.img = 0;
	g->tex_s.img = 0;
	g->tex_w.img = 0;
	g->tex_e.img = 0;
	g->tex_f.img = 0;
	g->tex_c.img = 0;
	g->mlx.img = 0;
	g->ai = 0;
	g->ai0 = 0;
	g->cos_ai0 = 0;
	g->tan_ai = 0;
	g->cos_ai = 0;
	g->sin_ai = 0;
	//printf("dpp %d\n", g->dpp);
}

int	precalcul(t_game *g)
{
	int		i;
	int		j;
	double	Xp;

	g->ai0 = malloc(sizeof(double) * WIDTH);
	g->cos_ai0 = malloc(sizeof(double) * WIDTH);
	g->ai = malloc(sizeof(double *) * WIDTH);
	g->tan_ai = malloc(sizeof(double *) * WIDTH);
	g->cos_ai = malloc(sizeof(double *) * WIDTH);
	g->sin_ai = malloc(sizeof(double *) * WIDTH);
	i = -1;
	while (++i < WIDTH)
	{
		Xp = WIDTH / 2 - i + 0.5;
		g->ai0[i] = atan(Xp / g->dpp) * 180.0 / PI; 
		g->cos_ai0[i] = 1 / cos(g->ai0[i] * PI /180.0); 
		g->ai[i] = malloc(sizeof(double) * 360.0 / ROT_SPEED);
		g->tan_ai[i] = malloc(sizeof(double) * 360.0 / ROT_SPEED);
		g->cos_ai[i] = malloc(sizeof(double) * 360.0 / ROT_SPEED);
		g->sin_ai[i] = malloc(sizeof(double) * 360.0 / ROT_SPEED);
		j = -1;
		while (++j < 360 / ROT_SPEED)
		{
			g->ai[i][j] = angle_convert(j * ROT_SPEED + g->ai0[i]);
			g->tan_ai[i][j] = tan(g->ai[i][j] * PI / 180.0);
			g->cos_ai[i][j] = cos(g->ai[i][j] * PI / 180.0);
			g->sin_ai[i][j] = sin(g->ai[i][j] * PI / 180.0);
		}
	}
	//ai = g->pos.alpha + ai0;
	//ai = angle_convert(ai);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	g;

	(void) argc;
	init(&g);
	if (!get_map(&g, argv[1]) || !precalcul(&g))
		end_game(&g, EXIT_FAILURE, "Error map or memories\n");
	g.mlx.mlx = mlx_init();
	g.mlx.win = mlx_new_window(g.mlx.mlx, WIDTH * SCALE, HEIGHT * SCALE, "Cub3D");
	if (!g.mlx.mlx || !g.mlx.win)
		end_game(&g, EXIT_FAILURE, "Error mlx\n");
	mlx_key_hook(g.mlx.win, key_hook, &g);
	//mlx_mouse_hook(g.win, mouse_hook, p);
	//mlx_loop_hook(g.mlx, loop_hook, p);
	mlx_hook(g.mlx.win, ClientMessage, LeaveWindowMask, &end_game, &g);
	g.mlx.img = mlx_new_image(g.mlx.mlx, WIDTH * SCALE, HEIGHT * SCALE);
	g.mlx.addr = mlx_get_data_addr(g.mlx.img, &g.mlx.bpp, &g.mlx.ll, &g.mlx.ed);
	if (!get_textures(&g))
		end_game(&g, EXIT_FAILURE, "Error textures load\n");
	draw(&g);
	mlx_loop(g.mlx.mlx);
}
