/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:15:14 by thomas            #+#    #+#             */
/*   Updated: 2024/05/06 22:58:56 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	castRays(t_data *data)
{
	int	ray;
	int	testX;
	int	testY;

	ray = 0;
	testX = 0;
	testY = 0;
	while (ray < data->map_width)
	{
		data->ray.rayAngle = data->player.angle - 30.0 + (ray * 60.0
				/ data->map_width);
		data->ray.posX = data->player.x;
		data->ray.posY = data->player.y;
		data->ray.dirX = cos(data->ray.rayAngle * M_PI / 180);
		data->ray.dirY = sin(data->ray.rayAngle * M_PI / 180);
		data->ray.distance = 0.0;
		data->ray.hitWall = false;
		while (!data->ray.hitWall && data->ray.distance < data->map_width)
		{
			testX = (int)(data->ray.posX + data->ray.dirX * data->ray.distance);
			testY = (int)(data->ray.posY + data->ray.dirY * data->ray.distance);
			// Vérifiez si testX et testY sont dans les limites du tableau de carte
			if (testX >= 0 && testX < data->map_width && testY >= 0
				&& testY < data->map_height)
			{
				if (data->map[testY][testX] == '1')
					data->ray.hitWall = true;
			}
			else
			{
				// Sortir de la boucle si les coordonnées sortent des limites de la carte
				break ;
			}
			data->ray.distance += 0.1;
		}
		if (data->ray.hitWall)
		{
			mlx_put_image_to_window(data->mlx, data->mlx_win, data->e_path,
				testX * data->img_width, testY * data->img_height);
		}
		ray++;
	}
}
