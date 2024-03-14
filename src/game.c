/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 23:48:08 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/14 10:03:06 by galves-f         ###   ########.fr       */
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

t_animation	*new_animation_player(char *name, char *path, t_win win)
{
	t_list		*frames;
	t_img		*frame1;
	t_img		*frame2;
	t_img		*frame3;
	t_img		*frame4;
	t_animation	*a;

	frames = NULL;
	(void)path;
	frame1 = malloc(sizeof(t_img));
	frame2 = malloc(sizeof(t_img));
	frame3 = malloc(sizeof(t_img));
	frame4 = malloc(sizeof(t_img));
	if (!frame1 || !frame2 || !frame3 || !frame4)
		return (NULL);
	*frame1 = new_file_img(path, win);
	frames = ft_lstnew(frame1);
	*frame2 = new_file_img("./assets/pac_semi_right.xpm", win);
	ft_lstadd_back(&frames, ft_lstnew(frame2));
	*frame3 = new_file_img("./assets/pac_closed.xpm", win);
	ft_lstadd_back(&frames, ft_lstnew(frame3));
	*frame4 = new_file_img("./assets/pac_semi_right.xpm", win);
	ft_lstadd_back(&frames, ft_lstnew(frame4));
	a = (t_animation *)malloc(sizeof(t_animation));
	if (!a)
		return (NULL);
	a->name = ft_strdup(name);
	a->frames = frames;
	a->delay = 8;
	a->_tmp_delay = 0;
	a->current_frame_num = 0;
	return (a);
}

t_animation	*new_animation_collectible(char *name, char *path, t_win win)
{
	t_list		*frames;
	t_img		*frame1;
	t_img		*frame2;
	t_animation	*a;

	frames = NULL;
	(void)path;
	frame1 = malloc(sizeof(t_img));
	if (!frame1)
		return (NULL);
	frame2 = malloc(sizeof(t_img));
	if (!frame2)
		return (NULL);
	*frame1 = new_file_img("./assets/pacdot_powerup.xpm", win);
	if (!frames)
		frames = ft_lstnew(frame1);
	else
		ft_lstadd_back(&frames, ft_lstnew(frame1));
	*frame2 = new_file_img("./assets/pacdot_food.xpm", win);
	if (!frames)
		frames = ft_lstnew(frame2);
	else
		ft_lstadd_back(&frames, ft_lstnew(frame2));
	a = (t_animation *)malloc(sizeof(t_animation));
	if (!a)
		return (NULL);
	a->name = ft_strdup(name);
	a->frames = frames;
	a->delay = 64;
	a->_tmp_delay = 0;
	a->current_frame_num = 0;
	return (a);
}

t_animation	*new_animation_enemy(char *name, char *path, t_win win)
{
	t_list		*frames;
	t_img		*frame1;
	t_img		*frame2;
	t_animation	*a;

	frames = NULL;
	(void)path;
	frame1 = malloc(sizeof(t_img));
	if (!frame1)
		return (NULL);
	frame2 = malloc(sizeof(t_img));
	if (!frame2)
		return (NULL);
	(void)path;
	*frame1 = new_file_img("./assets/ghost_left1.xpm", win);
	if (!frames)
		frames = ft_lstnew(frame1);
	else
		ft_lstadd_back(&frames, ft_lstnew(frame1));
	*frame2 = new_file_img("./assets/ghost_left2.xpm", win);
	if (!frames)
		frames = ft_lstnew(frame2);
	else
		ft_lstadd_back(&frames, ft_lstnew(frame2));
	a = (t_animation *)malloc(sizeof(t_animation));
	if (!a)
		return (NULL);
	a->name = ft_strdup(name);
	a->frames = frames;
	a->delay = 8;
	a->_tmp_delay = 0;
	a->current_frame_num = 0;
	return (a);
}

t_animation	*new_animation_exit_portal(char *name, char *path, t_win win)
{
	t_list		*frames;
	t_img		*frame1;
	t_animation	*a;

	frames = NULL;
	(void)path;
	frame1 = malloc(sizeof(t_img));
	if (!frame1)
		return (NULL);
	*frame1 = new_file_img("./assets/portal.xpm", win);
	if (!frames)
		frames = ft_lstnew(frame1);
	else
		ft_lstadd_back(&frames, ft_lstnew(frame1));
	a = (t_animation *)malloc(sizeof(t_animation));
	if (!a)
		return (NULL);
	a->name = ft_strdup(name);
	a->frames = frames;
	a->delay = 100;
	a->_tmp_delay = 0;
	a->current_frame_num = 0;
	return (a);
}

t_ent	*new_ent(t_entity type, char *path, t_win win, int x, int y)
{
	t_ent	*ent;

	ent = (t_ent *)malloc(sizeof(t_ent));
	if (!ent)
		return (NULL);
	if (type == PLAYER)
	{
		ent->animations = ft_lstnew(new_animation_player("player", path, win));
		ent->score = 0;
		ent->health = 100;
	}
	else if (type == ENEMY)
	{
		ent->animations = ft_lstnew(new_animation_enemy("enemy", path, win));
		ent->score = 0;
		ent->health = 100;
	}
	else if (type == COLLECTIBLE)
	{
		ent->animations = ft_lstnew(new_animation_collectible("collectible",
					path, win));
		ent->score = 1;
		ent->health = 0;
	}
	else if (type == EXIT_PORTAL)
		ent->animations = ft_lstnew(new_animation_exit_portal("exit_portal",
					path, win));
	else
	{
		free(ent);
		return (NULL);
	}
	ent->x = x * SPRITE_SIZE;
	ent->y = y * SPRITE_SIZE;
	ent->type = type;
	return (ent);
}

