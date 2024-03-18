/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:18:40 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 15:53:02 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/so_long.h"

void	get_assets(t_game *g)
{
	int	x;
	int	y;

	g->static_assets.wall = new_file_img(WALL_PATH, g->win);
	g->static_assets.floor = new_file_img(FLOOR_PATH, g->win);
	load_score_font(g);
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

void	destroy_assets(t_game *g)
{
	destroy_image(g->static_assets.wall);
	destroy_image(g->static_assets.floor);
	free_fonts(g);
	if (!g->ents)
		return ;
	ft_lstiter(g->ents, &destroy_entity);
	ft_lstclear(&g->ents, &free);
}
