/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:11:06 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/28 16:33:16 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

int		cub_file_parser2(char *line, int fd, t_info *game_info)
{
	if (ft_memcmp(line, "S", 1) == 0)
	{
		game_info->texture_sprite = ft_strtrim(line, "S ");
		return (0);
	}
	else if (ft_memcmp(line, "R", 1) == 0)
		return (resolution_handler(line + 1, game_info));
	else if (ft_memcmp(line, "F", 1) == 0)
	{
		game_info->color_floor = color_handler(line + 1);
		return (0);
	}
	else if (ft_memcmp(line, "C", 1) == 0)
	{
		game_info->color_ceil = color_handler(line + 1);
		return (0);
	}
	else if ((ft_memcmp(line, " ", 1) == 0) || (ft_memcmp(line, "1", 1) == 0))
		return (map_manager(fd, line, game_info));
	return (-1);
}

int		cub_file_parser(char *line, int fd, t_info *game_info)
{
	if (ft_memcmp(line, "SO", 2) == 0)
	{
		game_info->texture_so = ft_strtrim(line, "SO ");
		return (0);
	}
	else if (ft_memcmp(line, "NO", 2) == 0)
	{
		game_info->texture_no = ft_strtrim(line, "NO ");
		return (0);
	}
	else if (ft_memcmp(line, "WE", 2) == 0)
	{
		game_info->texture_we = ft_strtrim(line, "WE ");
		return (0);
	}
	else if (ft_memcmp(line, "EA", 2) == 0)
	{
		game_info->texture_ea = ft_strtrim(line, "EA ");
		return (0);
	}
	return (cub_file_parser2(line, fd, game_info));
}

int		resolution_handler(char *line, t_info *game_info)
{
	game_info->resolution_x = ft_atoi(line);
	line = next_number(line);
	game_info->resolution_y = ft_atoi(line);
	if (game_info->resolution_x <= 0 || game_info->resolution_x <= 0)
		return (-1);
	if (game_info->resolution_x > MAX_WIDTH)
		game_info->resolution_x = MAX_WIDTH;
	if (game_info->resolution_y > MAX_HEIGHT)
		game_info->resolution_y = MAX_HEIGHT;
	return (0);
}

int		color_handler(char *line)
{
	int color;

	color = 0;
	color += ft_atoi(line);
	color = color << 8;
	line = next_number(line);
	line++;
	color += ft_atoi(line);
	color = color << 8;
	line = next_number(line);
	line++;
	color += ft_atoi(line);
	return (color);
}

char	*next_number(char *line)
{
	while (*line == ' ')
		line++;
	while (ft_isdigit(*line))
		line++;
	return (line);
}