void	add_ent(t_entity entity, char *path, t_game *g, int x, int y)
{
	t_ent	*ent;

	ent = new_ent(entity, path, g->win, x, y);
	if (!ent)
		return ;
	if (!g->ents)
		g->ents = ft_lstnew(ent);
	else if (entity == EXIT_PORTAL)
		ft_lstadd_front(&g->ents, ft_lstnew(ent));
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
			else if (g->map->map[y][x] == 'X')
				add_ent(ENEMY, ENEMY_PATH, g, x, y);
			else if (g->map->map[y][x] == 'C')
				add_ent(COLLECTIBLE, COLLECTIBLE_PATH, g, x, y);
			else if (g->map->map[y][x] == 'E')
				add_ent(EXIT_PORTAL, EXIT_PORTAL_PATH, g, x, y);
			y++;
		}
		x++;
	}
}

void	destroy_entity(void *ptr)
{
	t_ent	*ent;

	ent = (t_ent *)ptr;
	if (!ent)
		return ;
	ft_lstiter(ent->animations, &destroy_animation);
	ft_lstclear(&ent->animations, &free);
}

void	on_destroy_message(char *msg, t_game *g)
{
	ft_printf("%s\n", msg);
	on_destroy(g);
}

void	check_entities_collision(t_ent *player, t_game *g)
{
	t_list	*ents;
	t_ent	*entity;
	t_list	*tmp;

	ents = g->ents;
	int i = 0;
	while (ents)
	{
		entity = (t_ent *)ents->content;
		if ((player->x + P_PAD < entity->x || player->x - P_PAD > entity->x)
			|| (player->y + P_PAD < entity->y || player->y - P_PAD > entity->y))
		{
			ents = ents->next;
			continue ;
		}
		tmp = ents;
		ents = ents->next;
		if (entity->type == COLLECTIBLE)
		{
			ft_printf("Collectible %d\n", i);
			player->score += entity->score;
			ft_lstremove_del(&g->ents, tmp, &destroy_entity);
			free(entity);
		}
		else if (entity->type == EXIT_PORTAL)
		{
			if (player->score == g->map->counts.collectibles)
				on_destroy_message("You won, congratsss\n", g);
		}
		else if (entity->type == ENEMY)
		{
			player->health -= entity->health;
			if (player->health <= 0)
				on_destroy_message("Game over\n", g);
		}
		i++;
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
	t_point		curr_point;
	t_point		next_point;
	static int	movements = 0;

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
	ft_printf("Movements: %d\n", movements++);
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
		{
			ent = ent->next;
			continue ;
		}
		move_player(ent_ptr, g, a);
		check_entities_collision(ent_ptr, g);
		return ;
	}
}

void	update_animation_(t_animation *a, t_ent *ent, t_img game_img)
{
	t_img	*img;

	if (!a || !ent)
		return ;
	if (a->_tmp_delay++ == a->delay)
	{
		a->_tmp_delay = 0;
		a->current_frame_num++;
		a->current_frame_num %= ft_lstsize(a->frames);
	}
	img = (t_img *)ft_lstget(a->frames, a->current_frame_num)->content;
	put_img_to_img(game_img, *img, ent->x, ent->y);
}

void	render_entities(t_game *g)
{
	t_list		*ent;
	t_ent		*ent_ptr;
	t_animation	*anim;

	update_player(&g->cur_actions, g);
	if (!g)
	{
		ft_printf("No game to render\n");
		return ;
	}
	if (!g->ents)
	{
		ft_printf("No entities to render\n");
		return ;
	}
	ent = g->ents;
	while (ent != NULL)
	{
		ent_ptr = (t_ent *)ent->content;
		anim = (t_animation *)ft_lstget(ent_ptr->animations, 0)->content;
		update_animation_(anim, ent_ptr, g->game_img);
		ent = ent->next;
	}
}

void	destroy_assets(t_game *g)
{
	destroy_image(g->static_assets.wall);
	destroy_image(g->static_assets.floor);
	if (!g->ents)
		return ;
	ft_lstiter(g->ents, &destroy_entity);
	ft_lstclear(&g->ents, &free);
}

int	on_destroy(t_game *game)
{
	if (!game)
		exit(EXIT_FAILURE);
	ft_printf("Exiting game\n");
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
	ft_printf("Game initialized\n");
	game.win = game_win;
	game.game_img = new_img(get_map_w(game.map), get_map_h(game.map), game_win);
	get_assets(&game);
	mlx_hook(game_win.win_ptr, KEY_PRESS, KEY_PRESS_MASK, &on_keypress, &game);
	mlx_hook(game_win.win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, &on_keyrelease,
		&game);
	mlx_hook(game_win.win_ptr, DESTROY_NOTIFY, STRUCT_NOTIFY_MASK, &on_destroy,
		&game);
	mlx_loop_hook(game_win.mlx_ptr, render_game, &game);
	mlx_loop(game_win.mlx_ptr);
}
