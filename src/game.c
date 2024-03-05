/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 23:48:08 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/05 19:20:04 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	on_destroy(t_game *game)
{
	if (!game)
		exit(EXIT_FAILURE);
	ft_putstr_fd("Exiting game\n", 1);
	free_map(game->map);
	destroy_image(game->game_img);
	destroy_window(game->win);
	exit(0);
}

int	on_keypress(int keysym, t_game *g)
{
	(void)g;
	if (keysym == KEY_ESCAPE)
	{
		printf("The %d key (ESC) has been pressed\n\n", keysym);
		on_destroy(g);
	}
	printf("Pressed key: %d\n", keysym);
	return (0);
}

void	draw_map(t_game *g)
{
	int		px;
	int		py;
	t_img	img;

	img = new_file_img(WALL_PATH, g->win);
	px = 1;
	py = 1;
	while (px < g->map->cols * img.w)
	{
		while (py < g->map->rows * img.h)
		{
			put_img_to_img(g->game_img, img, px, py);
			py += img.h;
		}
		px += img.w;
		py = 0;
	}
	put_img_to_img(g->game_img, img, px, py);
	mlx_put_image_to_window(g->game_img.win.mlx_ptr, g->game_img.win.win_ptr,
		g->game_img.img_ptr, 0, 0);
	destroy_image(img);
}

void	game_init(t_map *map)
{
	t_win	game_win;
	t_game	game;

	game.map = map;
	game_win = new_window(SIZE * game.map->cols, SIZE * game.map->rows,
			"animations");
	ft_putstr_fd("Game initialized\n", 1);
	game.win = game_win;
	game.game_img = new_img(game_win.width, game_win.height, game_win);
	mlx_hook(game_win.win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, &on_keypress,
		&game);
	mlx_hook(game_win.win_ptr, DESTROY_NOTIFY, STRUCT_NOTIFY_MASK, &on_destroy,
		&game);
	draw_map(&game);
	mlx_loop(game_win.mlx_ptr);
}
