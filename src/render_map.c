/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:11:31 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 17:21:43 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

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
