/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:09:04 by abougrai          #+#    #+#             */
/*   Updated: 2024/05/08 14:27:49 by thomas           ###   ########.fr       */
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
		init_raycast(&data.ray);
		init_window(&data);
		render_window(data);
	}
	else
		exit_prog(NULL, ARG);
}
