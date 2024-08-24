/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:09:04 by abougrai          #+#    #+#             */
/*   Updated: 2024/08/23 22:05:15 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 2)
	{
		valid_extension(av[1]);
		init(&data, av[1]);
		parsing(&data);
		init_window(&data);
		init_game(&data);
		init_ray(&data);
		render_window(&data);
	}
	else
		exit_prog(NULL, ARG, NULL);
}
