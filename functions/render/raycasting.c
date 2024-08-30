/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:45:47 by thomas            #+#    #+#             */
/*   Updated: 2024/08/30 13:27:46 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	data->ray_var.color = data->ray_var.ceiling_color;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			draw_pixel(data, data->img.addr, x, y);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_data *data)
{
	int	y;
	int	x;

	y = SCREEN_HEIGHT / 2;
	data->ray_var.color = data->ray_var.floor_color;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			draw_pixel(data, data->img.addr, x, y);
			x++;
		}
		y++;
	}
}

void	get_value_ray(t_data *data, int col)
{
	data->ray_var.camera_x = 2 * col / (double)SCREEN_WIDTH - 1;
	data->ray_var.ray_dir_x = data->ray.dirx + data->ray.plane_x
		* data->ray_var.camera_x;
	data->ray_var.ray_dir_y = data->ray.diry + data->ray.plane_y
		* data->ray_var.camera_x;
	data->ray_var.map_x = (int)data->ray.posx;
	data->ray_var.map_y = (int)data->ray.posy;
	data->ray_var.delta_dist_x = fabs(1 / data->ray_var.ray_dir_x);
	data->ray_var.delta_dist_y = fabs(1 / data->ray_var.ray_dir_y);
	data->ray_var.hit = 0;
}

void	raycast(t_data *data)
{
	int	col;

	col = 0;
	while (col < SCREEN_WIDTH)
	{
		get_value_ray(data, col);
		distance_wall(data);
		hit_wall(data);
		get_value_draw_wall(data);
		texture_wall_position_side(data);
		draw_wall(data, col);
		col++;
	}
}

void	init_render(t_data *data)
{
	create_img(data);
	draw_ceiling(data);
	draw_floor(data);
	raycast(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	mlx_destroy_image(data->mlx, data->img.img);
}
