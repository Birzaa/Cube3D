/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 23:09:14 by abougrai          #+#    #+#             */
/*   Updated: 2024/08/27 17:58:08 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	valid_extension(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len >= 5 && ft_strcmp(str + len - 4, ".cub") == 0)
		return ;
	else
	{
		ft_putstr("Error\nInvalid arg\n");
		exit(EXIT_FAILURE);
	}
}

int	check_comma(char *line)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	if (!ft_isdigit(line[i]))
		return (1);
	while (line[i])
	{
		if (line[i] == ',' && line[i + 1] && ft_isdigit(line[i + 1]))
			comma++;
		if (!ft_isdigit(line[i]) && line[i] != ',')
			return (1);
		i++;
	}
	if (comma == 2)
		return (0);
	return (1);
}

int	ft_parsing_map_leak(t_data *data, int x, int y)
{
	if (data->map.content[y][x] == '0' \
		|| ft_contains_char("NSWE", data->map.content[y][x]))
	{
		if (x == 0 || x == data->map.size.x - 1 || y == 0 \
			|| y == data->map.size.y - 1)
			return (ft_exit(data, ERR_MAP, "Map is not surrounded by 1"));
		if (data->map.content[y][x + 1] == '\0'
			|| data->map.content[y][x - 1] == '\0'
			|| data->map.content[y + 1][x] == '\0'
			|| data->map.content[y - 1][x] == '\0')
			return (ft_exit(data, ERR_MAP, "Map is not surrounded by 1"));
		if (data->map.content[y][x + 1] == ' '
			|| data->map.content[y][x - 1] == ' '
			|| data->map.content[y + 1][x] == ' '
			|| data->map.content[y - 1][x] == ' ')
			return (ft_exit(data, ERR_MAP, "Map is not surrounded by 1"));
	}
	if (x < data->map.size.x - 1 && data->map.content[y][x + 1] != '\0')
		return (ft_parsing_map_leak(data, x + 1, y));
	else if (y < data->map.size.y - 1 && data->map.content[y + 1] != NULL)
		return (ft_parsing_map_leak(data, 0, y + 1));
	return (1);
}
