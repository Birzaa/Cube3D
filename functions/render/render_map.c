/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:23:17 by thomas            #+#    #+#             */
/*   Updated: 2024/05/08 13:52:17 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(t_data *data, int x, int y)
{
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->e_path, x
		* data->img_width, y * data->img_height);
}

void draw_player(t_data *data, int x, int y) {
    for (int i = 0; i < 36; i++) {
        for (int j = 0; j < 36; j++) {
            mlx_pixel_put(data->mlx, data->mlx_win, (x * data->img_width) + i,
                          (y * data->img_height) + j, 8432);
        }
    }
}


void	draw_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x <= data->map_width)
		{
			if (data->map[y][x] == '1')
				draw_wall(data, x, y);
			else if (data->map[y][x] == 'N')
				draw_player(data, x, y);
			x++;
		}
		y++;
	}
}
