/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:24:18 by abougrai          #+#    #+#             */
/*   Updated: 2024/05/07 15:33:33 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_data *data, char *file)
{
	ft_memset(data, 0, sizeof(t_data));
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		ft_putstr_fd("Incorrect initialization", 2);
		exit(1);
	}
	data->file = file;
	data->nb_line = -1;
}

void	init_window(t_data *data)
{
	data->mlx_win = mlx_new_window(data->mlx, 1280,
			720, "cube3D");
	if (!data->mlx_win)
	{
		exit_prog(data, "Incorrect initialization\n");
	}
}

void	init_player(t_data *data)
{
	data->player.x = data->start_x;
	data->player.y = data->start_y;
	data->player.angle = 0.0;
}