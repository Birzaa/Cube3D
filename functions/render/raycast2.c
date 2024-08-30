/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:18:52 by thomas            #+#    #+#             */
/*   Updated: 2024/08/30 13:30:53 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	distance_wall(t_data *data)
{
	if (data->ray_var.ray_dir_x < 0)
	{
		data->ray_var.step_x = -1;
		data->ray_var.side_dist_x = (data->ray.posx - data->ray_var.map_x)
			* data->ray_var.delta_dist_x;
	}
	else
	{
		data->ray_var.step_x = 1;
		data->ray_var.side_dist_x = (data->ray_var.map_x + 1.0 - data->ray.posx)
			* data->ray_var.delta_dist_x;
	}
	if (data->ray_var.ray_dir_y < 0)
	{
		data->ray_var.step_y = -1;
		data->ray_var.side_dist_y = (data->ray.posy - data->ray_var.map_y)
			* data->ray_var.delta_dist_y;
	}
	else
	{
		data->ray_var.step_y = 1;
		data->ray_var.side_dist_y = (data->ray_var.map_y + 1.0 - data->ray.posy)
			* data->ray_var.delta_dist_y;
	}
}

void	hit_wall(t_data *data)
{
	while (data->ray_var.hit == 0)
	{
		if (data->ray_var.side_dist_x < data->ray_var.side_dist_y)
		{
			data->ray_var.side_dist_x += data->ray_var.delta_dist_x;
			data->ray_var.map_x += data->ray_var.step_x;
			data->ray_var.side = 0;
		}
		else
		{
			data->ray_var.side_dist_y += data->ray_var.delta_dist_y;
			data->ray_var.map_y += data->ray_var.step_y;
			data->ray_var.side = 1;
		}
		if (data->map[data->ray_var.map_y][data->ray_var.map_x] == '1')
			data->ray_var.hit = 1;
	}
	if (data->ray_var.side == 0)
		data->ray_var.perp_wall_dist = (data->ray_var.map_x - data->ray.posx
				+ (1 - data->ray_var.step_x) / 2) / data->ray_var.ray_dir_x;
	else
		data->ray_var.perp_wall_dist = (data->ray_var.map_y - data->ray.posy
				+ (1 - data->ray_var.step_y) / 2) / data->ray_var.ray_dir_y;
}

void	get_value_draw_wall(t_data *data)
{
	data->ray_var.line_height = (int)(SCREEN_HEIGHT
			/ data->ray_var.perp_wall_dist);
	data->ray_var.draw_start = (data->ray_var.line_height * -1) / 2
		+ SCREEN_HEIGHT / 2;
	if (data->ray_var.draw_start < 0)
		data->ray_var.draw_start = 0;
	data->ray_var.draw_end = data->ray_var.line_height / 2 + SCREEN_HEIGHT / 2;
	if (data->ray_var.draw_end >= SCREEN_HEIGHT)
		data->ray_var.draw_end = SCREEN_HEIGHT - 1;
	if (data->ray_var.side == 1)
	{
		if (data->ray_var.ray_dir_y > 0)
			data->ray_var.texture = data->e_path;
		else
			data->ray_var.texture = data->o_path;
	}
	else
	{
		if (data->ray_var.ray_dir_x > 0)
			data->ray_var.texture = data->s_path;
		else
			data->ray_var.texture = data->n_path;
	}
}

void	texture_wall_position_side(t_data *data)
{
	data->ray_var.texture_data = mlx_get_data_addr(data->ray_var.texture,
			&data->img.bits_per_pixel, &data->img.line_length,
			&data->img.endian);
	data->ray_var.tex_width = data->img_width;
	data->ray_var.tex_height = data->img_height;
	if (data->ray_var.side == 0)
		data->ray_var.wall_x = data->ray.posy + data->ray_var.perp_wall_dist
			* data->ray_var.ray_dir_y;
	else
		data->ray_var.wall_x = data->ray.posx + data->ray_var.perp_wall_dist
			* data->ray_var.ray_dir_x;
	data->ray_var.wall_x -= floor(data->ray_var.wall_x);
	data->ray_var.tex_x = (int)(data->ray_var.wall_x
			* (double)data->ray_var.tex_width);
	if ((data->ray_var.side == 0 && data->ray_var.ray_dir_x > 0)
		|| (data->ray_var.side == 1 && data->ray_var.ray_dir_y < 0))
		data->ray_var.tex_x = data->ray_var.tex_width - data->ray_var.tex_x - 1;
}

void	draw_wall(t_data *data, int col)
{
	int	y;

	y = data->ray_var.draw_start;
	while (y < data->ray_var.draw_end)
	{
		data->ray_var.d = y * 256 - SCREEN_HEIGHT * 128
			+ data->ray_var.line_height * 128;
		data->ray_var.tex_y = ((data->ray_var.d * data->ray_var.tex_height)
				/ data->ray_var.line_height) / 256;
		if (data->ray_var.tex_y >= 0
			&& data->ray_var.tex_y < data->ray_var.tex_height
			&& data->ray_var.tex_x >= 0
			&& data->ray_var.tex_x < data->ray_var.tex_width)
		{
			data->ray_var.color = *(int *)(data->ray_var.texture_data
					+ (data->ray_var.tex_y * data->img.line_length
						+ data->ray_var.tex_x * (data->img.bits_per_pixel
							/ 8)));
			draw_pixel(data, data->img.addr, col, y);
		}
		y++;
	}
}
