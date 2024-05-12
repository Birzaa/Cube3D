/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:24:53 by thenwood          #+#    #+#             */
/*   Updated: 2024/05/11 15:16:33 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move(t_data *data, int value)
{
    double newX = data->ray.posx + cos(data->ray.angle) * value;
    double newY = data->ray.posy + sin(data->ray.angle) * value;

    // Vérifier s'il y a une collision avec un mur
    if (data->map[(int)newY][(int)newX] != '1')
    {
        // Si aucune collision n'est détectée, déplacer le joueur
        data->ray.posx = newX;
        data->ray.posy = newY;
    }
}

void	update_angle(t_data *data, double value)
{
	data->ray.angle += value;
	
	// angle reste dans la plage [0, 2*PI]
	if (data->ray.angle >= 2 * M_PI)
		data->ray.angle -= 2 * M_PI;
	else if (data->ray.angle < 0)
		data->ray.angle += 2 * M_PI;
}

int	key_pressed(int keycode, t_data *data)
{
	(void)data;
	if (keycode == 65307)
		exit(0); // FREE TOUUUUUUUUUUUUUUUUT
	else if (keycode == 100 || keycode == 65363)
	{
		update_angle(data, 0.1);
		castRays(data);
	}
	else if (keycode == 97 || keycode == 65361)
	{
		update_angle(data, -0.1);
		castRays(data);
	}
	else if (keycode == 119 || keycode == 65362)
	{
		move(data, 1);
		castRays(data);
	}
	else if (keycode == 115 || keycode == 65364)
	{
		move(data, -1);
		castRays(data);
	}
		
	return (0);
}