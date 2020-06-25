/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:49:37 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/25 14:59:34 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void map_destroyer(char **map, int height)
{
	int i;

	i = 0;
	while (i < height)
		free(map[i++]);
	free(map);
}

void destroy_game(t_game *game)
{
	printf("ok\n");
	mlx_destroy_image(game->mlx_init, game->main_img.img);
	mlx_destroy_image(game->mlx_init, game->texture_ea.img);
	mlx_destroy_image(game->mlx_init, game->texture_no.img);
	mlx_destroy_image(game->mlx_init, game->texture_so.img);
	mlx_destroy_image(game->mlx_init, game->texture_we.img);
	map_destroyer(game->game_info.map, game->game_info.map_height);
}