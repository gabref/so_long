/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:15:08 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/03 23:48:01 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	on_destroy(t_data *t)
{
	mlx_destroy_window(t->mlx, t->mlx_win);
	mlx_destroy_display(t->mlx);
	free(t->mlx);
	exit(0);
	return (0);
}

int	on_keypress(int keysym, t_data *t)
{
	(void)t;
	if (keysym == KEY_ESCAPE)
	{
		printf("The %d key (ESC) has been pressed\n\n", keysym);
		on_destroy(t);
	}
	printf("Pressed key: %d\n", keysym);
	return (0);
}

int	run_game(void)
{
	t_data	t;
	int		size;
	int		size2;
	void	*img;
	void	*wall;

	t.mlx = mlx_init();
	if (!t.mlx)
		return (1);
	t.mlx_win = mlx_new_window(t.mlx, 600, 400, "Hello world!");
	if (!t.mlx_win)
		return (1);
	mlx_hook(t.mlx_win, KEY_RELEASE, KEY_RELEASE_MASK, &on_keypress, &t);
	mlx_hook(t.mlx_win, DESTROY_NOTIFY, STRUCT_NOTIFY_MASK, &on_destroy, &t);
	size = 32;
	size2 = 32;
	img = mlx_xpm_file_to_image(t.mlx, "./test_player.xpm", &size, &size);
	wall = mlx_xpm_file_to_image(t.mlx, "./other_0.xpm", &size2, &size2);
	if (!wall)
		return (1);
	printf("sizes: %d, %d\n", size, size2);
	mlx_put_image_to_window(t.mlx, t.mlx_win, wall, 100, 100);
	mlx_put_image_to_window(t.mlx, t.mlx_win, img, 100, 100);
	mlx_put_image_to_window(t.mlx, t.mlx_win, img, 130, 100);
	mlx_put_image_to_window(t.mlx, t.mlx_win, img, 160, 100);
	mlx_loop(t.mlx);
	return (0);
}
