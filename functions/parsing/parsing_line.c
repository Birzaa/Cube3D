/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:18:04 by thomas            #+#    #+#             */
/*   Updated: 2024/05/06 19:05:31 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**valid_color(char *line)
{
	int		i;
	int		j;
	char	**rgb;

	i = 0;
	rgb = ft_split(line, ',');
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			if (!ft_isdigit(rgb[i][j]))
				return (NULL);
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

	rgb = valid_color(line);
	if (!rgb)
	{
		free(line);
		exit_prog(data, "RGB impossible [0, 255]\n");
	}
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
		exit_prog(data, "RGB impossible [0, 255]\n");
	}
}

void	parse_color_floor(t_data *data, char *line)
{
	char	**rgb;
	int		i;

	rgb = valid_color(line);
	if (!rgb)
	{
		free(line);
		exit_prog(data, "RGB impossible [0, 255]\n");
	}
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
		free(line);
		exit_prog(data, "RGB impossible [0, 255]\n");
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
		parse_color_floor(data, line + 2);
	else if (!ft_strncmp(line, "C ", 2))
		parse_color_ceiling(data, line + 2);
}
