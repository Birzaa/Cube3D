/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:18:04 by thomas            #+#    #+#             */
/*   Updated: 2024/08/22 21:06:49 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_color(char c, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		printf("%c\n", line[i]);
		if (!ft_isdigit(line[i]) && line[i] != c && line[i] != ' ' && line[i] != ',')
			return (1);
		i++;
	}
	return (0);
}
char	**valid_color(t_data *data, char *line)
{
	
	int		i;
	int		j;
	char	**rgb;

	i = 0;
	rgb = ft_split(line, ',');
	if (!rgb)
		exit_prog(data, "Error malloc\n", line);
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			if (!ft_isdigit(rgb[i][j]))
				return (free_tab(rgb), (NULL));
			j++;
		}
		i++;
	}
	return (rgb);
}

void	parse_color_ceiling(t_data *data, char *line)
{
	char	**rgb;
	int		i;

	if (check_color('C', line))
		exit_prog(data, "Error RGB", line);
	rgb = valid_color(data, line + 2);
	if (!rgb)
		exit_prog(data, "RGB impossible [0, 255]\n", line);
	i = 0;
	while (rgb[i])
		i++;
	data->ceiling.r = ft_atoi(rgb[0]);
	data->ceiling.g = ft_atoi(rgb[1]);
	data->ceiling.b = ft_atoi(rgb[2]);
	free_tab(rgb);
	if (i > 3 || data->ceiling.r > 255 || data->ceiling.g > 255
		|| data->ceiling.b > 255 || data->ceiling.r < 0 || data->ceiling.g < 0
		|| data->ceiling.b < 0)
	{
		exit_prog(data, "RGB impossible [0, 255]\n", line);
	}
}

void	parse_color_floor(t_data *data, char *line)
{
	char	**rgb;
	int		i;

	if (check_color('F', line))
		exit_prog(data, "Error RGB", line);
	rgb = valid_color(data, line + 2);
	if (!rgb)
		exit_prog(data, "RGB impossible [0, 255]\n", NULL);
	i = 0;
	while (rgb[i])
		i++;
	data->floor.r = ft_atoi(rgb[0]);
	data->floor.g = ft_atoi(rgb[1]);
	data->floor.b = ft_atoi(rgb[2]);
	free_tab(rgb);
	if (i > 3 || i < 3 || data->floor.r > 255 || data->floor.g > 255
		|| data->floor.b > 255 || data->floor.r < 0 || data->floor.g < 0
		|| data->floor.b < 0)
	{
		exit_prog(data, "RGB impossible [0, 255]\n", line);
	}
}

void	empty_gnl(t_data *data, char *line)
{
	char	*empty;

	empty = "";
	free(line);
	while (1)
	{
		empty = get_next_line(data->fd);
		if (!empty)
			break ;
		free(empty);
	}
}

void	parsing_texture(t_data *data, char *line)
{
	char	*path;

	path = ft_strchr(line, '.');
	if (!ft_strncmp(line, "NO ", 3))
		data->n_path = mlx_xpm_file_to_image(data->mlx, path, &data->img_width,
				&data->img_height);
	else if (!ft_strncmp(line, "EA ", 3))
		data->e_path = mlx_xpm_file_to_image(data->mlx, path, &data->img_width,
				&data->img_height);
	else if (!ft_strncmp(line, "SO ", 3))
		data->s_path = mlx_xpm_file_to_image(data->mlx, path, &data->img_width,
				&data->img_height);
	else if (!ft_strncmp(line, "WE ", 3))
		data->o_path = mlx_xpm_file_to_image(data->mlx, path, &data->img_width,
				&data->img_height);
	else if (!ft_strncmp(line, "F ", 2))
	{
		parse_color_floor(data, line);
	}
	else if (!ft_strncmp(line, "C ", 2))
		parse_color_ceiling(data, line);
}
