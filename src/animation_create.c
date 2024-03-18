/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:03:38 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 17:02:16 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

t_list	*get_frames(char **paths, int path_size, t_win win)
{
	t_list	*frames;
	t_img	*frame;
	int		i;

	i = 0;
	frames = NULL;
	while (i < path_size)
	{
		frame = malloc(sizeof(t_img));
		if (!frame)
			return (NULL);
		*frame = new_file_img(paths[i], win);
		if (!frames)
			frames = ft_lstnew(frame);
		else
			ft_lstadd_back(&frames, ft_lstnew(frame));
		i++;
	}
	return (frames);
}

t_animation	*new_animation_player(char *name, t_win win)
{
	t_list		*frames;
	t_animation	*a;
	char		**paths;

	paths = ft_calloc(5, sizeof(char *));
	paths[0] = ft_strdup("assets/pacman.xpm");
	paths[1] = ft_strdup("assets/pac_semi_right.xpm");
	paths[2] = ft_strdup("assets/pac_closed.xpm");
	paths[3] = ft_strdup("assets/pac_semi_right.xpm");
	paths[4] = NULL;
	frames = get_frames(paths, 4, win);
	ft_free_2d_array((void **)paths);
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

t_animation	*new_animation_collectible(char *name, t_win win)
{
	t_list		*frames;
	t_animation	*a;
	char		**paths;

	paths = ft_calloc(3, sizeof(char *));
	paths[0] = ft_strdup("assets/pacdot_powerup.xpm");
	paths[1] = ft_strdup("assets/pacdot_food.xpm");
	paths[2] = NULL;
	frames = get_frames(paths, 2, win);
	ft_free_2d_array((void **)paths);
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

t_animation	*new_animation_enemy(char *name, t_win win)
{
	t_list		*frames;
	t_animation	*a;
	char		**paths;

	paths = ft_calloc(3, sizeof(char *));
	paths[0] = ft_strdup("assets/ghost_left1.xpm");
	paths[1] = ft_strdup("assets/ghost_left2.xpm");
	paths[2] = NULL;
	frames = get_frames(paths, 2, win);
	ft_free_2d_array((void **)paths);
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

t_animation	*new_animation_exit_portal(char *name, t_win win)
{
	t_list		*frames;
	t_img		*frame;
	t_animation	*a;

	frames = NULL;
	frame = malloc(sizeof(t_img));
	if (!frame)
		return (NULL);
	*frame = new_file_img("./assets/portal.xpm", win);
	frames = ft_lstnew(frame);
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
