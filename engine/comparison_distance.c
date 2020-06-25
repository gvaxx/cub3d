/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparison_distance.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 00:12:22 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/25 13:48:41 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	x_less_distance(t_distance *x_distance, t_line *line, t_game *game)
{
	if (M_PI / 2 < line->ra && line->ra < 3 * M_PI / 2)
	{
		line->start_texture = game->texture_we.strt_img;
		line->texture = &game->texture_we;
		line->x_percent = -((x_distance->y - (((int)x_distance->y / 64) * 64)
		- 64) / 64) * (game->texture_we.width);
	}
	else
	{
		line->start_texture = game->texture_ea.strt_img;
		line->texture = &game->texture_ea;
		line->x_percent = ((x_distance->y - (((int)x_distance->y / 64) * 64))
		/ 64) * (game->texture_ea.width);
	}
	line->dist = x_distance->dist;
}

void	y_less_distance(t_distance *y_distance, t_line *line, t_game *game)
{
	if (line->ra > M_PI)
	{
		line->start_texture = game->texture_no.strt_img;
		line->texture = &game->texture_no;
		line->x_percent = ((y_distance->x - (((int)y_distance->x / 64) * 64))
		/ 64) * (game->texture_no.width);
	}
	else
	{
		line->start_texture = game->texture_so.strt_img;
		line->texture = &game->texture_so;
		line->x_percent = -((y_distance->x - (((int)y_distance->x / 64) * 64)
		- 64) / 64 * (game->texture_so.width));
	}
	line->dist = y_distance->dist;
}

void	count_less_distance(t_distance *y_distance, t_distance *x_distance,
t_line *line, t_game *game)
{
	if (y_distance->dist > x_distance->dist)
		x_less_distance(x_distance, line, game);
	if (y_distance->dist < x_distance->dist)
		y_less_distance(y_distance, line, game);
}
