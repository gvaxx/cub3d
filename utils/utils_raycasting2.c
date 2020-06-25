/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:41:35 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/25 14:03:45 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	bias(t_game *game)
{
	game->pdx = cos(game->pa) * 30;
	game->pdy = sin(game->pa) * 30;
	game->prlx = cos(game->pa + M_PI / 2) * 30;
	game->prly = sin(game->pa + M_PI / 2) * 30;
}
