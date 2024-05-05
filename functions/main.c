/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:09:04 by abougrai          #+#    #+#             */
/*   Updated: 2024/05/05 22:39:41 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	touche(int keycode)
{
	if (keycode == 65307)
		exit(0);
	return (1);
}

void	init_mlx(t_game *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		exit_prog(cub, MLX);
	cub->mlx_win = mlx_new_window(cub->mlx, 640, 640, "cub3d");
	if (!cub->mlx_win)
		exit_prog(cub, MLX);
}

void	images_init(t_game *cub)
{
	cub->NO = mlx_xpm_file_to_image(cub->mlx, "textures/N.xpm", &cub->width, &cub->height); // remplacer les chemins par les chemins dans la map
	cub->SO = mlx_xpm_file_to_image(cub->mlx, "textures/S.xpm", &cub->width, &cub->height);
	cub->WE = mlx_xpm_file_to_image(cub->mlx, "textures/W.xpm", &cub->width, &cub->height);
	cub->EA = mlx_xpm_file_to_image(cub->mlx, "textures/E.xpm", &cub->width, &cub->height);
	if (!(cub->NO || !cub->SO || !cub->WE || !cub->EA))
		exit_prog(cub, IMAGE);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		printf("%s\n", tab[i++]);
}

int	main(int ac, char **av, char **env)
{
	t_game	cub;

	if (ac == 2)
	{
		ft_check_arg(&cub, av[1], ".cub", env);
		init_prog(&cub);
		get_setup_test(&cub, av[1]);
		init_mlx(&cub);
		// print_tab(cub.setup);
		mlx_key_hook(cub.mlx_win, &touche, NULL);
		mlx_loop(cub.mlx);
		exit_prog(&cub, NULL);
	}
	else
		exit_prog(NULL, ARG);
}
