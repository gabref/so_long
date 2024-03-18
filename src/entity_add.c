/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:06:45 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 17:31:14 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	new_ent_utils(t_entity type, t_ent *ent, t_win win)
{
	if (type == PLAYER)
	{
		ent->animations = ft_lstnew(new_animation_player("player", win));
		ent->score = 0;
		ent->health = 100;
	}
	else if (type == ENEMY)
	{
		ent->animations = ft_lstnew(new_animation_enemy("enemy", win));
		ent->score = 0;
		ent->health = 100;
	}
	else if (type == COLLECTIBLE)
	{
		ent->animations = ft_lstnew(new_animation_collectible("collectible",
					win));
		ent->score = 1;
		ent->health = 0;
	}
	else if (type == EXIT_PORTAL)
		ent->animations = ft_lstnew(new_animation_exit_portal("exit_portal",
					win));
}

t_ent	*new_ent(t_entity type, t_win win, int x, int y)
{
	t_ent	*ent;

	ent = (t_ent *)malloc(sizeof(t_ent));
	if (!ent)
		return (NULL);
	ent->animations = NULL;
	new_ent_utils(type, ent, win);
	if (!ent->animations)
	{
		free(ent);
		return (NULL);
	}
	ent->x = x * SPRITE_SIZE;
	ent->y = y * SPRITE_SIZE;
	ent->type = type;
	return (ent);
}

void	add_ent(t_entity entity, t_game *g, int x, int y)
{
	t_ent	*ent;

	ent = new_ent(entity, g->win, x, y);
	if (!ent)
		return ;
	if (!g->ents)
		g->ents = ft_lstnew(ent);
	else if (entity == EXIT_PORTAL)
		ft_lstadd_front(&g->ents, ft_lstnew(ent));
	else
		ft_lstadd_back(&g->ents, ft_lstnew(ent));
}
