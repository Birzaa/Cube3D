/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 23:09:14 by abougrai          #+#    #+#             */
/*   Updated: 2024/08/28 23:10:42 by abougrai         ###   ########.fr       */
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

ssize_t ft_find_char(char *str, char c)
{
	ssize_t index;

	if (!str)
		return (-1);
	index = 0;
	while (str[index])
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

int ft_contains_char(char *str, char c)
{
	return (ft_find_char(str, c) != -1);
}

int ft_parsing_map_leak(t_data *data, int x, int y)
{
    // Vérifier si la cellule actuelle est '0' ou un des caractères 'NSWE'
    if (data->map[y][x] == '0' || ft_contains_char("NSWE", data->map[y][x]))
    {
        // Vérifier les bords de la carte
        if (x == 0 || x == data->map_width - 1 || y == 0 || y == data->map_height - 1)
        {
            // Erreur : la carte n'est pas entourée de '1'
            return 1;
        }
        // Vérifier les voisins immédiats pour '\0' ou espaces ' '
        if (data->map[y][x + 1] == '\0' || data->map[y][x - 1] == '\0' ||
            data->map[y + 1][x] == '\0' || data->map[y - 1][x] == '\0')
        {
            // Erreur : la carte n'est pas entourée de '1'
            return 1;
        }
        if (data->map[y][x + 1] == ' ' || data->map[y][x - 1] == ' ' ||
            data->map[y + 1][x] == ' ' || data->map[y - 1][x] == ' ')
        {
            // Erreur : la carte n'est pas entourée de '1'
            return 1;
        }
    }

    // Continuer à parcourir la carte
    if (x < data->map_width - 1)
        return ft_parsing_map_leak(data, x + 1, y);
    else if (y < data->map_height - 1)
        return ft_parsing_map_leak(data, 0, y + 1);

    // Si tout est correct et aucune fuite n'a été trouvée
    return 0;
}


