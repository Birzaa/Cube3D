/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 22:20:51 by thomas            #+#    #+#             */
/*   Updated: 2024/08/21 22:41:59 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_pixel(t_data *data, char *img_data, int x, int y)
{
	char	*dst;

	dst = img_data + (y * data->ray_var.size_line + x * (data->ray_var.bpp
				/ 8));
	*(unsigned int *)dst = data->ray_var.color;
}

void	create_img(t_data *data)
{
	data->img.img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->ray_var.bpp,
			&data->ray_var.size_line, &data->ray_var.endian);
	data->ray_var.floor_color = create_trgb(0, data->floor.r, data->floor.g,
			data->floor.b);
	data->ray_var.ceiling_color = create_trgb(0, data->ceiling.r,
			data->ceiling.g, data->ceiling.b);
}
