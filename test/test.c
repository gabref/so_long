/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:14:44 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 14:33:08 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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

int	main(void)
{
	unsigned int	min;
	unsigned int	max;
	int				i;

	min = 10;
	max = 20;
	i = 0;
	while (i++ < 10)
	{
		printf("%d\n", rand_range(min, max));
	}
	return (0);
}
