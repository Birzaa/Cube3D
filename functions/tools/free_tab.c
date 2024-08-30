/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 02:56:06 by abougrai          #+#    #+#             */
/*   Updated: 2024/08/30 13:04:42 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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

ssize_t	ft_find_char(char *str, char c)
{
	ssize_t	index;

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

int	ft_contains_char(char *str, char c)
{
	return (ft_find_char(str, c) != -1);
}
