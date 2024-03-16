/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galves-f <galves-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 08:54:50 by galves-f          #+#    #+#             */
/*   Updated: 2024/03/16 16:29:17 by galves-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	put_font(t_game *g, int digit, int i)
{
	t_img	font;

	if (digit == 0)
		font = g->score_font.zero;
	if (digit == 1)
		font = g->score_font.one;
	if (digit == 2)
		font = g->score_font.two;
	if (digit == 3)
		font = g->score_font.three;
	if (digit == 4)
		font = g->score_font.four;
	if (digit == 5)
		font = g->score_font.five;
	if (digit == 6)
		font = g->score_font.six;
	if (digit == 7)
		font = g->score_font.seven;
	if (digit == 8)
		font = g->score_font.eight;
	if (digit == 9)
		font = g->score_font.nine;
	put_img_to_img(g->score_img, g->score_font.black, 12 * i, 0);
	put_img_to_img(g->score_img, font, 12 * i, 0);
}

void	update_score(t_game *g)
{
	int	i;
	int	score;
	int	digit;

	i = 4;
	score = g->moves;
	while (i >= 0)
	{
		digit = score % 10;
		score /= 10;
		put_font(g, digit, i);
		i--;
	}
	mlx_put_image_to_window(g->game_img.win.mlx_ptr, g->game_img.win.win_ptr,
		g->score_img.img_ptr, g->win.width / 2 - 24, g->win.height - 67);
}

t_font	load_score_font(t_game *g)
{
	g->score_font.zero = new_file_img("assets/digits/0.xpm", g->win);
	g->score_font.one = new_file_img("assets/digits/1.xpm", g->win);
	g->score_font.two = new_file_img("assets/digits/2.xpm", g->win);
	g->score_font.three = new_file_img("assets/digits/3.xpm", g->win);
	g->score_font.four = new_file_img("assets/digits/4.xpm", g->win);
	g->score_font.five = new_file_img("assets/digits/5.xpm", g->win);
	g->score_font.six = new_file_img("assets/digits/6.xpm", g->win);
	g->score_font.seven = new_file_img("assets/digits/7.xpm", g->win);
	g->score_font.eight = new_file_img("assets/digits/8.xpm", g->win);
	g->score_font.nine = new_file_img("assets/digits/9.xpm", g->win);
	g->score_font.black = new_file_img("assets/digits/black.xpm", g->win);
	return (g->score_font);
}

void	free_fonts(t_game *g)
{
	destroy_image(g->score_font.black);
	destroy_image(g->score_font.zero);
	destroy_image(g->score_font.one);
	destroy_image(g->score_font.two);
	destroy_image(g->score_font.three);
	destroy_image(g->score_font.four);
	destroy_image(g->score_font.five);
	destroy_image(g->score_font.six);
	destroy_image(g->score_font.seven);
	destroy_image(g->score_font.eight);
	destroy_image(g->score_font.nine);
}
