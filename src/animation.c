/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 22:03:09 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 15:53:14 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static void	destroy_image_helper(void *ptr)
{
	t_img	*img;

	img = (t_img *)ptr;
	if (img)
		destroy_image(*img);
}

void	destroy_animation(void *ptr)
{
	t_animation	*anim;

	anim = (t_animation *)ptr;
	if (!anim)
		return ;
	ft_lstiter(anim->frames, &destroy_image_helper);
	ft_lstclear(&anim->frames, &free);
	free(anim->name);
}

void	update_animation(t_animation *a, t_ent *ent, t_img game_img)
{
	t_img	*img;

	if (!a || !ent)
		return ;
	if (a->_tmp_delay++ == a->delay)
	{
		a->_tmp_delay = 0;
		a->current_frame_num++;
		a->current_frame_num %= ft_lstsize(a->frames);
	}
	img = (t_img *)ft_lstget(a->frames, a->current_frame_num)->content;
	put_img_to_img(game_img, *img, ent->x, ent->y);
}
