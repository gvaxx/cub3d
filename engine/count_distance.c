/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_distance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 00:15:17 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/25 14:03:17 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_y_params(t_game *game, t_param *y_param, float ra)
{
	float atan;

	atan = -1 / tan(ra);
	y_param->dof = 0;
	if (ra > M_PI)
	{
		y_param->ry = (game->py / 64) * 64;
		y_param->yo = -64;
	}
	else if (ra < M_PI)
	{
		y_param->ry = (game->py / 64) * 64 + 64;
		y_param->yo = 64;
	}
	else if (ra == 0 || ra == M_PI)
	{
		y_param->rx = game->px;
		y_param->ry = game->py;
		y_param->xo = 64;
		y_param->yo = 0;
		y_param->dof = game->game_info.map_height;
	}
	y_param->rx = (game->py - y_param->ry) * atan + game->px;
	y_param->xo = -y_param->yo * atan;
}

void	fill_x_params(t_game *game, t_param *x_param, float ra)
{
	float ntan;

	x_param->dof = 0;
	ntan = -tan(ra);
	if (ra > M_PI / 2 && ra < 3 * M_PI / 2)
	{
		x_param->rx = (game->px / 64) * 64;
		x_param->xo = -64;
	}
	if (ra < M_PI / 2 || ra > 3 * M_PI / 2)
	{
		x_param->rx = (game->px / 64) * 64 + 64;
		x_param->xo = 64;
	}
	if (ra == 0 || ra == M_PI)
	{
		x_param->rx = game->px;
		x_param->ry = game->py;
		x_param->dof = game->game_info.map_width;
		x_param->xo = 64;
		x_param->yo = 0;
	}
	x_param->ry = (game->px - x_param->rx) * ntan + game->py;
	x_param->yo = -x_param->xo * ntan;
}

void	count_y_distance(t_param *y_param, t_game *game, float ra,
t_distance *y_distance)
{
	y_distance->dist = 100000;
	while (y_param->dof < game->game_info.map_height)
	{
		y_distance->mx = y_param->rx / 64;
		y_distance->my = y_param->ry / 64;
		if (ra > M_PI)
			y_distance->my -= 1;
		if (y_distance->mx < game->game_info.map_width && y_distance->mx > -1 &&
		y_distance->my < game->game_info.map_height && y_distance->my > -1
		&& game->game_info.map[y_distance->my][y_distance->mx] == '1')
		{
			y_distance->x = y_param->rx;
			y_distance->y = y_param->ry;
			y_param->dof = game->game_info.map_height;
			y_distance->dist = dist(game->px, game->py,
			y_distance->x, y_distance->y);
		}
		y_param->rx += y_param->xo;
		y_param->ry += y_param->yo;
		y_param->dof += 1;
	}
}

void	count_x_distance(t_param *x_param, t_game *game,
float ra, t_distance *x_distance)
{
	x_distance->dist = 100000;
	while (x_param->dof < game->game_info.map_width)
	{
		x_distance->mx = x_param->rx / 64;
		x_distance->my = x_param->ry / 64;
		if (ra > M_PI / 2 && ra < 3 * M_PI / 2)
			x_distance->mx -= 1;
		if (x_distance->mx < game->game_info.map_width && x_distance->mx > -1 &&
		x_distance->my < game->game_info.map_height && x_distance->my > -1 &&
		game->game_info.map[x_distance->my][x_distance->mx] == '1')
		{
			x_distance->x = x_param->rx;
			x_distance->y = x_param->ry;
			x_param->dof = game->game_info.map_width;
			x_distance->dist = dist(game->px, game->py, x_distance->x,
			x_distance->y);
		}
		x_param->rx += x_param->xo;
		x_param->ry += x_param->yo;
		x_param->dof++;
	}
}

void	distance_handler(t_game *game, t_line *line)
{
	t_param		y_param;
	t_param		x_param;
	t_distance	x_distance;
	t_distance	y_distance;

	fill_y_params(game, &y_param, line->ra);
	count_y_distance(&y_param, game, line->ra, &y_distance);
	fill_x_params(game, &x_param, line->ra);
	count_x_distance(&x_param, game, line->ra, &x_distance);
	count_less_distance(&y_distance, &x_distance, line, game);
}
