/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:18:52 by thomas            #+#    #+#             */
/*   Updated: 2024/08/21 22:30:24 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	distance_wall(t_data *data)
{
	if (data->ray_var.rayDirX < 0)
	{
		data->ray_var.stepX = -1;
		data->ray_var.sideDistX = (data->ray.posx - data->ray_var.mapX)
			* data->ray_var.deltaDistX;
	}
	else
	{
		data->ray_var.stepX = 1;
		data->ray_var.sideDistX = (data->ray_var.mapX + 1.0 - data->ray.posx)
			* data->ray_var.deltaDistX;
	}
	if (data->ray_var.rayDirY < 0)
	{
		data->ray_var.stepY = -1;
		data->ray_var.sideDistY = (data->ray.posy - data->ray_var.mapY)
			* data->ray_var.deltaDistY;
	}
	else
	{
		data->ray_var.stepY = 1;
		data->ray_var.sideDistY = (data->ray_var.mapY + 1.0 - data->ray.posy)
			* data->ray_var.deltaDistY;
	}
}

void	hit_wall(t_data *data)
{
	while (data->ray_var.hit == 0)
	{
		if (data->ray_var.sideDistX < data->ray_var.sideDistY)
		{
			data->ray_var.sideDistX += data->ray_var.deltaDistX;
			data->ray_var.mapX += data->ray_var.stepX;
			data->ray_var.side = 0;
		}
		else
		{
			data->ray_var.sideDistY += data->ray_var.deltaDistY;
			data->ray_var.mapY += data->ray_var.stepY;
			data->ray_var.side = 1;
		}
		if (data->map[data->ray_var.mapY][data->ray_var.mapX] == '1')
			data->ray_var.hit = 1;
	}
	if (data->ray_var.side == 0)
		data->ray_var.perpWallDist = (data->ray_var.mapX - data->ray.posx + (1
					- data->ray_var.stepX) / 2) / data->ray_var.rayDirX;
	else
		data->ray_var.perpWallDist = (data->ray_var.mapY - data->ray.posy + (1
					- data->ray_var.stepY) / 2) / data->ray_var.rayDirY;
}

void	get_value_draw_wall(t_data *data)
{
	data->ray_var.lineHeight = (int)(SCREEN_HEIGHT
			/ data->ray_var.perpWallDist);
	data->ray_var.drawStart = (data->ray_var.lineHeight * -1) / 2
		+ SCREEN_HEIGHT / 2;
	if (data->ray_var.drawStart < 0)
		data->ray_var.drawStart = 0;
	data->ray_var.drawEnd = data->ray_var.lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (data->ray_var.drawEnd >= SCREEN_HEIGHT)
		data->ray_var.drawEnd = SCREEN_HEIGHT - 1;
	if (data->ray_var.side == 1)
	{
		if (data->ray_var.rayDirY > 0)
			data->ray_var.texture = data->e_path;
		else
			data->ray_var.texture = data->o_path;
	}
	else
	{
		if (data->ray_var.rayDirX > 0)
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
		data->ray_var.wallX = data->ray.posy + data->ray_var.perpWallDist
			* data->ray_var.rayDirY;
	else
		data->ray_var.wallX = data->ray.posx + data->ray_var.perpWallDist
			* data->ray_var.rayDirX;
	data->ray_var.wallX -= floor(data->ray_var.wallX);
	data->ray_var.texX = (int)(data->ray_var.wallX
			* (double)data->ray_var.tex_width);
	if ((data->ray_var.side == 0 && data->ray_var.rayDirX > 0)
		|| (data->ray_var.side == 1 && data->ray_var.rayDirY < 0))
		data->ray_var.texX = data->ray_var.tex_width - data->ray_var.texX - 1;
}

void	draw_wall(t_data *data, int col)
{
	int	y;

	y = data->ray_var.drawStart;
	while (y < data->ray_var.drawEnd)
	{
		data->ray_var.d = y * 256 - SCREEN_HEIGHT * 128
			+ data->ray_var.lineHeight * 128;
		data->ray_var.texY = ((data->ray_var.d * data->ray_var.tex_height)
				/ data->ray_var.lineHeight) / 256;
		if (data->ray_var.texY >= 0
			&& data->ray_var.texY < data->ray_var.tex_height
			&& data->ray_var.texX >= 0
			&& data->ray_var.texX < data->ray_var.tex_width)
		{
			data->ray_var.color = *(int *)(data->ray_var.texture_data
					+ (data->ray_var.texY * data->img.line_length
						+ data->ray_var.texX * (data->img.bits_per_pixel / 8)));
			draw_pixel(data, data->img.addr, col, y);
		}
		y++;
	}
}
