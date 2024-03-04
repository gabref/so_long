/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */ /*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:19:21 by galves-f          #+#    #+#             */
/*   Updated: 2024/02/19 19:40:34 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/so_long.h"

static char	*read_map(char *file)
{
	int		fd;
	char	*map;
	char	*line;
	char	*tmp;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nInvalid file\n", 2);
		exit(1);
	}
	map = ft_strdup("");
	line = get_next_line(fd);
	while (line != NULL)
	{
		tmp = map;
		map = ft_strjoin(tmp, line);
		free(line);
		free(tmp);
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}

void print_map(t_map *map)
{
	int i = 0;
	while (map->map[i])
	{
		printf("%s\n", map->map[i]);
		i++;
	}
}

t_map *check_args(int ac, char **av)
{
	t_map	*map;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		exit(1);
	}
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".ber", 4))
	{
		ft_putstr_fd("Error\nInvalid file extension\n", 2);
		exit(1);
	}
	// read the map file
	// check if the file exists
	char *map_inline = read_map(av[1]);
	printf("%s", map_inline);
	map = malloc(sizeof(t_map));
	if (!map)
	{
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		free(map_inline);
		exit(1);
	}
	map->map = ft_split_word(map_inline, "\n");
	printf("split\n");
	free(map_inline);
	if (!map->map)
	{
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		free(map);
		exit(1);
	}
	// check if the map is valid
	// check if the map is not empty
	printf("check map emtpy\n");
	if (map->map[0] == NULL)
	{
		ft_putstr_fd("Error\nEmpty map\n", 2);
		free(map->map);
		free(map);
		exit(1);
	}
	printf("check map not rectangular\n");
	if (map->map[1] == NULL)
	{
		ft_putstr_fd("Error\nMap is not rectangular\n", 2);
		free(map->map[0]);
		free(map->map);
		free(map);
		exit(1);
	}
	// check if the map is rectangular
	int i = 0;
	map->cols = ft_strlen(map->map[0]);
	while (map->map[i])
	{
		if ((int)ft_strlen(map->map[i]) != map->cols)
		{
			ft_putstr_fd("Error\nMap is not rectangular\n", 2);
			// free entire map
			free(map->map[i]);
			free(map->map);
			free(map);
			exit(1);
		}
		i++;
	}
	map->rows = i;

	// check if the map is surrounded by walls
	int j;
	i = 0;
	while (map->map[i])
	{
		if (i == 0 || i == map->rows - 1)
		{
			j = 0;
			while (map->map[i][j])
			{
				if (map->map[i][j] != '1')
				{
					ft_putstr_fd("Error\nMap is not surrounded by walls\n", 2);
					// free entire map
					free(map->map[i]);
					free(map->map);
					free(map);
					exit(1);
				}
				j++;
			}
		}
		if (map->map[i][0] != '1' || map->map[i][map->cols - 1] != '1')
		{
			ft_putstr_fd("Error\nMap is not surrounded by walls\n", 2);
			// free entire map
			free(map->map[i]);
			free(map->map);
			free(map);
			exit(1);
		}
		i++;
	}

	// check if the map has only valid characters
	map->counts = (t_counts){0, 0, 0, 0, 0, 0};
	i = 0;
	j = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'P')
				map->counts.player++;
			else if (map->map[i][j] == 'E')
				map->counts.exit++;
			else if (map->map[i][j] == 'C')
				map->counts.collectibles++;
			else if (map->map[i][j] == '1')
				map->counts.wall++;
			else if (map->map[i][j] == '0')
				map->counts.empty++;
			else if (map->map[i][j] == 'X')
				map->counts.enemies++;
			else
			{
				ft_putstr_fd("Error\nInvalid character in map\n", 2);
				// free entire map
				free(map->map[i]);
				free(map->map);
				free(map);
				exit(1);
			}
			j++;
		}
		i++;
	}

	// check if there is only one exit
	if (map->counts.exit != 1)
	{
		ft_putstr_fd("Error\nInvalid number of exits\n", 2);
		// free entire map
		free(map->map[i]);
		free(map->map);
		free(map);
		exit(1);
	}
	// check if there is only one player
	if (map->counts.player != 1)
	{
		ft_putstr_fd("Error\nInvalid number of players\n", 2);
		// free entire map
		free(map->map[i]);
		free(map->map);
		free(map);
		exit(1);
	}
	// check if there is at least one collectible
	if (map->counts.collectibles < 1)
	{
		ft_putstr_fd("Error\nInvalid number of collectibles\n", 2);
		// free entire map
		free(map->map[i]);
		free(map->map);
		free(map);
		exit(1);
	}
	// check if there is at least one floor
	if (map->counts.empty < 1)
	{
		ft_putstr_fd("Error\nInvalid number of floors\n", 2);
		// free entire map
		free(map->map[i]);
		free(map->map);
		free(map);
		exit(1);
	}
	// check if there is at least one wall
	if (map->counts.wall < 1)
	{
		ft_putstr_fd("Error\nInvalid number of walls\n", 2);
		// free entire map
		free(map->map[i]);
		free(map->map);
		free(map);
		exit(1);
	}
	return (map);
}
