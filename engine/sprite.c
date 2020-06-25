/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 00:26:17 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/25 02:06:36 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_sprite_tech(t_game *game, t_tech *sp_t, t_sprite *sprite)
{
	sp_t->sprite_dir = atan2(sprite->y - game->py, sprite->x - game->px);
	while (sp_t->sprite_dir - game->pa > M_PI)
		sp_t->sprite_dir -= 2 * M_PI;
	while (sp_t->sprite_dir - game->pa < -M_PI)
		sp_t->sprite_dir += 2 * M_PI;
	sp_t->sp_h = game->game_info.resolution_y * 64 / sprite->dist;
	sp_t->sp_w = sp_t->sp_h * game->texture_sprite.width
	/ game->texture_sprite.height;
	sp_t->sp_dw = (sp_t->sprite_dir - game->pa) * game->game_info.resolution_x
	/ (M_PI / 3) + (game->game_info.resolution_x / 2) - sp_t->sp_w / 2;
	sp_t->sp_dh = game->game_info.resolution_y / 2 - sp_t->sp_h / 2;
}

void	draw_sprite(t_game *game, t_sprite *sprite,
float *depth_buffer, t_image sp_im)
{
	t_tech		sp_t;
	size_t		i;
	size_t		j;

	i = 0;
	fill_sprite_tech(game, &sp_t, sprite);
	while (i < sp_t.sp_w)
	{
		if (i + sp_t.sp_dw >= 0 && sp_t.sp_dw + i < game->game_info.resolution_x
		&& depth_buffer[sp_t.sp_dw + i] > sprite->dist)
		{
			j = 0;
			while (j < sp_t.sp_h)
			{
				if (sp_t.sp_dh + j >= 0 && sp_t.sp_dh + j <
				game->game_info.resolution_y)
					replace_pixel(&game->main_img.strt_img[(sp_t.sp_dw + i)
					* 4 + ((sp_t.sp_dh + j) * game->main_img.len_of_line)],
					&sp_im.strt_img[((i * sp_im.width / sp_t.sp_w) * 4) +
					((j * sp_im.height / sp_t.sp_h) * sp_im.len_of_line)]);
				j++;
			}
		}
		i++;
	}
}

void	sort_sprites(t_sprite *sprite_array, size_t num)
{
	t_sprite	temp;
	int			i;

	i = 1;
	while (i < num)
	{
		if (sprite_array[i].dist > sprite_array[i - 1].dist)
		{
			temp = sprite_array[i];
			sprite_array[i] = sprite_array[i - 1];
			sprite_array[i - 1] = temp;
		}
		i++;
	}
}

void	sprite_dist(t_game *game)
{
	int i;

	i = 0;
	while (i < game->sprites_num)
		game->sprites_array[i++].dist = dist(game->px,
		game->py, game->sprites_array[i].x, game->sprites_array[i].y);
}

void	sprite_handler(t_game *game, float *depth_buffer)
{
	int i;

	i = 0;
	sprite_dist(game);
	sort_sprites(game->sprites_array, game->sprites_num);
	while (i < game->sprites_num)
	{
		draw_sprite(game, &game->sprites_array[i++],
		depth_buffer, game->texture_sprite);
	}
}
