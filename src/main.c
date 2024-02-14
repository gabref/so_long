#include "../inc/so_long.h"
#include <X11/X.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int on_destroy(t_data *t)
{
	mlx_destroy_window(t->mlx, t->mlx_win);
	mlx_destroy_display(t->mlx);
	free(t->mlx);
	exit(0);
	return (0);
}

int on_keypress(int keysym, t_data *t)
{
	(void)t;
	if (keysym == XK_Escape)
	{
		printf("The %d key (ESC) has been pressed\n\n", keysym);
		on_destroy(t);
	}
	printf("Pressed key: %d\n", keysym);
	return (0);
}

int	main(void)
{
	t_data	t;

	t.mlx = mlx_init();
	if (!t.mlx)
		return (1);
	t.mlx_win = mlx_new_window(t.mlx, 600, 400, "Hello world!");
	if (!t.mlx_win)
		return (1);

	mlx_hook(t.mlx_win, KeyRelease, KeyReleaseMask, &on_keypress, &t);
	mlx_hook(t.mlx_win, DestroyNotify, StructureNotifyMask, &on_destroy, &t);

	t.img = mlx_new_image(t.mlx, 600, 400);
	t.addr = mlx_get_data_addr(t.img, &t.bits_per_pixel, &t.line_length,
			&t.endian);
	mlx_put_image_to_window(t.mlx, t.mlx_win, t.img, 0, 0);
	mlx_loop(t.mlx);
	return (0);
}
