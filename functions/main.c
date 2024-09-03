/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:09:04 by abougrai          #+#    #+#             */
/*   Updated: 2024/09/03 16:56:10 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file(t_data *data)
{
	data->fd = open(data->file, __O_DIRECTORY);
	if (data->fd != -1)
	{
		close(data->fd);
		exit_prog(data, "Error file\n", NULL);
	}
}

int	main(int ac, char **av)
{
	(void)av;
	t_data	data;

	if (ac == 2)
	{
		valid_extension(av[1]);
		init(&data, av[1]);
		check_file(&data);
		parsing(&data);
		init_window(&data);
		init_game(&data);
		init_ray(&data);
		render_window(&data);
	}
	else
		exit_prog(NULL, ARG, NULL);
}
