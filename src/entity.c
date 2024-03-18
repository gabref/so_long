/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:59:48 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 15:06:26 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	destroy_entity(void *ptr)
{
	t_ent	*ent;

	ent = (t_ent *)ptr;
	if (!ent)
		return ;
	ft_lstiter(ent->animations, &destroy_animation);
	ft_lstclear(&ent->animations, &free);
}

void	render_entities(t_game *g)
{
	t_list		*ent;
	t_ent		*ent_ptr;
	t_animation	*anim;

	if (!g)
	{
		ft_printf("No game to render\n");
		return ;
	}
	if (!g->ents)
	{
		ft_printf("No entities to render\n");
		return ;
	}
	update_player(&g->cur_actions, g);
	ent = g->ents;
	while (ent != NULL)
	{
		ent_ptr = (t_ent *)ent->content;
		anim = (t_animation *)ft_lstget(ent_ptr->animations, 0)->content;
		update_animation(anim, ent_ptr, g->game_img);
		ent = ent->next;
	}
}

void	check_entities_collision(t_ent *player, t_game *g)
{
	t_list	*ents;
	t_ent	*entity;
	t_list	*tmp;

	ents = g->ents;
	while (ents)
	{
		entity = (t_ent *)ents->content;
		if ((player->x + P_PAD < entity->x || player->x - P_PAD > entity->x)
			|| (player->y + P_PAD < entity->y || player->y - P_PAD > entity->y))
		{
			ents = ents->next;
			continue ;
		}
		tmp = ents;
		ents = ents->next;
		if (entity->type == COLLECTIBLE)
		{
			player->score += entity->score;
			ft_lstremove_del(&g->ents, tmp, &destroy_entity);
			free(entity);
		}
		else if (entity->type == EXIT_PORTAL)
		{
			if (player->score == g->map->counts.collectibles)
				on_destroy_message("You won, congratsss\n", g);
		}
		else if (entity->type == ENEMY)
		{
			player->health -= entity->health;
			if (player->health <= 0)
				on_destroy_message("Game over\n", g);
		}
	}
}

t_ent	*new_ent(t_entity type, char *path, t_win win, int x, int y)
{
	t_ent	*ent;

	ent = (t_ent *)malloc(sizeof(t_ent));
	if (!ent)
		return (NULL);
	if (type == PLAYER)
	{
		ent->animations = ft_lstnew(new_animation_player("player", path, win));
		ent->score = 0;
		ent->health = 100;
	}
	else if (type == ENEMY)
	{
		ent->animations = ft_lstnew(new_animation_enemy("enemy", path, win));
		ent->score = 0;
		ent->health = 100;
	}
	else if (type == COLLECTIBLE)
	{
		ent->animations = ft_lstnew(new_animation_collectible("collectible",
					path, win));
		ent->score = 1;
		ent->health = 0;
	}
	else if (type == EXIT_PORTAL)
		ent->animations = ft_lstnew(new_animation_exit_portal("exit_portal",
					path, win));
	else
	{
		free(ent);
		return (NULL);
	}
	ent->x = x * SPRITE_SIZE;
	ent->y = y * SPRITE_SIZE;
	ent->type = type;
	return (ent);
}

void	add_ent(t_entity entity, char *path, t_game *g, int x, int y)
{
	t_ent	*ent;

	ent = new_ent(entity, path, g->win, x, y);
	if (!ent)
		return ;
	if (!g->ents)
		g->ents = ft_lstnew(ent);
	else if (entity == EXIT_PORTAL)
		ft_lstadd_front(&g->ents, ft_lstnew(ent));
	else
		ft_lstadd_back(&g->ents, ft_lstnew(ent));
}
