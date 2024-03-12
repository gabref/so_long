/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 23:48:08 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/12 15:04:25 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"
#include <sys/time.h>

uint64_t	gettimeofday_ms(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

uint64_t	timestamp_in_ms(t_game *game)
{
	if (!game)
		return (0);
	if (game->created_at == 0)
		game->created_at = gettimeofday_ms();
	return (gettimeofday_ms() - game->created_at);
}

int	get_px(int x, t_game *g)
{
	if (x < 0 || x >= g->map->cols)
		return (-1);
	return (x * SPRITE_SIZE);
}

int	get_py(int y, t_game *g)
{
	if (y < 0 || y >= g->map->rows)
		return (-1);
	return (y * SPRITE_SIZE);
}

t_animation	*new_animation(char *name, char *path, t_win win)
{
	t_list		*frames;
	t_img		*frame1;
	t_img		*frame2;
	t_img		*frame3;
	t_img		*frame4;
	t_animation	*a;

	printf("Creating new animation\n");
	frames = NULL;

	frame1 = malloc(sizeof(t_img));
	if (!frame1)
		return (NULL);
	frame2 = malloc(sizeof(t_img));
	if (!frame2)
		return (NULL);
	frame3 = malloc(sizeof(t_img));
	if (!frame3)
		return (NULL);
	frame4 = malloc(sizeof(t_img));
	if (!frame4)
		return (NULL);

	*frame1 = new_file_img(path, win);
	if (!frames)
		frames = ft_lstnew(frame1);
	else
		ft_lstadd_back(&frames, ft_lstnew(frame1));

	*frame2 = new_file_img("./assets/pac_semi_right.xpm", win);
	if (!frames)
		frames = ft_lstnew(frame2);
	else
		ft_lstadd_back(&frames, ft_lstnew(frame2));

	*frame3 = new_file_img("./assets/pac_closed.xpm", win);
	if (!frames)
		frames = ft_lstnew(frame3);
	else
		ft_lstadd_back(&frames, ft_lstnew(frame3));

	*frame4 = new_file_img("./assets/pac_semi_right.xpm", win);
	if (!frames)
		frames = ft_lstnew(frame4);
	else
		ft_lstadd_back(&frames, ft_lstnew(frame4));

	a = (t_animation *)malloc(sizeof(t_animation));
	if (!a)
		return (NULL);
	a->name = ft_strdup(name);
	a->frames = frames;
	a->delay = 8;
	a->_tmp_delay = 0;
	a->current_frame_num = 0;
	printf("Animation created\n");
	return (a);
}

t_ent	*new_ent(t_entity type, char *path, t_win win, int x, int y)
{
	t_ent	*ent;

	printf("Creating new entity\n");
	ent = (t_ent *)malloc(sizeof(t_ent));
	if (!ent)
		return (NULL);
	if (type == PLAYER)
	{
		// ent->animation[PLAYER_IDLE] = new_animation("player", path, win);
		ent->animations = ft_lstnew(new_animation("player", path, win));
		// ent->img = new_file_img(path, win);
		printf("Animation created\n");
	}
	ent->x = x * SPRITE_SIZE;
	ent->y = y * SPRITE_SIZE;
	ent->type = type;
	printf("Entity created\n");
	return (ent);
}

void	add_ent(t_entity entity, char *path, t_game *g, int x, int y)
{
	t_ent	*ent;

	ent = new_ent(entity, path, g->win, x, y);
	if (!g->ents)
		g->ents = ft_lstnew(ent);
	else
		ft_lstadd_back(&g->ents, ft_lstnew(ent));
}

void	get_assets(t_game *g)
{
	int	x;
	int	y;

	g->static_assets.wall = new_file_img(WALL_PATH, g->win);
	g->static_assets.floor = new_file_img(FLOOR_PATH, g->win);
	x = 0;
	while (x < g->map->cols)
	{
		y = 0;
		while (y < g->map->rows)
		{
			if (g->map->map[y][x] == 'P')
				add_ent(PLAYER, PLAYER_PATH, g, x, y);
			// else if (g->map->map[y][x] == 'I')
			// 	add_ent(ENEMY, ENEMY_PATH, g, x, y);
			// else if (g->map->map[y][x] == 'C')
			// 	add_ent(COLLECTIBLE, COLLECTIBLE_PATH, g, x, y);
			// else if (g->map->map[y][x] == 'E')
			// 	add_ent(EXIT_PORTAL, EXIT_PORTAL_PATH, g, x, y);
			y++;
		}
		x++;
	}
}

int	check_collision_y(t_point cp, t_point np, char c, t_game *g)
{
	int	cx;
	int	cy;

	cx = np.x + (SPRITE_SIZE / 2);
	cy = np.y + (SPRITE_SIZE / 2);
	if (np.y < cp.y)
	{
		if (g->map->map[(cy - P_PAD) / SPRITE_SIZE][cx / SPRITE_SIZE] == c)
			return (1);
	}
	else if (np.y > cp.y)
	{
		if (g->map->map[(cy + P_PAD) / SPRITE_SIZE][cx / SPRITE_SIZE] == c)
			return (1);
	}
	return (0);
}

int	check_collision_x(t_point cp, t_point np, char c, t_game *g)
{
	int	cx;
	int	cy;

	cx = np.x + (SPRITE_SIZE / 2);
	cy = np.y + (SPRITE_SIZE / 2);
	if (np.x < cp.x)
	{
		if (g->map->map[cy / SPRITE_SIZE][(cx - P_PAD) / SPRITE_SIZE] == c)
			return (1);
	}
	else if (np.x > cp.x)
	{
		if (g->map->map[cy / SPRITE_SIZE][(cx + P_PAD) / SPRITE_SIZE] == c)
			return (1);
	}
	return (0);
}

void	move_player(t_ent *ent, t_game *g, t_actions *a)
{
	t_point	curr_point;
	t_point	next_point;

	curr_point = (t_point){ent->x, ent->y};
	next_point = (t_point){ent->x, ent->y};
	if (a->up)
		next_point.y -= PLAYER_SPEED;
	if (a->down)
		next_point.y += PLAYER_SPEED;
	if (a->left)
		next_point.x -= PLAYER_SPEED;
	if (a->right)
		next_point.x += PLAYER_SPEED;
	if (next_point.x == curr_point.x && next_point.y == curr_point.y)
		return ;
	if (!check_collision_x(curr_point, next_point, '1', g))
		ent->x = next_point.x;
	if (!check_collision_y(curr_point, next_point, '1', g))
		ent->y = next_point.y;
}

void	update_player(t_actions *a, t_game *g)
{
	t_list	*ent;
	t_ent	*ent_ptr;

	ent = g->ents;
	while (ent)
	{
		ent_ptr = (t_ent *)ent->content;
		if (ent_ptr->type != PLAYER)
			ent = ent->next;
		move_player(ent_ptr, g, a);
		return ;
	}
}

void	update_animation_(t_animation *a, t_ent *ent, t_img game_img)
{
	t_img	*img;

	printf("update_animation: Updating animation\n");
	if (!a || !ent)
		return ;
	if (a->_tmp_delay++ == a->delay)
	{
		a->_tmp_delay = 0;
		a->current_frame_num++;
		a->current_frame_num %= ft_lstsize(a->frames);
	}
	printf("update_animation: Current frame: %d\n", a->current_frame_num);
	img = (t_img *)ft_lstget(a->frames, a->current_frame_num)->content;
	put_img_to_img(game_img, *img, ent->x, ent->y);
	printf("update_animation: Animation updated %s\n", a->name);
}

void	render_entities(t_game *g)
{
	t_list		*ent;
	t_ent		*ent_ptr;
	int			i;
	t_animation	*anim;

	update_player(&g->cur_actions, g);
	ent = g->ents;
	i = 0;
	while (ent != NULL)
	{
		printf("Entity %d\n", i++);
		ent_ptr = (t_ent *)ent->content;
		anim = (t_animation *)ft_lstget(ent_ptr->animations, 0)->content;
		update_animation_(anim, ent_ptr, g->game_img);
		// put_img_to_img(g->game_img, ent_ptr->img, ent_ptr->x, ent_ptr->y);
		printf("going t	next entity\n");
		ent = ent->next;
	}
	printf("Entities updated\n");
}

void	destroy_entity(void *ptr)
{
	t_ent	*ent;

	ent = (t_ent *)ptr;
	if (!ent)
		return ;
	// destroy_animation_noptr(ent->animation[PLAYER_IDLE]);
	destroy_animation(ft_lstget(ent->animations, 0));
	// destroy_image(ent->img);
}

void	destroy_assets(t_game *g)
{
	destroy_image(g->static_assets.wall);
	destroy_image(g->static_assets.floor);
	if (g->ents)
	{
		ft_lstiter(g->ents, &destroy_entity);
		ft_lstclear(&g->ents, &free);
	}
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

void	render_map(t_game *g)
{
	int	x;
	int	y;

	x = 0;
	while (x < g->map->cols)
	{
		y = 0;
		while (y < g->map->rows)
		{
			if (g->map->map[y][x] == '1')
				put_img_to_img(g->game_img, g->static_assets.wall, get_px(x, g),
					get_py(y, g));
			else
				put_img_to_img(g->game_img, g->static_assets.floor, get_px(x,
						g), get_py(y, g));
			y++;
		}
		x++;
	}
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

	game.ents = NULL;
	game.cur_actions = (t_actions){0, 0, 0, 0, 0};
	game.map = map;
	game.created_at = gettimeofday_ms();
	game.updated_at = 0;
	game.fps = 64;
	game_win = new_window(get_win_w(game), get_win_h(game), TITLE);
	ft_putstr_fd("Game initialized\n", 1);
	game.win = game_win;
	game.game_img = new_img(get_map_w(game.map), get_map_h(game.map), game_win);
	get_assets(&game);
	printf("Got assets\n");
	mlx_hook(game_win.win_ptr, KEY_PRESS, KEY_PRESS_MASK, &on_keypress, &game);
	mlx_hook(game_win.win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, &on_keyrelease,
		&game);
	mlx_hook(game_win.win_ptr, DESTROY_NOTIFY, STRUCT_NOTIFY_MASK, &on_destroy,
		&game);
	mlx_loop_hook(game_win.mlx_ptr, render_game, &game);
	mlx_loop(game_win.mlx_ptr);
}
