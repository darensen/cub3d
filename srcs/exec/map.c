/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusezett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:25:25 by lusezett          #+#    #+#             */
/*   Updated: 2023/12/22 20:32:04 by lusezett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
    
void draw_large_pixel(void *mlx_ptr, void *win_ptr, int x, int y, int size, int color)
{
    int half_size = size / 2;
    int i, j;

    for (i = -half_size; i < half_size; i++)
    {
        for (j = -half_size; j < half_size; j++)
        {
            mlx_pixel_put(mlx_ptr, win_ptr, x + i, y + j, color);
        }
    }
}

void draw_pixel(t_data *data) 
{
    draw_large_pixel(data->mlx_ptr, data->mlx_win, data->playerx, data->playery, 26,0xFF0000);
}

void clear_pixel(t_data *data) 
{
    draw_large_pixel(data->mlx_ptr, data->mlx_win, data->playerx, data->playery, 26,0x000000);
}

void draw_map2D(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (y < data->mapy)
    {
        x = 0;
        while (x < data->mapx)
        {
            if (data->map[y][x] == '1')
                draw_large_pixel(data->mlx_ptr, data->mlx_win, (x * 32) + 16, (y * 32) + 16, 26, 0x00FF00);
            else if (is_charset(data->map[y][x], "0") == 0)
                draw_large_pixel(data->mlx_ptr, data->mlx_win, (x * 32) + 16, (y * 32) + 16, 26, 0xFFFFFF);
            x++;
        }
        y++;
    }
}
