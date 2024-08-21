/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougrai <abougrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:24:53 by thenwood          #+#    #+#             */
/*   Updated: 2024/08/21 16:07:43 by abougrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move(t_data *data, int value)
{
    double moveSpeed = 0.04 * value;
    double buffer = 0.1; // Taille du buffer pour empêcher la caméra de rentrer dans le mur
    
    double newX = data->ray.posx + data->ray.dirx * moveSpeed;
    double newY = data->ray.posy + data->ray.diry * moveSpeed;

    // Vérification des collisions avec le mur en prenant en compte la marge de sécurité (buffer)
    if (data->map[(int)(newY + data->ray.diry * buffer)][(int)(newX + data->ray.dirx * buffer)] != '1' &&
        data->map[(int)(newY - data->ray.diry * buffer)][(int)(newX - data->ray.dirx * buffer)] != '1' &&
        data->map[(int)(newY + data->ray.diry * buffer)][(int)(newX - data->ray.dirx * buffer)] != '1' &&
        data->map[(int)(newY - data->ray.diry * buffer)][(int)(newX + data->ray.dirx * buffer)] != '1')
    {
        data->ray.posx = newX;
        data->ray.posy = newY;
    }
}


void update_angle(t_data *data, double value)
{
    data->ray.angle += value;

    // Keep angle within the range [0, 2*PI]
    if (data->ray.angle >= 2 * M_PI)
        data->ray.angle -= 2 * M_PI;
    else if (data->ray.angle < 0)
        data->ray.angle += 2 * M_PI;

    // Update the direction vector based on the new angle
    data->ray.dirx = cos(data->ray.angle);
    data->ray.diry = sin(data->ray.angle);

    // Update the camera plane (perpendicular to the direction vector)
    data->ray.plane_x = -0.66 * sin(data->ray.angle);
    data->ray.plane_y = 0.66 * cos(data->ray.angle);
	// printf("Angle : %f, posx : %f, posy : %f\n", data->ray.angle, data->ray.posx, data->ray.posy);
}


int	key_pressed(int keycode, t_data *data)
{
    if (keycode == KEY_ESC)
        exit_game(data);
    else if (keycode == KEY_D || keycode == KEY_RIGHT)
        data->keys.right = 1;
    else if (keycode == KEY_A || keycode == KEY_LEFT)
        data->keys.left = 1;
    else if (keycode == KEY_W || keycode == KEY_UP)
        data->keys.forward = 1;
    else if (keycode == KEY_S || keycode == KEY_DOWN)
        data->keys.backward = 1;
    return (0);
}

int	key_released(int keycode, t_data *data)
{
    if (keycode == KEY_D || keycode == KEY_RIGHT)
        data->keys.right = 0;
    else if (keycode == KEY_A || keycode == KEY_LEFT)
        data->keys.left = 0;
    else if (keycode == KEY_W || keycode == KEY_UP)
        data->keys.forward = 0;
    else if (keycode == KEY_S || keycode == KEY_DOWN)
        data->keys.backward = 0;
    return (0);
}

void update(t_data *data)
{
    if (data->keys.forward)
        move(data, 1);
    if (data->keys.backward)
        move(data, -1);
    if (data->keys.left)
        update_angle(data, -0.035);
    if (data->keys.right)
        update_angle(data, 0.035);

    castRays(data);
}
