/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:24:18 by abougrai          #+#    #+#             */
/*   Updated: 2024/05/05 13:27:16 by abougrai         ###   ########.fr       */
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
