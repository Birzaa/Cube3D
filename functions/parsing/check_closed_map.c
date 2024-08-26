/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closed_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:39:16 by abougrai          #+#    #+#             */
/*   Updated: 2024/08/26 18:45:37 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_closed_map(data)
{
	
}
typedef struct
{
	char	**map;
	int		rows;
	int		cols;
	bool	**visited;
}			Map;

bool	is_inside(int x, int y, Map *map)
{
	return (x >= 0 && x < map->rows && y >= 0 && y < map->cols);
}

void	explore(Map *map, int x, int y)
{
	int	newX;
	int	newY;
	int	directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

	map->visited[x][y] = true;
	for (int i = 0; i < 4; i++)
	{
		newX = x + directions[i][0];
		newY = y + directions[i][1];
		if (is_inside(newX, newY, map) && map->map[newX][newY] == '0'
			&& !map->visited[newX][newY])
		{
			explore(map, newX, newY);
		}
	}
}

bool	is_map_closed(Map *map)
{
	map->visited = (bool **)malloc(map->rows * sizeof(bool *));
	for (int i = 0; i < map->rows; i++)
	{
		map->visited[i] = (bool *)calloc(map->cols, sizeof(bool));
	}

	int startX = -1, startY = -1;
	for (int i = 0; i < map->rows && startX == -1; i++)
	{
		for (int j = 0; j < map->cols && startY == -1; j++)
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'E'
				|| map->map[i][j] == 'S' || map->map[i][j] == 'W')
			{
				startX = i;
				startY = j;
			}
		}
	}

	explore(map, startX, startY);

	bool closed = true;
	for (int i = 0; i < map->rows; i++)
	{
		for (int j = 0; j < map->cols; j++)
		{
			if (map->map[i][j] == '0' && !map->visited[i][j])
			{
				closed = false;
				break ;
			}
		}
	}

	for (int i = 0; i < map->rows; i++)
	{
		free(map->visited[i]);
	}
	free(map->visited);

	return (closed);
}