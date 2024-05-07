/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:24:53 by thenwood          #+#    #+#             */
/*   Updated: 2024/05/07 17:10:39 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void key(t_data *data, int value, bool horizontal)
{
	if (data->map[data->player.y][data->player.x] == 'N')
		data->map[data->player.y][data->player.x] = '0';
	if (data->map[data->player.y - 1][data->player.x] != '1')
	{
		if(!horizontal)
			data->player.y+= value;
		else
			data->player.x+= value;
		castRays(data);
	}
}

int	key_pressed(int keycode, t_data *data)
{
	(void)data;
	if (keycode == 65307)
		exit(0); //FREE TOUUUUUUUUUUUUUUUUT
	else if (keycode == 119 || keycode == 65362)
	{
		key(data, -1, false);
	}
	else if (keycode == 100 || keycode == 65363)
	{
		key(data, 1, true);
	}
	else if (keycode == 97 || keycode == 65361)
	{
		key(data, -1, true);
	}
	else if (keycode == 115 || keycode == 65364)
	{
		key(data, 1, false);
	}
	return (0);
}