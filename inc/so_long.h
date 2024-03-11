/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:14:32 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/11 18:48:28 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/libft/inc/libft.h"
# include "multiplatform.h"
# include <stdint.h>
# include <stdio.h>

# define WALL_PATH "assets/wall.xpm"
# define FLOOR_PATH "assets/black.xpm"
# define PLAYER_PATH "assets/pacman.xpm"
# define COLLECTIBLE_PATH "assets/collectible.xpm"
# define ENEMY_PATH "assets/enemy.xpm"
# define EXIT_PORTAL_PATH "assets/exit.xpm"

# define SPRITE_SIZE 32
# define P_PAD 2
# define PADDING_Y 5
# define PADDING_X 2
# define TITLE "so_long - galves-f"
# define PLAYER_SPEED 5

# define get_win_h(g) (SPRITE_SIZE * (g.map->rows + PADDING_Y))
# define get_win_w(g) (SPRITE_SIZE * (g.map->cols + PADDING_X))
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

typedef struct counts
{
	int				exit;
	int				wall;
	int				empty;
	int				player;
	int				enemies;
	int				collectibles;
}					t_counts;

typedef struct s_map
{
	char			**map;
	int				rows;
	int				cols;
	t_counts		counts;
}					t_map;

typedef struct s_static_assets
{
	t_img			wall;
	t_img			floor;
}					t_static_assets;

// ============================================================================
typedef enum e_entity
{
	PLAYER,
	ENEMY,
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
	t_img			img;
	t_animation		*animation[7];
	t_entity		type;
}					t_ent;

void				destroy_animation(void *ptr);
void   destroy_animation_noptr(t_animation anim);
// ============================================================================

typedef struct s_point {
	int x;
	int y;
} t_point;

typedef struct s_actions
{
	int				up;
	int				down;
	int				left;
	int				right;
	int				attack;
}					t_actions;

typedef struct s_game
{
	uint64_t		created_at;
	uint64_t		updated_at;
	int				fps;
	t_map			*map;
	t_win			win;
	t_img			game_img;
	t_list			*ents;
	t_actions		cur_actions;
	t_static_assets	static_assets;
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

#endif
