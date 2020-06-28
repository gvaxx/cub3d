/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:26:04 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/28 16:35:28 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycasting_line(t_game *game, t_line *line, int r, float *depth_buffer)
{
	int		lineh;
	int		lineo;
	int		i_y;
	int		t_y;
	int		y;

	y = 0;
	line->dist = line->dist * cos(is_full_circle(game->pa - line->ra));
	lineh = game->game_info.resolution_y * 64 / line->dist;
	lineo = game->game_info.resolution_y / 2 - lineh / 2;
	while (y < lineh)
	{
		t_y = (y * line->texture->width) / lineh;
		i_y = y + lineo;
		if (i_y >= 0 && i_y < game->game_info.resolution_y)
			replace_pixel(&game->main_img.strt_img[r * 4 +
			(game->main_img.len_of_line * (i_y))],
			&line->start_texture[(int)line->x_percent * 4
			+ (line->texture->len_of_line * t_y)]);
		y++;
	}
	print_floor(r, 0, lineo, game);
	print_ceil(r, lineo + lineh, lineo, game);
}

void	drawrays3d(t_game *game)
{
	t_line	line;
	float	depth_buffer[game->game_info.resolution_x];
	int		r;

	r = 0;
	line.ra = is_full_circle(game->pa - (30 * DR));
	while (r < game->game_info.resolution_x)
	{
		distance_handler(game, &line);
		raycasting_line(game, &line, r, depth_buffer);
		depth_buffer[r++] = line.dist;
		line.ra = is_full_circle(line.ra + DR / game->rax);
	}
	sprite_handler(game, depth_buffer);
}

int		fill_texture(t_image *image, char *name, void *mlx_init)
{
	if ((image->img = mlx_xpm_file_to_image(mlx_init, name,
	&image->width, &image->height)) == NULL ||
	(image->strt_img = mlx_get_data_addr(image->img,
	&image->bppx, &image->len_of_line, &image->endian)) == NULL)
		return (-1);
	return (0);
}

void	first_frame(t_game *game)
{
	game->sprites_num = 0;
	num_sprites(game);
	find_sprites(game);
	find_player_position(game);
	game->rax = game->game_info.resolution_x / (M_PI / 3) * DR;
	bias(game);
	drawrays3d(game);
	mlx_put_image_to_window(game->mlx_init, game->window,
	game->main_img.img, 0, 0);
}

int		window_init(t_game *game)
{
	game->mlx_init = mlx_init();
	game->window = mlx_new_window(game->mlx_init, game->game_info.resolution_x,
	game->game_info.resolution_y, "cub3d");
	game->main_img.img = mlx_new_image(game->mlx_init,
	game->game_info.resolution_x, game->game_info.resolution_y);
	game->main_img.strt_img = mlx_get_data_addr(game->main_img.img,
	&game->main_img.bppx, &game->main_img.len_of_line, &game->main_img.endian);
	if (fill_texture(&game->texture_ea, game->game_info.texture_ea,
	game->mlx_init) < 0 || fill_texture(&game->texture_no,
	game->game_info.texture_no, game->mlx_init) < 0 ||
	fill_texture(&game->texture_we, game->game_info.texture_we,
	game->mlx_init) < 0 ||
	fill_texture(&game->texture_so, game->game_info.texture_so,
	game->mlx_init) < 0 ||
	fill_texture(&game->texture_sprite, game->game_info.texture_sprite,
	game->mlx_init) < 0)
		return (error_handler(TEXTURE_FAILED));
	first_frame(game);
	mlx_hook(game->window, 2, 1L, key_win, game);
	mlx_hook(game->window, 17, 0L, destroy_game, game);
	mlx_loop(game->mlx_init);
}
