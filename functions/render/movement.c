/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:24:53 by thenwood          #+#    #+#             */
/*   Updated: 2024/05/07 20:49:22 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	left_right(t_data *data, int value)
{
	if (data->map[data->player.y][data->player.x += value] != '1')
	{
		data->player.x += value;
		castRays(data);
	}
}

void	up_down(t_data *data, int value)
{
	if (data->map[data->player.y += value][data->player.x] != '1')
	{
		data->player.y += value;
		castRays(data);
	}
}

int	key_pressed(int keycode, t_data *data)
{
	(void)data;
	if (keycode == 65307)
		exit(0); // FREE TOUUUUUUUUUUUUUUUUT
	else if (keycode == 119 || keycode == 65362)
	{
		up_down(data, -1);
	}
	else if (keycode == 100 || keycode == 65363)
	{
		left_right(data, 1);
	}
	else if (keycode == 97 || keycode == 65361)
	{
		left_right(data, -1);
	}
	else if (keycode == 115 || keycode == 65364)
	{
		up_down(data, 1);
	}
	return (0);
}