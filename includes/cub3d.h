/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:12:22 by abougrai          #+#    #+#             */
/*   Updated: 2024/05/05 13:59:01 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# define ARG "Invalid argument\n"
# define ACCESS "Impossible acess to arg\n"
# define DIRECTORY "Arg is a directory\n"
# define EXTENSION "Invalid extension\n"
# define ENV "ENV is not set\n"
# define DISPLAY "DISPLAY variable is not set\n"
# define MALLOC "malloc\n"
# define OPEN "Cannot open file\n"
# define MLX "init mlx\n"
# define MAP "Invalid map\n"
# define IMAGE "Init image\n"

typedef struct s_path
{
	char			*texture;
	char			*content;
	struct s_node	*next;

}					t_path;

typedef struct s_game
{
	void			*mlx;
	void			*mlx_win;
	void			*img;
	void			*NO;
	void			*SO;
	void			*WE;
	void			*EA;
	int				width;
	int				height;

	char			**setup;
	char			**map;
	int				fd;
	t_path			*path;
}					t_game;

// functions/init.c
void				ft_check_arg(t_game *cub, char *map, char *exten,
						char **env);
void				init_prog(t_game *cub);

//	exit.c
void				exit_prog(t_game *cub, char *error);

// functions/tools
void				free_tab(char **tab);

// test.c
void				get_setup_test(t_game *cub, char *map);

#endif