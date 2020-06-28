/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 23:51:06 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/28 16:41:20 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	forward_handler(t_game *game)
{
	int my;
	int mx;
	int next_step;

	my = game->py + (game->pdy * 2);
	mx = game->px + (game->pdx * 2);
	mx = mx / 64;
	my = my / 64;
	if (game->game_info.map[my][mx] != '1')
	{
		game->px += game->pdx;
		game->py += game->pdy;
		return (1);
	}
	return (0);
}

int	back_handler(t_game *game)
{
	int my;
	int mx;
	int next_step;

	my = game->py - (game->pdy * 2);
	mx = game->px - (game->pdx * 2);
	mx = mx / 64;
	my = my / 64;
	if (game->game_info.map[my][mx] != '1')
	{
		game->px -= game->pdx;
		game->py -= game->pdy;
		return (1);
	}
	return (0);
}

int	left_handler(t_game *game)
{
	int my;
	int mx;
	int next_step;

	my = game->py + (game->prly * 2);
	mx = game->px + (game->prlx * 2);
	mx = mx / 64;
	my = my / 64;
	if (game->game_info.map[my][mx] != '1')
	{
		game->px += game->prlx;
		game->py += game->prly;
		return (1);
	}
	return (0);
}

int	right_handler(t_game *game)
{
	int my;
	int mx;
	int next_step;

	my = game->py - (game->prly * 2);
	mx = game->px - (game->prlx * 2);
	mx = mx / 64;
	my = my / 64;
	if (game->game_info.map[my][mx] != '1')
	{
		game->px -= game->prlx;
		game->py -= game->prly;
		return (1);
	}
	return (0);
}

int	key_win(int key, t_game *game)
{
	if (key == 119)
		if (forward_handler(game) == 0)
			return (0);
	if (key == 115)
		if (back_handler(game) == 0)
			return (0);
	if (key == 100)
		if (left_handler(game) == 0)
			return (0);
	if (key == 97)
		if (right_handler(game) == 0)
			return (0);
	if (key == 65361)
	{
		game->pa = is_full_circle(game->pa - 0.05);
		bias(game);
	}
	if (key == 65363)
	{
		game->pa = is_full_circle(game->pa + 0.05);
		bias(game);
	}
	if (key == 65307)
	{
		destroy_game(1, game);
		return (0);
	}
	drawrays3d(game);
	mlx_put_image_to_window(game->mlx_init,
	game->window, game->main_img.img, 0, 0);
}
