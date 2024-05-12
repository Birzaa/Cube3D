/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:45:47 by thomas            #+#    #+#             */
/*   Updated: 2024/05/12 22:26:46 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_impact_ray(t_data *data, int hitX, int hitY)
{
    // (rouge)
    int color = 0xFF8438; 
	for(int i = 0; i < 64; i++)
    	{
        // mlx_pixel_put(data->mlx, data->mlx_win, hitX, hitY+i, color);
		mlx_pixel_put(data->mlx, data->mlx_win, hitX+i, hitY, color);
		// mlx_pixel_put(data->mlx, data->mlx_win, hitX+i, hitY + 64, color);
		// mlx_pixel_put(data->mlx, data->mlx_win, hitX+64, hitY + i, color);
        
        }
}

void castRays(t_data *data)
{
    mlx_clear_window(data->mlx, data->mlx_win);
    // Angle de vision du joueur
    double startAngle = data->ray.angle - M_PI / 6; // Angle de départ
    double endAngle = data->ray.angle + M_PI / 6;   // Angle de fin
    double angleIncrement = (endAngle - startAngle) / SCREEN_WIDTH; // Incrément d'angle par colonne

    // Parcourir chaque colonne de pixels sur l'écran
    for (int col = 0; col < SCREEN_WIDTH; col++)
    {
        // Angle correspondant à cette colonne
        double rayAngle = startAngle + col * angleIncrement;
    
        // Coordonnées du point d'impact initialisées à la position du joueur
        double hitX = data->ray.posx, hitY = data->ray.posy;
        
        // Avancez le rayon jusqu'à ce qu'il atteigne un mur
        while (data->map[(int)hitY][(int)hitX] != '1')
        {
            // Déplacement du rayon en fonction de son angle
            hitX += cos(rayAngle);
            hitY += sin(rayAngle);
        }
        // Calculer la distance entre le joueur et le mur pour déterminer la hauteur du mur
        double distance = sqrt((hitX - data->ray.posx) * (hitX - data->ray.posx) + (hitY - data->ray.posy) * (hitY - data->ray.posy));
        double wallHeight = SCREEN_HEIGHT / distance; // Plus la distance est courte, plus le mur est grand

        // Ajuster la hauteur du mur en fonction de l'angle de vue
        double angleDifference = fabs(data->ray.angle - rayAngle);
        wallHeight *= cos(angleDifference); // Appliquer la correction de la perspective

        // Dessinez
        int wallStart = (SCREEN_HEIGHT - wallHeight) / 2;
        int wallEnd = wallStart + wallHeight;
        for (int row = wallStart; row < wallEnd; row++)
        {
            mlx_pixel_put(data->mlx, data->mlx_win, col, row, 0xFF8438);
        }
    }
}


