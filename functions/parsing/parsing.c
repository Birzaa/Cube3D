/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:21:41 by thomas            #+#    #+#             */
/*   Updated: 2024/05/06 00:58:00 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_fd(t_data *data)
{
	data->fd = open(data->file, O_RDONLY);
	if (data->fd == -1)
	{
		ft_putstr_fd("Can't open the file\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	parse_line(t_data *data, char *line)
{
	if ((!ft_strncmp(line, "NO ", 3) && !data->n_path) || (!ft_strncmp(line,
				"EA ", 3) && !data->e_path) || (!ft_strncmp(line, "SO ", 3)
			&& !data->s_path) || (!ft_strncmp(line, "WE ", 3) && !data->o_path))
			return;
}

void	create_map(t_data *data)
{
	char	*line;

	while (1)
	{
		line = get_next_line(data->fd);
		if (!line)
			break ;
		free(line);
	}
	// CLOSE + erreur
}

void	parsing(t_data *data)
{
	open_fd(data);
	create_map(data);
}