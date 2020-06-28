/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 00:21:06 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/28 16:35:18 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "cub3d.h"

int		is_in_set(char c, char const *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

int		is_in_around(char *c)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if ((is_in_set(c[i++], "012SWEN") == 0))
			return (-1);
	}
}

int		add_white_space(char **line, int max_height, int max_width)
{
	int		y;
	int		len;
	char	*new_str;

	y = 0;
	while (y < max_height)
	{
		len = ft_strlen(line[y]);
		if (len != max_width)
		{
			if ((new_str = malloc(sizeof(char *) * (max_width + 1))) == NULL)
				return (-1);
			ft_strlcpy(new_str, line[y], len + 1);
			while (len != max_width)
				new_str[len++] = ' ';
			new_str[len] = '\0';
			free(line[y]);
			line[y] = new_str;
		}
		y++;
	}
	return (1);
}

int		check_map(char **line, int max_height, int max_width)
{
	int x;
	int y;

	y = 0;
	while (y < max_height)
	{
		x = 0;
		while (x < max_width)
		{
			if (is_in_set(line[y][x], " 012SWEN") == 0)
				return (-1);
			if (is_in_set(line[y][x], "02SWEN"))
			{
				if (x == 0 || y == 0 || x == max_width - 1 ||
					max_height - 1 == y ||
					(is_in_around(&line[y - 1][x - 1])) == -1 ||
					(is_in_around(&line[y][x - 1])) == -1 ||
					(is_in_around(&line[y + 1][x - 1])) == -1)
					return (-1);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int		map_manager(int fd, char *line, t_info *game_info)
{
	char	**map;
	int		height;
	int		max_width;

	height = 0;
	if ((map = malloc(sizeof(char *) * 300)) == NULL)
		return (error_handler(MALLOC_MAP_ERROR));
	max_width = ft_strlen(line);
	map[height++] = line;
	while ((get_next_line(fd, &map[height]) > 0))
	{
		if (ft_strlen(map[height++]) > max_width)
			max_width = ft_strlen(map[height - 1]);
	}
	free(map[height]);
	if (add_white_space(map, height, max_width) < 0)
		return (error_handler(MALLOC_MAP_ERROR));
	if ((check_map(map, height, max_width) == -1))
		return (error_handler(HANDLE_MAP_ERROR));
	game_info->map = map;
	game_info->map_height = height;
	game_info->map_width = max_width;
	return (1);
}
