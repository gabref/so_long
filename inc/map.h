/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:48:59 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 16:05:06 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "../libs/ft_printf/inc/ft_printf.h"
# include "../libs/libft/inc/libft.h"

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

void			check_map_walls(t_map *map);
void			util_valid_chars(int i, int j, t_map *map);
void			check_map_valid_chars(t_map *map);
void			basic_map_checks(t_map *map);
void			check_map_counts(t_map *map);
void			free_map_and_exit(t_map *map, char *message);

#endif
