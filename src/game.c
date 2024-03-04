/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 23:48:08 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/04 01:20:50 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

t_game	*game_init(t_map *map)
{
	t_game	*game;

	ft_putstr_fd("Game initialized\n", 1);
	game = (t_game *)malloc(sizeof(t_game));
	game->map = map;
	return (game);
}
