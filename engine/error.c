/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 13:53:54 by mcaptain          #+#    #+#             */
/*   Updated: 2020/06/25 14:45:25 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int error_handler(int error_num)
{
	if (error_num == MALLOC_MAP_ERROR)
		write(2, "Error\nmap's malloc return 0\n", 29);
	if (error_num == HANDLE_MAP_ERROR)
		write(2, "Error\nmap doesn't surrounded by wall\n", 38);
	if (error_num == WRONG_NUM_ARG)
		write(2, "Error\nwrong number of arguments\n", 33);
	if (error_num == WRONG_ARG)
		write(2, "Error\nwrong argument\n", 22);
	if (error_num == TEXTURE_FAILED)
		write(2, "Error\nwrong path to texture\n", 29);
	return(error_num);
}