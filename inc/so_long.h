/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:14:32 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 15:50:26 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/ft_printf/inc/ft_printf.h"
# include "../libs/libft/inc/libft.h"
# include "multiplatform.h"
# include "map.h"
# include <stdint.h>

# define WALL_PATH "assets/wall.xpm"
# define FLOOR_PATH "assets/black.xpm"
# define PLAYER_PATH "assets/pacman.xpm"
# define COLLECTIBLE_PATH "assets/collectible.xpm"
# define ENEMY_PATH "assets/enemy.xpm"
# define EXIT_PORTAL_PATH "assets/exit.xpm"

# define SPRITE_SIZE 32
# define P_PAD 10
# define PADDING_Y 5
# define PADDING_X 2
# define TITLE "so_long - galves-f"
# define PLAYER_SPEED 5
# define ENEMY_SPEED 2
# define ENEMY_DELAY_CHANGE_DIR 100

# define get_win_h(map) (SPRITE_SIZE * (map->rows + PADDING_Y))
# define get_win_w(map) (SPRITE_SIZE * (map->cols + PADDING_X))
# define get_map_h(map) (SPRITE_SIZE * map->rows)
# define get_map_w(map) (SPRITE_SIZE * map->cols)

typedef struct s_win
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				width;
	int				height;
}					t_win;

typedef struct s_img
{
	t_win			win;
	void			*img_ptr;
	char			*addr;
	int				h;
	int				w;
	int				bpp;
	int				endian;
	int				line_len;
}					t_img;

typedef struct s_static_assets
{
	t_img			wall;
	t_img			floor;
}					t_static_assets;

// ============================================================================
typedef enum e_entity
{
	ENEMY,
	PLAYER,
	COLLECTIBLE,
	EXIT_PORTAL,
	EVENT,
	OBJ,
	ANIMAL,
}					t_entity;

typedef struct s_animation
{
	t_list			*frames;
	int				width;
	int				height;
	int delay;             // How many fps it takes to change animation
	int _tmp_delay;        // Delay Iterator
	int current_frame_num; // Which frame is selected
	int				mirrored;
	long int updated_at;  // When was the last update
	long int frame_count; // The frame count
	t_entity		entity;
	char			*name;
}					t_animation;

typedef enum e_panimations
{
	PLAYER_IDLE,
	PLAYER_DEATH,
	PLAYER_WALK_LEFT,
	PLAYER_WALK_RIGHT,
	PLAYER_WALK_UP,
	PLAYER_WALK_DOWN,
	PLAYER_ATTACK,
}					t_panimations;

typedef struct s_ent
{
	int				x;
	int				y;
	int				score;
	int				health;
	t_img			img;
	t_list			*animations;
	t_entity		type;
}					t_ent;

void				destroy_animation(void *ptr);
void				destroy_animation_noptr(t_animation anim);
void				update_animation(t_animation *a, t_ent *ent,
						t_img game_img);
t_animation			*new_animation_player(char *name, char *path, t_win win);
t_animation			*new_animation_collectible(char *name, char *path,
						t_win win);
t_animation			*new_animation_exit_portal(char *name, char *path,
						t_win win);
t_animation			*new_animation_enemy(char *name, char *path, t_win win);
// ============================================================================

/* Struct to store the sprites for every digit */
typedef struct s_font
{
	t_img			zero;
	t_img			one;
	t_img			two;
	t_img			three;
	t_img			four;
	t_img			five;
	t_img			six;
	t_img			seven;
	t_img			eight;
	t_img			nine;
	t_img			black;
}					t_font;

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_actions
{
	int				up;
	int				down;
	int				left;
	int				right;
	int				attack;
}					t_actions;

typedef enum e_direction
{
	STOPED,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT,
}					t_direction;

typedef struct s_game
{
	uint64_t		created_at;
	uint64_t		updated_at;
	int				moves;
	int				fps;
	t_direction		cur_dir;
	t_map			*map;
	t_win			win;
	t_img			game_img;
	t_img			score_img;
	t_list			*ents;
	t_actions		cur_actions;
	t_static_assets	static_assets;
	t_font			score_font;
}					t_game;

int					on_destroy(t_game *game);
int					on_keypress(int keysym, t_game *g);

t_map				*check_args(int ac, char **av);
void				game_init(t_map *map);

void				free_map(t_map *map);

t_win				new_window(int w, int h, char *str);
void				destroy_window_linux(t_win w);
void				destroy_window_mac(t_win w);
t_img				new_file_img(char *path, t_win window);
t_img				new_img(int w, int h, t_win window);
unsigned int		get_pixel_img(t_img img, int x, int y);
void				put_pixel_img(t_img img, int x, int y, int color);
void				put_img_to_img(t_img dst, t_img src, int x, int y);
void				destroy_image(t_img img);

void				update_score(t_game *g);
t_font				load_score_font(t_game *g);
void				free_fonts(t_game *g);

void				destroy_entity(void *ptr);
void				render_entities(t_game *g);
void				check_entities_collision(t_ent *player, t_game *g);

void	move_enemy(t_ent *ent, t_game *g);
void	move_player(t_ent *ent, t_game *g, t_actions *a);
int	on_destroy(t_game *game);
void	on_destroy_message(char *msg, t_game *g);

void	render_map(t_game *g);
int	get_px(int x, t_game *g);
int	get_py(int x, t_game *g);

int	check_collision_y(t_point cp, t_point np, char c, t_game *g);
int	check_collision_x(t_point cp, t_point np, char c, t_game *g);
int	change_direction(t_point cp, t_point np, t_game *g);

unsigned int	rand_range(unsigned int min, unsigned int max);
uint64_t	gettimeofday_ms(void);
uint64_t	timestamp_in_ms(t_game *game);

void	update_player(t_actions *a, t_game *g);

void	get_assets(t_game *g);
void	destroy_assets(t_game *g);

void	add_ent(t_entity entity, char *path, t_game *g, int x, int y);

void	free_map(t_map *map);
t_map	*check_args(int ac, char **av);

void exit_error_message(char *msg);

#endif
