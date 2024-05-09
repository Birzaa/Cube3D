/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:12:22 by abougrai          #+#    #+#             */
/*   Updated: 2024/05/09 14:21:41 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
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
# define M_PI 3.14159265358979323846

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

typedef struct s_raycast
{
	double			posx;
	double			posy;
	char			start;
}					t_ray;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_data
{
	int				rx;
	int				ry;
	int				fd;
	int				nb_start;
	int				map_height;
	int				map_width;
	int				screenx;
	int				screeny;
	char			*file;
	char			**map;
	int				nb_line;
	int				map_start_line;
	void			*mlx;
	void			*mlx_win;
	int				img_width;
	int				img_height;
	void			*n_path;
	void			*e_path;
	void			*s_path;
	void			*o_path;
	t_color			floor;
	t_color			ceiling;
	t_ray			ray;
}					t_data;

// functions/init.c
void				init(t_data *data, char *file);
void				init_window(t_data *data);

// Parsing
void				parsing(t_data *data);
void				valid_extension(char *str);
void				parsing_texture(t_data *data, char *str);
void				parse_map(t_data *data, char *line, int i);
void				get_start_position(t_data *data);

// Render
void				render_window(t_data data);
int					key_pressed(int keycode, t_data *data);
void				draw_map(t_data *data);

//	exit.c
void				exit_prog(t_data *cub, char *error);
int					exit_game(t_data *data);

// functions/tools
void				free_tab(char **tab);

#endif