/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:21:41 by thomas            #+#    #+#             */
/*   Updated: 2024/05/06 21:00:16 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_fd(t_data *data)
{
	data->fd = open(data->file, O_RDONLY);
	if (data->fd == -1)
	{
		exit_prog(data, "Can't open the file\n");
	}
}

void	parse_line(t_data *data, char *line, int i)
{
	if ((!ft_strncmp(line, "NO ", 3) && data->n_path) || (!ft_strncmp(line,
				"EA ", 3) && data->e_path) || (!ft_strncmp(line, "SO ", 3)
			&& data->s_path) || (!ft_strncmp(line, "WE ", 3) && data->o_path))
	{
		free(line);
		exit_prog(data, "Path already registered\n");
	}
	if (!ft_strncmp(line, "NO ", 3))
		parsing_texture(data, line);
	else if (!ft_strncmp(line, "EA ", 3))
		parsing_texture(data, line);
	else if (!ft_strncmp(line, "SO ", 3))
		parsing_texture(data, line);
	else if (!ft_strncmp(line, "WE ", 3))
		parsing_texture(data, line);
	else if (!ft_strncmp(line, "F ", 2))
		parsing_texture(data, line);
	else if (!ft_strncmp(line, "C ", 2))
		parsing_texture(data, line);
	else
		parse_map(data, line, i);
	if (data->nb_start > 1)
		(free(line), exit_prog(data, "Too much start position\n"));
}

void	parsing_map(t_data *data)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(data->fd);
		i++;
		if (!line)
			break ;
		parse_line(data, line, i);
		free(line);
	}
	if (close(data->fd) < 0)
		exit_prog(data, "Impossible to close FD\n");
}

void	create_map(t_data *data)
{
	char	*line;
	int		i;
	int		j;

	j = 0;
	i = 0;
	data->map = malloc(sizeof(char *) * (data->nb_line + 1));
	if (!data->map)
		exit(1); // MODIF
	while (1)
	{
		line = get_next_line(data->fd);
		j++;
		if (!line)
			break ;
		if (j >= data->map_start_line)
			data->map[i++] = ft_strdup(line);
		free(line);
	}
	data->map[i] = NULL;
	data->map_height = i;
	data->map_width = ft_strlen(data->map[0]) - 1;
	if (close(data->fd) < 0)
		exit_prog(data, "Impossible to close FD\n");
}

void	parsing(t_data *data)
{
	open_fd(data);
	parsing_map(data);
	open_fd(data);
	create_map(data);
	get_start_position(data);
}