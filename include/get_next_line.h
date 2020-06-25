/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 23:28:30 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/13 18:07:16 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>

int				get_next_line(int fd, char **line);
char			*ft_strnjoin(char *s1, char *s2, int n);
char			*ft_strchr(const char *str, int ch);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
int				push(char **buf, char **line);

#endif
