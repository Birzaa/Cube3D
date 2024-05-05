/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:16:12 by abougrai          #+#    #+#             */
/*   Updated: 2024/05/05 13:53:18 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_prog(t_game *cub)
{
	if (cub->NO)
		mlx_destroy_image(cub->mlx, cub->NO);
	if (cub->SO)
		mlx_destroy_image(cub->mlx, cub->SO);
	if (cub->WE)
		mlx_destroy_image(cub->mlx, cub->WE);
	if (cub->EA)
		mlx_destroy_image(cub->mlx, cub->EA);
	if (cub->setup)
		free_tab(cub->setup);
	if (cub->mlx_win)
	{
		mlx_destroy_window(cub->mlx, cub->mlx_win);
		mlx_destroy_display(cub->mlx);
	}
	if (cub->mlx)
		free(cub->mlx);
}

void exit_prog(t_game *cub, char *error)
{
	if (error)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(error, 2);
	}
	if (cub)
		free_prog(cub);
	if (error)
		exit(1);
	exit(0);
}
