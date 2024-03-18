/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:09:04 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 17:41:06 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	on_destroy(t_game *game)
{
	if (!game)
		exit(EXIT_FAILURE);
	ft_printf("Total moves: %d\n\n", game->moves);
	ft_printf("Exiting game\n");
	free_map(game->map);
	destroy_assets(game);
	destroy_image(game->game_img);
	destroy_image(game->score_img);
	destroy_window(game->win);
	exit(0);
}

void	on_destroy_message(char *msg, t_game *g)
{
	ft_printf("%s\n", msg);
	on_destroy(g);
}

void	exit_error_message(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(1);
}
