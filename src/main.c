#include "../inc/so_long.h"

int	main(int ac, char **av)
{
	t_map	*map;

	map = check_args(ac, av);
	game_init(map);
	return (0);
}
