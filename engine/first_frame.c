/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 00:11:08 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/25 00:26:04 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_direction(char c, float *pa)
{
	if (c == 'W')
		*pa = M_PI;
	if (c == 'S')
		*pa = M_PI / 2;
	if (c == 'N')
		*pa = M_PI * 3 / 2;
	if (c == 'E')
		*pa = 0;
}

void	find_player_position(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < game->game_info.map_height)
	{
		x = 0;
		while (x < game->game_info.map_width)
		{
			if (is_in_set(game->game_info.map[y][x], "SWEN"))
			{
				game->px = x * 64 + 32;
				game->py = y * 64 + 32;
				player_direction(game->game_info.map[y][x], &game->pa);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	find_sprites(t_game *game)
{
	int x;
	int y;
	int i;

	game->sprites_array = malloc(sizeof(t_sprite) * game->sprites_num);
	y = 0;
	i = 0;
	while (y < game->game_info.map_height)
	{
		x = 0;
		while (x < game->game_info.map_width)
		{
			if (game->game_info.map[y][x] == '2')
			{
				game->sprites_array[i].x = x * 64 + 32;
				game->sprites_array[i].y = y * 64 + 32;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	num_sprites(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < game->game_info.map_height)
	{
		x = 0;
		while (x < game->game_info.map_width)
		{
			if (game->game_info.map[y][x] == '2')
				game->sprites_num++;
			x++;
		}
		y++;
	}
}
