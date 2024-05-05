/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 23:09:14 by abougrai          #+#    #+#             */
/*   Updated: 2024/05/05 12:32:05 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_display(char **env, char *display)
{
	int	i;

	i = 0;
	if (!*env)
		exit_prog(NULL, ENV);
	while (env[i])
	{
		if (!ft_strncmp(env[i], display, ft_strlen(display)))
			return ;
		i++;
	}
	exit_prog(NULL, DISPLAY);
}

void	check_extension(char *arg, char *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arg[i])
	{
		j = 0;
		while (arg[i + j] == map[j])
		{
			if (map[j + 1] == '\0' && j + 1 == (int)ft_strlen(map))
				return ;
			j++;
		}
		i++;
	}
	exit_prog(NULL, EXTENSION);
}

void	access_arg(t_game *cub, char *arg)
{
	if (access(arg, R_OK))
		exit_prog(NULL, ACCESS);
	cub->fd = open(arg, __O_DIRECTORY);
	if (cub->fd != -1)
	{
		close(cub->fd);
		exit_prog(NULL, DIRECTORY);
	}
	return ;
}

void	ft_check_arg(t_game *cub, char *map, char *exten, char **env)
{
	if (!*env)
	{
		printf("test\n");
	}
	access_arg(cub, map);
	check_extension(map, exten);
	check_display(env, "DISPLAY");
}
