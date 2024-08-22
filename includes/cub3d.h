/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:12:22 by abougrai          #+#    #+#             */
/*   Updated: 2024/08/22 18:10:37 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include "game.h"
# include <fcntl.h>
# include <limits.h>
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
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_ESC 65307

typedef struct s_raycast
{
	double posx; // position joueur
	double	posy;
	double	plane_x;
	double	plane_y;
	double	angle;
	double dirx; // direction du rayon
	double	diry;
	char direction; // N E S O
}			t_ray;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_img
{
	void *img;          // Pointeur vers l'image
	char *addr;         // Adresse de l'image en mémoire
	int bits_per_pixel; // Nombre de bits par pixel
	int line_length;    // Longueur d'une ligne en octets
	int endian;         // Endianness de l'image (petit ou grand boutiste)
}			t_img;

typedef struct s_keys
{
    int forward;    // Pour la touche 'W' ou flèche haut
    int backward;   // Pour la touche 'S' ou flèche bas
    int left;       // Pour la touche 'A' ou flèche gauche
    int right;      // Pour la touche 'D' ou flèche droite
} t_keys;

typedef struct s_ray_var
{
	int	bpp;
	int	size_line;
	int	endian;
	int	floor_color;
	int	ceiling_color;
	int	x;
	int	y;
	double cameraX;
	double rayDirX;
	double rayDirY;
	int mapX;
	int mapY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int stepX;
	int stepY;
	int hit;
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;
	void *texture;
	char *texture_data;
	int tex_width;
	int tex_height;
	double wallX;
	int texX;
	int d;
	int texY;
	int color;
} t_ray_var;


typedef struct s_data
{
	int		map_x;
	int		map_y;
	int		fd;
	double	dir_x;
	double	dir_y;
	void	*mlx_img;
	void	*img_add;
	void	*img_no_add;
	int		img_bpp;
	int		img_len;
	int		img_endian;
	int		img_no_bpp;
	int		img_no_len;
	int		img_no_endian;
	int		nb_start;
	int		map_height;
	int		map_width;
	char	*file;
	char	**map;
	int		nb_line;
	int		map_start_line;
	void	*mlx;
	void	*mlx_win;
	int		img_width;
	int		img_height;
	void	*n_path;
	void	*e_path;
	void	*s_path;
	void	*o_path;

	t_color	floor;
	t_color	ceiling;
	t_ray	ray;
	t_img	img;
	t_keys keys;      // Structure pour l'état des touches
	t_ray_var	ray_var;
}			t_data;

// functions/init.c
void		init(t_data *data, char *file);
void		init_window(t_data *data);
void		init_game(t_data *data);
void		init_ray(t_data *data);

// Parsing
void		parsing(t_data *data);
void		valid_extension(char *str);
void		parsing_texture(t_data *data, char *str);
void		parse_map(t_data *data, char *line, int i);
void		get_start_position(t_data *data);
void		empty_gnl(t_data *data, char *line);


// Render
void		render_window(t_data *data);
int			key_pressed(int keycode, t_data *data);
void		draw_map(t_data *data);

// Raycasting
void		init_render(t_data *data);
void	distance_wall(t_data *data);
void	hit_wall(t_data *data);
void	get_value_draw_wall(t_data *data);
void	texture_wall_position_side(t_data *data);
void	draw_wall(t_data *data, int col);
int	create_trgb(int t, int r, int g, int b);
void	draw_pixel(t_data *data,char *img_data, int x, int y);
void	create_img(t_data *data);
void	draw_ceiling(t_data *data);
void	draw_floor(t_data *data);
void	get_value_ray(t_data *data, int col);
void	raycast(t_data *data);
int	create_trgb(int t, int r, int g, int b);
void	create_img(t_data *data);


//	exit.c
void		exit_prog(t_data *cub, char *error);
int			exit_game(t_data *data);

// functions/tools
void		free_tab(char **tab);

// Movements
int	key_released(int keycode, t_data *data);
void update(t_data *data);

#endif