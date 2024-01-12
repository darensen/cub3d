/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendu3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsenatus <dsenatus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:31:38 by dsenatus          #+#    #+#             */
/*   Updated: 2024/01/12 16:37:24 by dsenatus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color) 
{
    if (x < 0) 
        return ;
    else if (x >= S_W)
        return ;
    if (y < 0) 
        return ;
    else if (y >= S_H)
        return ;
    mlx_pixel_put(data->mlx_ptr, data->mlx_win, x, y, color);
}

float nor_angle(float angle) 
{
    if (angle < 0)
        angle += (2 * M_PI);
    if (angle > (2 * M_PI))
        angle -= (2 * M_PI);
    return (angle);
}

void draw_floor_ceiling(t_data *data, int ray, int top_pix, int bot_pix) 
{
    int  i;
    int  c;

    i = bot_pix;
    while (i < S_H)
    {
        my_mlx_pixel_put(data, ray, i++, 0xB99470FF); 
    }
    i = 0;
    while (i < top_pix)
    {
        my_mlx_pixel_put(data, ray, i++, 0x89CFF3FF); 
    }
}

int get_color(t_data *data, int flag) 
{
    data->ray->angle = nor_angle(data->ray->angle); 
    if (flag == 0)
    {
        if (data->ray->angle > M_PI / 2 && data->ray->angle < 3 * (M_PI / 2))
            return (0xB5B5B5FF); 
        else
            return (0xB5B5B5FF); 
    }
    else
    {
        if (data->ray->angle > 0 && data->ray->angle < M_PI)
            return (0xF5F5F5FF); 
        else
            return (0xF5F5F5FF); 
    }
}

void    draw_wall(t_data *data, int ray, int top_pix, int bot_pix) 
{
    int color;

    color = get_color(data, data->ray->flag);
    while (top_pix < bot_pix)
    my_mlx_pixel_put(data, ray, top_pix++, color);
}

void    render_wall(t_data *data, int ray) 
{
    double wall_h;
    double bot_pix;
    double top_pix;

    data->ray->distance *= cos(nor_angle(data->ray->angle - data->player->angle)); 
    wall_h = (TILE_SIZE / data->ray->distance) * ((S_W / 2) / tan(data->player->fov_rd / 2)); 
    bot_pix = (S_H / 2) + (wall_h / 2); 
    top_pix = (S_H / 2) - (wall_h / 2); 
    if (bot_pix > S_H) 
    bot_pix = S_H;
    if (top_pix < 0) 
    top_pix = 0;
    draw_wall(data, ray, top_pix, bot_pix); 
    draw_floor_ceiling(data, ray, top_pix, bot_pix); 
}