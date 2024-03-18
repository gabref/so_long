/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 01:36:02 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 17:22:36 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/map.h"
#include "../inc/so_long.h"

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

t_map	*check_args(int ac, char **av)
{
	t_map	*map;
	char	*map_inline;

	if (ac != 2)
		exit_error_message("Error\nInvalid number of arguments\n");
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".ber", 4))
		exit_error_message("Error\nInvalid file extension\n");
	map_inline = read_map(av[1]);
	map = malloc(sizeof(t_map));
	if (!map)
	{
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		free(map_inline);
		exit(1);
	}
	map->map = ft_split_word(map_inline, "\n");
	free(map_inline);
	basic_map_checks(map);
	check_map_walls(map);
	check_map_valid_chars(map);
	check_map_counts(map);
	return (map);
}

void	free_map(t_map *map)
{
	ft_free_2d_array((void **)map->map);
	if (map)
		free(map);
}

void	free_map_and_exit(t_map *map, char *message)
{
	free_map(map);
	ft_putstr_fd(message, 2);
	exit(1);
}
