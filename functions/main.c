/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:09:04 by abougrai          #+#    #+#             */
/*   Updated: 2024/08/22 17:58:48 by abougrai         ###   ########.fr       */
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
		if (!data.e_path || !data.n_path || !data.o_path || !data.s_path)
		{
			ft_printf("%d\n", data.nb_line);
			exit_prog(&data, "capart\n");
		}
		init_window(&data);
		init_game(&data);
		init_ray(&data);
		render_window(&data);
	}
	else
		exit_prog(NULL, ARG);
}
