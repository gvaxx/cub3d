/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:49:37 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/29 15:35:57 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_destroyer(char **map, int height)
{
	int i;

	i = 0;
	while (i < height)
		free(map[i++]);
	free(map);
}

int		destroy_game(int win, t_game *game)
{
	if (win == 1)
	{
		mlx_destroy_image(game->mlx_init, game->main_img.img);
		mlx_destroy_image(game->mlx_init, game->texture_ea.img);
		mlx_destroy_image(game->mlx_init, game->texture_no.img);
		mlx_destroy_image(game->mlx_init, game->texture_so.img);
		mlx_destroy_image(game->mlx_init, game->texture_we.img);
		map_destroyer(game->game_info.map, game->game_info.map_height);
		mlx_destroy_window(game->mlx_init, game->window);
	}
	exit(0);
	return (0);
}
