#include "../inc/so_long.h"

int	main(int ac, char **av)
{
	t_map *map = check_args(ac, av);
	t_game *game = game_init(map);
	(void)game;
	// game_loop(&game);
	// game_exit(&game);
	return (0);
}
