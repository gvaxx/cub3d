/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 23:09:29 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/15 20:23:55 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	push(char **buf, char **line)
{
	char *n;
	char *temp;

	if ((n = ft_strchr(*buf, '\n')))
	{
		*line = ft_strnjoin(*line, *buf, n - *buf);
		temp = *buf;
		*buf = ft_strdup(n + 1);
		free(temp);
		temp = 0;
		if (!(*line) || !(*buf))
			return (-1);
		return (1);
	}
	*line = ft_strnjoin(*line, *buf, 10);
	return (0);
}

int	free_all(char **buf, char **line, int flag)
{
	if (flag)
	{
		free(*buf);
		free(*line);
		*line = 0;
		*buf = 0;
		return (-1);
	}
	free(*buf);
	*buf = 0;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*buf[1];
	char		temp[1];
	int			n;
	int			p;

	if ((read(fd, temp, 0) < 0) || !line ||
	!(*line = ft_strdup("")))
		return (-1);
	if (*buf)
		if ((p = push(buf, line)))
			return (p == 1 ? 1 : free_all(buf, line, 1));
	free(*buf);
	if (!(*buf = malloc(sizeof(char *) * (10 + 1))))
		return (-1);
	while (0 < (n = read(fd, buf[0], 10)))
	{
		buf[0][n] = '\0';
		if ((p = push(buf, line)))
			return (p == 1 ? 1 : free_all(buf, line, 1));
	}
	return (n == 0 ? free_all(buf, line, 0) : free_all(buf, line, 1));
}
