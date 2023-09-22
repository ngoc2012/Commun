/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:57:31 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/22 19:35:20 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	end_game(t_game *g, int exit_code, char *s)
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
	if (g->ai)
		free(g->ai);
	if (g->ai0)
		free(g->ai0);
	if (g->tan_ai)
		free(g->tan_ai);
	if (g->cos_ai)
		free(g->cos_ai);
	if (g->sin_ai)
		free(g->sin_ai);
	exit(exit_code);
}

void	init(t_game *g)
{
	g->map.h = 0;
	g->map.l = 0;
	g->map.ph = 0;
	g->map.pl = 0;
	g->pos.x = 0;
	g->pos.y = 0;
	g->pos.alpha = 90;
	g->pos.alpha = 90;
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
	g->tan_ai = 0;
	g->cos_ai = 0;
	g->sin_ai = 0;
	//printf("dpp %d\n", g->dpp);
}

int	precalcul(t_game *g)
{
	int		i;
	double	Xp;

	g->ai0 = malloc(sizeof(double) * WIDTH);
	//g->ai = malloc(sizeof(double) * WIDTH);
	i = -1;
	while (++i < WIDTH)
	{
		Xp = WIDTH / 2 - ix;
		g->ai0[i] = atan(Xp / g->dpp) * 180 / PI; 
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
	g.mlx.win = mlx_new_window(g.mlx.mlx, WIDTH, HEIGHT, "Cub3D");
	if (!g.mlx.mlx || !g.mlx.win)
		end_game(&g, EXIT_FAILURE, "Error mlx\n");
	mlx_key_hook(g.mlx.win, key_hook, &g);
	//mlx_mouse_hook(g.win, mouse_hook, p);
	//mlx_loop_hook(g.mlx, loop_hook, p);
	//mlx_hook(g.win, ClientMessage, LeaveWindowMask, &end_prog, p);
	g.mlx.img = mlx_new_image(g.mlx.mlx, WIDTH, HEIGHT);
	g.mlx.addr = mlx_get_data_addr(g.mlx.img, &g.mlx.bpp, &g.mlx.ll, &g.mlx.ed);
	if (!get_textures(&g))
		end_game(&g, EXIT_FAILURE, "Error textures load\n");
	draw(&g);
	mlx_loop(g.mlx.mlx);
}
