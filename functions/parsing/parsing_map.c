/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:33:57 by thomas            #+#    #+#             */
/*   Updated: 2024/08/25 15:28:06 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_space(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

void	parse_map(t_data *data, char *line, int j)
{
	int	i;

	i = 0;
	line = skip_space(line);
	data->nb_line++;
	if (!*line)
		return ;
	if (!data->map_start_line)
		data->map_start_line = j;
	/* if (line[0] != '1' || line[ft_strlen(line) - 1] != '1')
		exit_prog(data, "Invalid border\n", line); */
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
			data->nb_start++;
		else if (line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ')
			exit_prog(data, "Impossible value\n", line);
		i++;
	}
}

void	get_start_position(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
			{
				data->ray.direction = data->map[i][j];
				data->ray.posx = j + 0.5;
				data->ray.posy = i + 0.5;
			}
			j++;
		}
		i++;
	}
}
