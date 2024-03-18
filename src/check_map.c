/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:45:53 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 17:30:33 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/map.h"

void	check_map_walls(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		if (i == 0 || i == map->rows - 1)
		{
			j = 0;
			while (map->map[i][j])
				if (map->map[i][j++] != '1')
					free_map_and_exit(map,
						"Error\nMap is not surrounded by walls\n");
		}
		if (map->map[i][0] != '1' || map->map[i][map->cols - 1] != '1')
			free_map_and_exit(map, "Error\nMap is not surrounded by walls\n");
		i++;
	}
}

void	util_valid_chars(int i, int j, t_map *map)
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
		free_map_and_exit(map, "Error\nInvalid character in map\n");
}

void	check_map_valid_chars(t_map *map)
{
	int	i;
	int	j;

	map->counts = (t_counts){0, 0, 0, 0, 0, 0};
	i = 0;
	j = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			util_valid_chars(i, j, map);
			j++;
		}
		i++;
	}
}

void	check_map_counts(t_map *map)
{
	if (map->counts.exit != 1)
		free_map_and_exit(map, "Error\nInvalid number of exits\n");
	if (map->counts.player != 1)
		free_map_and_exit(map, "Error\nInvalid number of players\n");
	if (map->counts.collectibles < 1)
		free_map_and_exit(map, "Error\nInvalid number of collectibles\n");
	if (map->counts.empty < 1)
		free_map_and_exit(map, "Error\nInvalid number of floors\n");
	if (map->counts.wall < 1)
		free_map_and_exit(map, "Error\nInvalid number of walls\n");
}

void	basic_map_checks(t_map *map)
{
	int	i;

	if (!map->map)
	{
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		free(map);
		exit(1);
	}
	if (map->map[0] == NULL)
	{
		ft_putstr_fd("Error\nEmpty map\n", 2);
		free(map->map);
		free(map);
		exit(1);
	}
	if (map->map[1] == NULL)
		free_map_and_exit(map, "Error\nMap is not rectangular\n");
	i = 0;
	map->cols = ft_strlen(map->map[0]);
	while (map->map[i])
		if ((int)ft_strlen(map->map[i++]) != map->cols)
			free_map_and_exit(map, "Error\nMap is not rectangular\n");
	map->rows = i;
}
