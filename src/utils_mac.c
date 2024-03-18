/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mac.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:40:24 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 17:40:42 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	destroy_window(t_win w)
{
	if (w.mlx_ptr && w.win_ptr)
		mlx_destroy_window(w.mlx_ptr, w.win_ptr);
	if (w.mlx_ptr)
		free(w.mlx_ptr);
}
