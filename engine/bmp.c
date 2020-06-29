/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 16:06:15 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/29 16:37:42 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		fill_header(int fd, t_game *game)
{
	int size;

	write(fd, "BM", 2);
	size = (game->game_info.resolution_x *
	game->game_info.resolution_y) * 4 + 54;
	write(fd, &size, 4);
	write(fd, "\0\0\0\0", 4);
	size = 54;
	write(fd, &size, 4);
	size = 40;
	write(fd, &size, 4);
	size = -game->game_info.resolution_y;
	write(fd, &game->game_info.resolution_x, 4);
	write(fd, &size, 4);
	size = 1;
	write(fd, &size, 2);
	write(fd, &game->main_img.bppx, 2);
	write(fd, "\0\0\0\0", 4);
	size = game->game_info.resolution_x * game->game_info.resolution_y * 4;
	write(fd, &size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, "\0\0\0\0", 4);
	return (size);
}

void	fill_image(int fd, t_game *game, int size)
{
	int i;

	i = 0;
	while (i < size)
		write(fd, &game->main_img.strt_img[i++], 1);
}

void	save_bmp(t_game *game)
{
	int	fd;
	int size;

	fd = open("cub3d.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	size = fill_header(fd, game);
	fill_image(fd, game, size);
	close(fd);
}

void	bmp_frame(t_game *game)
{
	game->sprites_num = 0;
	num_sprites(game);
	find_sprites(game);
	find_player_position(game);
	game->rax = game->game_info.resolution_x / (M_PI / 3) * DR;
	bias(game);
	drawrays3d(game);
}

int		screenshot(t_game *game)
{
	printf("ok\n");
	game->mlx_init = mlx_init();
	game->main_img.img = mlx_new_image(game->mlx_init,
	game->game_info.resolution_x, game->game_info.resolution_y);
	game->main_img.strt_img = mlx_get_data_addr(game->main_img.img,
	&game->main_img.bppx, &game->main_img.len_of_line, &game->main_img.endian);
	if (fill_texture(&game->texture_ea, game->game_info.texture_ea,
	game->mlx_init) < 0 || fill_texture(&game->texture_no,
	game->game_info.texture_no, game->mlx_init) < 0 ||
	fill_texture(&game->texture_we, game->game_info.texture_we,
	game->mlx_init) < 0 || fill_texture(&game->texture_so,
	game->game_info.texture_so, game->mlx_init) < 0 ||
	fill_texture(&game->texture_sprite, game->game_info.texture_sprite,
	game->mlx_init) < 0)
		return (error_handler(TEXTURE_FAILED));
	bmp_frame(game);
	save_bmp(game);
	destroy_game(1, game);
	return (0);
}
