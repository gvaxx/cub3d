/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 00:21:06 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/28 16:34:54 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "cub3d.h"

int		cub_file_manager(int argc, char **argv, t_info *game_info)
{
	char	*line;
	int		fd;
	int		num_of_args;
	int		n;

	num_of_args = 0;
	if (argc == 1)
		return (-1);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (-1);
	while ((get_next_line(fd, &line) > 0))
	{
		if (*line)
		{
			num_of_args++;
			n = cub_file_parser(line, fd, game_info);
			if (n < 0)
				return (error_handler(WRONG_ARG));
			if (n == 1)
				break ;
		}
		free(line);
	}
	if (num_of_args != 9)
		return (error_handler(WRONG_NUM_ARG));
	close(fd);
	return (0);
}

int		main(int argc, char **argv)
{
	t_game game;

	if (cub_file_manager(argc, argv, &game.game_info) >= 0)
	{
		if (argc == 3)
			if (ft_strncmp("--save", argv[2], ft_strlen(argv[2])) == 0)
				return (screenshot(&game));
			else
				return (error_handler(WRONG_SECOND_ARGUMENT));
		else
			return (window_init(&game));
	}
}
