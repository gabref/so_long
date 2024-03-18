/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:03:38 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 15:56:09 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/so_long.h"

t_animation	*new_animation_player(char *name, char *path, t_win win)
{
	t_list		*frames;
	t_img		*frame1;
	t_img		*frame2;
	t_img		*frame3;
	t_img		*frame4;
	t_animation	*a;

	frames = NULL;
	(void)path;
	frame1 = malloc(sizeof(t_img));
	frame2 = malloc(sizeof(t_img));
	frame3 = malloc(sizeof(t_img));
	frame4 = malloc(sizeof(t_img));
	if (!frame1 || !frame2 || !frame3 || !frame4)
		return (NULL);
	*frame1 = new_file_img(path, win);
	frames = ft_lstnew(frame1);
	*frame2 = new_file_img("./assets/pac_semi_right.xpm", win);
	ft_lstadd_back(&frames, ft_lstnew(frame2));
	*frame3 = new_file_img("./assets/pac_closed.xpm", win);
	ft_lstadd_back(&frames, ft_lstnew(frame3));
	*frame4 = new_file_img("./assets/pac_semi_right.xpm", win);
	ft_lstadd_back(&frames, ft_lstnew(frame4));
	a = (t_animation *)malloc(sizeof(t_animation));
	if (!a)
		return (NULL);
	a->name = ft_strdup(name);
	a->frames = frames;
	a->delay = 8;
	a->_tmp_delay = 0;
	a->current_frame_num = 0;
	return (a);
}

t_animation	*new_animation_collectible(char *name, char *path, t_win win)
{
	t_list		*frames;
	t_img		*frame1;
	t_img		*frame2;
	t_animation	*a;

	frames = NULL;
	(void)path;
	frame1 = malloc(sizeof(t_img));
	if (!frame1)
		return (NULL);
	frame2 = malloc(sizeof(t_img));
	if (!frame2)
		return (NULL);
	*frame1 = new_file_img("./assets/pacdot_powerup.xpm", win);
	if (!frames)
		frames = ft_lstnew(frame1);
	else
		ft_lstadd_back(&frames, ft_lstnew(frame1));
	*frame2 = new_file_img("./assets/pacdot_food.xpm", win);
	if (!frames)
		frames = ft_lstnew(frame2);
	else
		ft_lstadd_back(&frames, ft_lstnew(frame2));
	a = (t_animation *)malloc(sizeof(t_animation));
	if (!a)
		return (NULL);
	a->name = ft_strdup(name);
	a->frames = frames;
	a->delay = 64;
	a->_tmp_delay = 0;
	a->current_frame_num = 0;
	return (a);
}

t_animation	*new_animation_enemy(char *name, char *path, t_win win)
{
	t_list		*frames;
	t_img		*frame1;
	t_img		*frame2;
	t_animation	*a;

	frames = NULL;
	(void)path;
	frame1 = malloc(sizeof(t_img));
	if (!frame1)
		return (NULL);
	frame2 = malloc(sizeof(t_img));
	if (!frame2)
		return (NULL);
	(void)path;
	*frame1 = new_file_img("./assets/ghost_left1.xpm", win);
	if (!frames)
		frames = ft_lstnew(frame1);
	else
		ft_lstadd_back(&frames, ft_lstnew(frame1));
	*frame2 = new_file_img("./assets/ghost_left2.xpm", win);
	if (!frames)
		frames = ft_lstnew(frame2);
	else
		ft_lstadd_back(&frames, ft_lstnew(frame2));
	a = (t_animation *)malloc(sizeof(t_animation));
	if (!a)
		return (NULL);
	a->name = ft_strdup(name);
	a->frames = frames;
	a->delay = 8;
	a->_tmp_delay = 0;
	a->current_frame_num = 0;
	return (a);
}

t_animation	*new_animation_exit_portal(char *name, char *path, t_win win)
{
	t_list		*frames;
	t_img		*frame1;
	t_animation	*a;

	frames = NULL;
	(void)path;
	frame1 = malloc(sizeof(t_img));
	if (!frame1)
		return (NULL);
	*frame1 = new_file_img("./assets/portal.xpm", win);
	if (!frames)
		frames = ft_lstnew(frame1);
	else
		ft_lstadd_back(&frames, ft_lstnew(frame1));
	a = (t_animation *)malloc(sizeof(t_animation));
	if (!a)
		return (NULL);
	a->name = ft_strdup(name);
	a->frames = frames;
	a->delay = 100;
	a->_tmp_delay = 0;
	a->current_frame_num = 0;
	return (a);
}

