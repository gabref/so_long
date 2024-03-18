/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:12:52 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 15:13:39 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/so_long.h"

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

int	change_direction(t_point cp, t_point np, t_game *g)
{
	t_direction	dir;

	dir = STOPED;
	if (np.x == cp.x && np.y == cp.y)
		dir = STOPED;
	else if (np.x == cp.x && np.y < cp.y)
		dir = DOWN;
	else if (np.x == cp.x && np.y > cp.y)
		dir = UP;
	else if (np.x < cp.x && np.y == cp.y)
		dir = LEFT;
	else if (np.x > cp.x && np.y == cp.y)
		dir = RIGHT;
	else if (np.x < cp.x && np.y < cp.y)
		dir = DOWN_LEFT;
	else if (np.x > cp.x && np.y < cp.y)
		dir = DOWN_RIGHT;
	else if (np.x < cp.x && np.y > cp.y)
		dir = UP_LEFT;
	else if (np.x > cp.x && np.y > cp.y)
		dir = UP_RIGHT;
	if (dir != g->cur_dir && (dir != STOPED || g->cur_dir == STOPED))
	{
		g->cur_dir = dir;
		return (1);
	}
	g->cur_dir = dir;
	return (0);
}
