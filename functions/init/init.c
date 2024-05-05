/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:24:18 by abougrai          #+#    #+#             */
/*   Updated: 2024/05/06 00:44:14 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_prog(t_game *cub)
{
	cub->mlx = NULL;
	cub->mlx_win = NULL;
	cub->setup = NULL;
	cub->map = NULL;
	cub->fd = 0;
	cub->NO = NULL;
	cub->SO = NULL;
	cub->WE = NULL;
	cub->EA = NULL;
	cub->path = NULL;
}

void	init(t_data *data, char *file)
{
	ft_memset(data, 0, sizeof(t_data));
	data->file = file;
}