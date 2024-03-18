/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 23:48:08 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 15:33:36 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	on_keypress(int keysym, t_game *g)
{
	if (keysym == KEY_UP || keysym == KEY_W)
		g->cur_actions.up = 1;
	else if (keysym == KEY_DOWN || keysym == KEY_S)
		g->cur_actions.down = 1;
	else if (keysym == KEY_LEFT || keysym == KEY_A)
		g->cur_actions.left = 1;
	else if (keysym == KEY_RIGHT || keysym == KEY_D)
		g->cur_actions.right = 1;
	else if (keysym == KEY_SPACE)
		g->cur_actions.attack = 1;
	return (0);
}

int	on_keyrelease(int keysym, t_game *g)
{
	if (keysym == KEY_ESCAPE)
		on_destroy(g);
	else if (keysym == KEY_UP || keysym == KEY_W)
		g->cur_actions.up = 0;
	else if (keysym == KEY_DOWN || keysym == KEY_S)
		g->cur_actions.down = 0;
	else if (keysym == KEY_LEFT || keysym == KEY_A)
		g->cur_actions.left = 0;
	else if (keysym == KEY_RIGHT || keysym == KEY_D)
		g->cur_actions.right = 0;
	else if (keysym == KEY_SPACE)
		g->cur_actions.attack = 0;
	return (0);
}

int	render_game(t_game *g)
{
	int	x;
	int	y;

	if (!g)
		exit(EXIT_FAILURE);
	if (timestamp_in_ms(g) - g->updated_at < (uint64_t)(1000 / g->fps))
		return (0);
	g->updated_at = timestamp_in_ms(g);
	render_map(g);
	render_entities(g);
	update_score(g);
	x = (g->win.width - g->game_img.w) / 2;
	y = SPRITE_SIZE;
	mlx_put_image_to_window(g->game_img.win.mlx_ptr, g->game_img.win.win_ptr,
		g->game_img.img_ptr, x, y);
	return (0);
}

void	game_init(t_map *map)
{
	t_win	game_win;
	t_game	game;

	game_win = new_window(get_win_w(map), get_win_h(map), TITLE);
	game.moves = 0;
	game.cur_dir = STOPED;
	game.ents = NULL;
	game.cur_actions = (t_actions){0, 0, 0, 0, 0};
	game.map = map;
	game.created_at = gettimeofday_ms();
	game.updated_at = 0;
	game.fps = 64;
	game.win = game_win;
	game.game_img = new_img(get_map_w(game.map), get_map_h(game.map), game_win);
	game.score_img = new_img(100, 100, game_win);
	get_assets(&game);
	mlx_hook(game_win.win_ptr, KEY_PRESS, KEY_PRESS_MASK, &on_keypress, &game);
	mlx_hook(game_win.win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, &on_keyrelease,
		&game);
	mlx_hook(game_win.win_ptr, DESTROY_NOTIFY, STRUCT_NOTIFY_MASK, &on_destroy,
		&game);
	mlx_loop_hook(game_win.mlx_ptr, render_game, &game);
	ft_printf("Game initialized\n");
	mlx_loop(game_win.mlx_ptr);
}
