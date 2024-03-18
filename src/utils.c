/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:14:01 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 15:15:22 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"
#include <sys/time.h>

uint64_t	gettimeofday_ms(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

uint64_t	timestamp_in_ms(t_game *game)
{
	if (!game)
		return (0);
	if (game->created_at == 0)
		game->created_at = gettimeofday_ms();
	return (gettimeofday_ms() - game->created_at);
}

unsigned int	rand_range(unsigned int min, unsigned int max)
{
	static unsigned short	lfsr = 0xACE1u;
	unsigned int			range;
	unsigned int			result;
	unsigned int			bit;

	range = max - min + 1;
	while (1)
	{
		bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
		lfsr = (lfsr >> 1) | (bit << 15);
		result = lfsr % range;
		if (result < range)
			break ;
	}
	return (min + result);
}
