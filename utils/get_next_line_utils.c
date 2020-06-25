/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 10:39:36 by mcaptain          #+#    #+#             */
/*   Updated: 2020/05/18 11:52:02 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int ch)
{
	while (*str)
	{
		if (*str == ch)
			return (char *)(str);
		str++;
	}
	if (*str == ch)
		return (char *)(str);
	return (0);
}

char	*ft_strdup(const char *s)
{
	char	*temp;
	int		len;

	len = ft_strlen(s);
	temp = malloc((len + 1) * sizeof(char));
	if (temp)
	{
		temp[len] = '\0';
		while (len--)
			temp[len] = s[len];
		return (temp);
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	int			i;
	const char	*source;

	source = s;
	i = 0;
	while (source[i])
		i++;
	return (i);
}

char	*ft_strnjoin(char *s1, char *s2, int n)
{
	char	*str1;
	char	*str2;
	char	*newstr;
	char	*startnewstr;
	int		len;

	if (!s1 || !s2)
		return (0);
	str1 = s1;
	str2 = s2;
	len = ft_strlen(s1) + n;
	newstr = malloc((len + 1) * sizeof(char));
	if (!newstr)
		return (0);
	startnewstr = newstr;
	while (*str1 && len--)
		*newstr++ = *str1++;
	while (*str2 && len--)
		*newstr++ = *str2++;
	free(s1);
	s1 = 0;
	*newstr = '\0';
	return (startnewstr);
}
