/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:14:32 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/03 23:54:57 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/libft/inc/libft.h"
# include "multiplatform.h"
# include <stdio.h>

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct counts
{
	int			exit;
	int			wall;
	int			empty;
	int			player;
	int			enemies;
	int			collectibles;
}				t_counts;

typedef struct s_map
{
	char		**map;
	int			rows;
	int			cols;
	t_counts	counts;
}				t_map;

typedef struct s_game
{
	t_map		*map;
	t_data		*data;
}				t_game;

void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				on_destroy(t_data *t);
int				on_keypress(int keysym, t_data *t);

t_map			*check_args(int ac, char **av);
t_game 			*game_init(t_map *map);

#endif
