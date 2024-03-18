/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:06:58 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 17:56:20 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	move_player(t_ent *ent, t_game *g, t_actions *a)
{
	t_point	curr_point;
	t_point	next_point;

	curr_point = (t_point){ent->x, ent->y};
	next_point = (t_point){ent->x, ent->y};
	if (a->up)
		next_point.y -= PLAYER_SPEED;
	if (a->down)
		next_point.y += PLAYER_SPEED;
	if (a->left)
		next_point.x -= PLAYER_SPEED;
	if (a->right)
		next_point.x += PLAYER_SPEED;
	if (!check_collision_x(curr_point, next_point, '1', g))
		ent->x = next_point.x;
	if (!check_collision_y(curr_point, next_point, '1', g))
		ent->y = next_point.y;
	if (change_direction(curr_point, next_point, g))
		g->moves++;
}

void	update_next_point(t_actions *a, t_point *next_point)
{
	if (a->up)
		next_point->y -= ENEMY_SPEED;
	if (a->down)
		next_point->y += ENEMY_SPEED;
	if (a->left)
		next_point->x -= ENEMY_SPEED;
	if (a->right)
		next_point->x += ENEMY_SPEED;
}

void	move_enemy(t_ent *ent, t_game *g)
{
	t_point				curr_point;
	t_point				next_point;
	static int			cur_change_move = 0;
	static t_actions	a = (t_actions){0, 0, 0, 0, 0};

	curr_point = (t_point){ent->x, ent->y};
	next_point = (t_point){ent->x, ent->y};
	if (cur_change_move > ENEMY_DELAY_CHANGE_DIR)
	{
		cur_change_move = 0;
		a = (t_actions){rand_range(0, 1), rand_range(0, 1), rand_range(0, 1),
			rand_range(0, 1), 0};
	}
	cur_change_move++;
	update_next_point(&a, &next_point);
	if (!check_collision_x(curr_point, next_point, '1', g))
		ent->x = next_point.x;
	if (!check_collision_y(curr_point, next_point, '1', g))
		ent->y = next_point.y;
}

void	update_player(t_actions *a, t_game *g)
{
	t_list	*ent;
	t_ent	*ent_ptr;

	ent = g->ents;
	while (ent)
	{
		ent_ptr = (t_ent *)ent->content;
		if (ent_ptr->type != PLAYER)
		{
			if (ent_ptr->type == ENEMY)
				move_enemy(ent_ptr, g);
			ent = ent->next;
			continue ;
		}
		move_player(ent_ptr, g, a);
		check_entities_collision(ent_ptr, g);
		return ;
	}
}
