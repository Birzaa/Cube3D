/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:24:18 by abougrai          #+#    #+#             */
/*   Updated: 2024/05/08 14:26:35 by thomas           ###   ########.fr       */
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
	data->mlx_win = mlx_new_window(data->mlx, 1280, 720, "cube3D");
	if (!data->mlx_win)
	{
		exit_prog(data, "Incorrect initialization\n");
	}
}

void	init_raycast(t_ray *ray)
{
	ray->dirX = -1;
	ray->dirY = 0;
	ray->planeX = 0;
	ray->planeY = 0.66;
	ray->time = 0;
	ray->oldTime = 0;
}