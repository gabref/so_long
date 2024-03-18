/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:59:48 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 17:18:59 by galves-f         ###   ########.fr       */
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

void	collision_action(t_ent *ent_cont, t_list *t, t_ent *player, t_game *g)
{
	if (ent_cont->type == COLLECTIBLE)
	{
		player->score += ent_cont->score;
		ft_lstremove_del(&g->ents, t, &destroy_entity);
		free(ent_cont);
	}
	else if (ent_cont->type == EXIT_PORTAL)
	{
		if (player->score == g->map->counts.collectibles)
			on_destroy_message("You won, congratsss\n", g);
	}
	else if (ent_cont->type == ENEMY)
	{
		player->health -= ent_cont->health;
		if (player->health <= 0)
			on_destroy_message("Game over\n", g);
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
		collision_action(entity, tmp, player, g);
	}
}
