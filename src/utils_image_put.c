/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_image_put.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:24:49 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/18 17:29:51 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	destroy_image(t_img img)
{
	if (img.img_ptr && img.win.mlx_ptr)
		mlx_destroy_image(img.win.mlx_ptr, img.img_ptr);
}

void	put_pixel_img(t_img img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < img.w && y < img.h)
	{
		dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

unsigned int	get_pixel_img(t_img img, int x, int y)
{
	int	img_ly;
	int	img_x;

	img_ly = y * img.line_len;
	img_x = x * img.bpp / 8;
	return (*(unsigned int *)((img.addr + img_ly + img_x)));
}

static int	put_pixel_valid(t_img img, int x, int y)
{
	int	a;
	int	b;

	if (x >= 0 && y >= 0 && x < img.w && y < img.h)
	{
		a = y * img.line_len + x * (img.bpp / 8);
		b = y * img.line_len + x * (img.bpp / 8);
		return (*(unsigned int *)(img.addr + a) != 0xFF000000
			&& *(unsigned int *)(img.addr + b) != 0x00000000);
	}
	return (0);
}

void	put_img_to_img(t_img dst, t_img src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < src.w)
	{
		j = 0;
		while (j < src.h)
		{
			if (put_pixel_valid(src, i, j))
				put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}
