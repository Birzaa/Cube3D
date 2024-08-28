/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:21:41 by thomas            #+#    #+#             */
/*   Updated: 2024/08/28 23:23:15 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_fd(t_data *data)
{
	data->fd = open(data->file, O_RDONLY);
	if (data->fd == -1)
	{
		exit_prog(data, "Can't open the file\n", NULL);
	}
}

void	parse_line(t_data *data, char *line, int i)
{
	if ((!ft_strncmp(line, "NO ", 3) && data->n_path) || (!ft_strncmp(line,
				"EA ", 3) && data->e_path) || (!ft_strncmp(line, "SO ", 3)
			&& data->s_path) || (!ft_strncmp(line, "WE ", 3) && data->o_path))
		exit_prog(data, "Path already registered\n", line);
	else if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "EA ", 3)
		|| !ft_strncmp(line, "SO ", 3) || !ft_strncmp(line, "WE ", 3))
		parsing_texture(data, line);
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		parsing_color(data, line);
	else if (data->e_path && data->n_path && data->o_path && data->s_path
		&& data->parsed == 1 && line[0] != '\0')
	{
		data->in_map = 1;
		parse_map(data, line, i);
	}
	else if (line[0] == '\0' && !data->in_map)
		return ;
	else
		exit_prog(data, "Error parsing\n", line);
	if (data->nb_start > 1)
		exit_prog(data, "Too much starting position\n", line);
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
		exit_prog(data, "Impossible to close FD\n", line);
}

void	create_map(t_data *data)
{
	char	*line;
	int		i;
	int		j;

	j = 0;
	i = 0;
	data->map = malloc(sizeof(char *) * (data->nb_line + 2));
	if (!data->map)
		exit_prog(data, "Error malloc\n", NULL);
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
		exit_prog(data, "Impossible to close FD\n", line);
}

char **cpy_map(char **actual_map, int map_height, int map_width)
{
    char **cpy_map;
    int i;

    // Allouer de la mémoire pour les lignes de la carte copiée
    cpy_map = (char **)malloc(sizeof(char *) * map_height);
    if (cpy_map == NULL)
    {
        perror("Failed to allocate memory for copied map");
        exit(EXIT_FAILURE);
    }

    // Copier chaque ligne de la carte originale
    for (i = 0; i < map_height; i++)
    {
        cpy_map[i] = (char *)malloc(sizeof(char) * (map_width + 1)); // +1 pour le caractère nul de fin
        if (cpy_map[i] == NULL)
        {
            perror("Failed to allocate memory for a line of copied map");
            // Libérer la mémoire allouée jusqu'à présent en cas d'erreur
            while (i > 0)
                free(cpy_map[--i]);
            free(cpy_map);
            exit(EXIT_FAILURE);
        }
        strcpy(cpy_map[i], actual_map[i]);
    }

    return cpy_map;
}

void	parsing(t_data *data)
{
	open_fd(data);
	parsing_map(data);
	open_fd(data);
	create_map(data);
	print_tab(data->map);
	data->map_width = find_longest_line(data->map);
	printf("map height : %d\n", data->map_height);
	printf("map width : %d\n", data->map_width);
	if (ft_parsing_map_leak(data, 0, 0))
		exit_prog(data, "Map is not closed\n", NULL);
	optimizing_map(data);
	if (check_border(data->map))
		exit_prog(data, "Error map\n", NULL);
	get_start_position(data);
}
