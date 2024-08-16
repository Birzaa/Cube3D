/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:16:12 by abougrai          #+#    #+#             */
/*   Updated: 2024/08/16 12:00:53 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_prog(t_data *data)
{
	if (data->n_path)
		mlx_destroy_image(data->mlx, data->n_path);
	if (data->s_path)
		mlx_destroy_image(data->mlx, data->s_path);
	if (data->o_path)
		mlx_destroy_image(data->mlx, data->o_path);
	if (data->e_path)
		mlx_destroy_image(data->mlx, data->e_path);
	if (data->map)
		free_tab(data->map);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
}

int	exit_game(t_data *data)
{
	if (data->n_path)
		mlx_destroy_image(data->mlx, data->n_path);
	if (data->s_path)
		mlx_destroy_image(data->mlx, data->s_path);
	if (data->o_path)
		mlx_destroy_image(data->mlx, data->o_path);
	if (data->e_path)
		mlx_destroy_image(data->mlx, data->e_path);
	if (data->map)
		free_tab(data->map);
	mlx_destroy_image(data->mlx, data->mlx_img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

void	exit_prog(t_data *data, char *error)
{
	if (error)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(error, 2);
	}
	if (data)
	{
		free_prog(data);
	}
	if (error)
		exit(1);
	exit(0);
}
