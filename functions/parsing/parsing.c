/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:21:41 by thomas            #+#    #+#             */
/*   Updated: 2024/08/22 21:04:27 by abougrai         ###   ########.fr       */
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
	{
		exit_prog(data, "Path already registered\n", line);
	}
	else if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "EA ", 3)
		|| !ft_strncmp(line, "SO ", 3) || !ft_strncmp(line, "WE ", 3)
		|| !ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
	{
		parsing_texture(data, line);
	}
	else if (data->e_path && data->n_path && data->o_path && data->s_path)
	{
		printf("on a les textures, on peut parser la map\n");
		parse_map(data, line, i);
	}
	else
	{
		return ;
	}
	if (data->nb_start > 1)
		exit_prog(data, "Too much start position\n", line);
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
		printf("line : %s\n", line);
		parse_line(data, line, i);
		free(line);
	}
	if (close(data->fd) < 0)
		exit_prog(data, "Impossible to close FD\n", line);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_putstr(tab[i++]);
		ft_putstr("\n");
	}
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

int	find_longest_line(char **map)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) > len)
			len = ft_strlen(map[i]);
		i++;
	}
	return (len);
}

void	copy_new_map(t_data *data, char **new_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			if (j < (int)ft_strlen(data->map[i]))
			{
				if ((unsigned char)data->map[i][j] != ' ')
					new_map[i][j] = data->map[i][j];
				else
					new_map[i][j] = '1';
			}
			else
				new_map[i][j] = '1';
			j++;
		}
		new_map[i++][j] = '\0';
	}
	new_map[i] = NULL;
}

void	optimizing_map(t_data *data)
{
	int		i;
	char	**new_map;

	i = 0;
	new_map = NULL;
	data->map_width = find_longest_line(data->map);
	new_map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!new_map)
		exit_prog(data, "Malloc failed\n", NULL);
	while (i < data->map_height)
	{
		new_map[i] = malloc(sizeof(char) * (data->map_width + 1));
		if (!new_map[i])
			exit_prog(data, "Malloc failed\n", NULL);
		i++;
	}
	copy_new_map(data, new_map);
	free_tab(data->map);
	data->map = new_map;
	print_tab(data->map);
	printf("nb of lines new map : %d", data->nb_line);
}

void	parsing(t_data *data)
{
	open_fd(data);
	parsing_map(data);
	open_fd(data);
	create_map(data);
	optimizing_map(data);
	get_start_position(data);
}
