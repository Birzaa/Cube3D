/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizing_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:16:33 by abougrai          #+#    #+#             */
/*   Updated: 2024/08/24 19:45:34 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_border(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i][j])
	{
		if (map[i][j] != '1')
			return (1);
		j++;
	}
	while (map[i + 1])
		i++;
	j = 0;
	while (map[i][j])
	{
		if (map[i][j] != '1')
			return (1);
		j++;
	}
	return (0);
}

int	check_pos(char **map)
{
	int	i;
	int	j;
	int	start;

	start = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E')
				start++;
			j++;
		}
		i++;
	}
	if (start > 1 || start == 0)
		return (1);
	return (0);
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
				if ((unsigned char)data->map[i][j] != ' '
					|| (unsigned char)data->map[i][j] != '\t')
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
	if (check_border(data->map) || check_pos(data->map))
		exit_prog(data, "Error map\n", NULL);
	printf("nb of lines new map : %d", data->nb_line);
}
