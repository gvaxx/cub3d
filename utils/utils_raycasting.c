/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:41:41 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/29 16:09:04 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_img_pxl(char *img, unsigned int color)
{
	int i;

	i = 4;
	while (i--)
	{
		*img++ = color;
		color = color >> 8;
	}
}

void	replace_pixel(char *convert_img, char *source_img)
{
	if (source_img[0] == 0 && source_img[1] == 0 &&
	source_img[2] == 0)
		return ;
	convert_img[0] = source_img[0];
	convert_img[1] = source_img[1];
	convert_img[2] = source_img[2];
	convert_img[3] = source_img[3];
}

void	print_floor(int x, int y, int length, t_game *game)
{
	int	i;

	i = 0;
	while (i < length)
	{
		print_img_pxl(&game->main_img.strt_img[(x) * 4 +
		(game->main_img.len_of_line * (y + i))], game->game_info.color_floor);
		i++;
	}
}

void	print_ceil(int x, int y, int length, t_game *game)
{
	int	i;

	i = 0;
	while (i < length)
	{
		print_img_pxl(&game->main_img.strt_img[(x) * 4 +
		(game->main_img.len_of_line * (y + i))], game->game_info.color_ceil);
		i++;
	}
}

float	is_full_circle(float ra)
{
	if (ra < 0)
		return (ra += 2 * M_PI);
	if (ra > 2 * M_PI)
		return (ra -= 2 * M_PI);
	return (ra);
}
