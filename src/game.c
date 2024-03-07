/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 23:48:08 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/08 00:06:55 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void get_assets(t_game *g)
{
	g->static_assets.wall = new_file_img(WALL_PATH, g->win);
	g->static_assets.floor = new_file_img(FLOOR_PATH, g->win);
}

void destroy_assets(t_game *g)
{
	destroy_image(g->static_assets.wall);
	destroy_image(g->static_assets.floor);
}

int	on_destroy(t_game *game)
{
	if (!game)
		exit(EXIT_FAILURE);
	ft_putstr_fd("Exiting game\n", 1);
	free_map(game->map);
	destroy_assets(game);
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

int get_px(int x, t_game *g)
{
	if (x < 0 || x >= g->map->cols)
		return (-1);
	return (x * SPRITE_SIZE);
}

int get_py(int y, t_game *g)
{
	if (y < 0 || y >= g->map->rows)
		return (-1);
	return (y * SPRITE_SIZE);
}

void render_map(t_game *g)
{
	int		x;
	int		y;

	x = 0;
	while (x < g->map->cols)
	{
		y = 0;
		while (y < g->map->rows)
		{
			if (g->map->map[y][x] == '1')
				put_img_to_img(g->game_img, g->static_assets.wall, get_px(x, g), get_py(y, g));
			else
				put_img_to_img(g->game_img, g->static_assets.floor, get_px(x, g), get_py(y, g));
			y++;
		}
		x++;
	}
}

void	render_game(t_game *g)
{
	int		x;
	int		y;

	render_map(g);
	x = (g->win.width - g->game_img.w) / 2;
	y = SPRITE_SIZE;
	mlx_put_image_to_window(g->game_img.win.mlx_ptr, g->game_img.win.win_ptr,
		g->game_img.img_ptr, x, y);
}

void	game_init(t_map *map)
{
	t_win	game_win;
	t_game	game;

	game.map = map;
	game_win = new_window(get_win_w(game), get_win_h(game), TITLE);
	ft_putstr_fd("Game initialized\n", 1);
	game.win = game_win;
	game.game_img = new_img(get_map_w(game.map), get_map_h(game.map), game_win);
	get_assets(&game);
	mlx_hook(game_win.win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, &on_keypress,
		&game);
	mlx_hook(game_win.win_ptr, DESTROY_NOTIFY, STRUCT_NOTIFY_MASK, &on_destroy,
		&game);
	render_game(&game);
	mlx_loop(game_win.mlx_ptr);
}
