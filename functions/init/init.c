/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:24:18 by abougrai          #+#    #+#             */
/*   Updated: 2024/08/16 11:59:53 by thomas           ###   ########.fr       */
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
			/// bien free tout meme truc apres
	}
	data->mlx_img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->mlx_img)
		exit_prog(data, "Error mlx img\n"); // tout free
	data->img_add = mlx_get_data_addr(data->mlx_img, &data->img_bpp,
			&data->img_len, &data->img_endian);
	data->img_no_add = mlx_get_data_addr(data->mlx_img, &data->img_no_bpp,
			&data->img_no_len, &data->img_no_endian);
}

void init_game(t_data *data)
{
    if (data->ray.direction == 'N')
    {
        data->ray.dirx = 0;
        data->ray.diry = -1;
        data->ray.plane_x = 0.66;
        data->ray.plane_y = 0;
    }
    else if (data->ray.direction == 'S')
    {
        data->ray.dirx = 0;
        data->ray.diry = 1;
        data->ray.plane_x = -0.66;
        data->ray.plane_y = 0;
    }
    else if (data->ray.direction == 'W')
    {
        data->ray.dirx = -1;
        data->ray.diry = 0;
        data->ray.plane_x = 0;
        data->ray.plane_y = -0.66;
    }
    else if (data->ray.direction == 'E')
    {
        data->ray.dirx = 1;
        data->ray.diry = 0;
        data->ray.plane_x = 0;
        data->ray.plane_y = 0.66;
    }
}

void init_ray(t_data *data)
{
    if (data->ray.direction == 'N')
        data->ray.angle = M_PI / 2; // 90 degrees
    else if (data->ray.direction == 'S')
        data->ray.angle = 3 * M_PI / 2; // 270 degrees
    else if (data->ray.direction == 'W')
        data->ray.angle = M_PI; // 180 degrees
    else if (data->ray.direction == 'E')
        data->ray.angle = 0; // 0 degrees

    // Update the direction vector based on the new angle
    data->ray.dirx = cos(data->ray.angle);
    data->ray.diry = sin(data->ray.angle);

    // Update the camera plane (perpendicular to the direction vector)
    data->ray.plane_x = -0.66 * sin(data->ray.angle);
    data->ray.plane_y = 0.66 * cos(data->ray.angle);
}

