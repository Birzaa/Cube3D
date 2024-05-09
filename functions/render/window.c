/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 21:02:59 by thomas            #+#    #+#             */
/*   Updated: 2024/05/09 23:05:53 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	render_window(t_data data)
{
	mlx_hook(data.mlx_win, 17, 0, &exit_game, &data);
	mlx_key_hook(data.mlx_win, &key_pressed, &data); // Movements non fonctionnels
	draw_map(&data); // Visualiser map 2D
	mlx_loop(data.mlx);
}
