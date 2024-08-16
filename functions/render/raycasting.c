/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:45:47 by thomas            #+#    #+#             */
/*   Updated: 2024/08/16 12:07:32 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}
void draw_pixel(char *img_data, int x, int y, int color, int size_line, int bpp)
{
    char *dst;

    // Calculer la position du pixel dans l'image en utilisant la formule décrite
    dst = img_data + (y * size_line + x * (bpp / 8));
    
    // Appliquer la couleur au pixel
    *(unsigned int*)dst = color;
}

void castRays(t_data *data)
{
    int bpp, size_line, endian;
    
    // Création de l'image qui couvrira tout l'écran
    data->img.img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    data->img.addr = mlx_get_data_addr(data->img.img, &bpp, &size_line, &endian);

    int floor_color = create_trgb(0, data->floor.r, data->floor.g, data->floor.b);
    int ceiling_color = create_trgb(0, data->ceiling.r, data->ceiling.g, data->ceiling.b);

    // Dessin du plafond
    for (int y = 0; y < SCREEN_HEIGHT / 2; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            draw_pixel(data->img.addr, x, y, ceiling_color, size_line, bpp);
        }
    }

    // Dessin du sol
    for (int y = SCREEN_HEIGHT / 2; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            draw_pixel(data->img.addr, x, y, floor_color, size_line, bpp);
        }
    }

    // Raycasting pour dessiner les murs
    for (int col = 0; col < SCREEN_WIDTH; col++)
    {
        double cameraX = 2 * col / (double)SCREEN_WIDTH - 1;
        double rayDirX = data->ray.dirx + data->ray.plane_x * cameraX;
        double rayDirY = data->ray.diry + data->ray.plane_y * cameraX;

        int mapX = (int)data->ray.posx;
        int mapY = (int)data->ray.posy;

        double sideDistX;
        double sideDistY;

        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;
        int hit = 0;
        int side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (data->ray.posx - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - data->ray.posx) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (data->ray.posy - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - data->ray.posy) * deltaDistY;
        }

        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (data->map[mapY][mapX] == '1') hit = 1;
        }

        if (side == 0) perpWallDist = (mapX - data->ray.posx + (1 - stepX) / 2) / rayDirX;
        else           perpWallDist = (mapY - data->ray.posy + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

        void *texture;
        if (side == 1)
        {
            if (rayDirY > 0)
                texture = data->e_path;
            else
                texture = data->o_path;
        }
        else
        {
            if (rayDirX > 0)
                texture = data->s_path;
            else
                texture = data->n_path;
        }

        char *texture_data = mlx_get_data_addr(texture, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
        int tex_width = data->img_width;
        int tex_height = data->img_height;

        double wallX;
        if (side == 0) wallX = data->ray.posy + perpWallDist * rayDirY;
        else wallX = data->ray.posx + perpWallDist * rayDirX;
        wallX -= floor(wallX);

        int texX = (int)(wallX * (double)tex_width);
        if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0)) {
            texX = tex_width - texX - 1;
        }

        for (int y = drawStart; y < drawEnd; y++)
        {
            int d = y * 256 - SCREEN_HEIGHT * 128 + lineHeight * 128;
            int texY = ((d * tex_height) / lineHeight) / 256;

            if (texY >= 0 && texY < tex_height && texX >= 0 && texX < tex_width) {
                int color = *(int *)(texture_data + (texY * data->img.line_length + texX * (data->img.bits_per_pixel / 8)));
                draw_pixel(data->img.addr, col, y, color, size_line, bpp);
            }
        }
    }
    
    // Afficher l'image sur l'écran
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
    mlx_destroy_image(data->mlx, data->img.img);
}
