/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:51:18 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 17:54:00 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/map.h"

int	get_map_h(t_map *map)
{
	return (SPRITE_SIZE * map->rows);
}

int	get_map_w(t_map *map)
{
	return (SPRITE_SIZE * map->cols);
}

int	get_win_h(t_map *map)
{
	return (SPRITE_SIZE * (map->rows + PADDING_Y));
}

int	get_win_w(t_map *map)
{
	return (SPRITE_SIZE * (map->cols + PADDING_X));
}
