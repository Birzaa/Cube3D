/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 21:02:59 by thomas            #+#    #+#             */
/*   Updated: 2024/08/21 21:22:34 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main_loop(t_data *data)
{
	update(data);
	return (0);
}

void	render_window(t_data *data)
{
	mlx_hook(data->mlx_win, 17, 0, exit_game, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_pressed, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, key_released, data);
	mlx_loop_hook(data->mlx, main_loop, data);
	mlx_loop(data->mlx);
}
