/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendu3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsenatus <dsenatus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:31:38 by dsenatus          #+#    #+#             */
/*   Updated: 2024/01/11 19:06:43 by dsenatus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color) // put the pixel
{
    if (x < 0) // check the x position
        return ;
    else if (x >= S_W)
        return ;
    if (y < 0) // check the y position
        return ;
    else if (y >= S_H)
        return ;
    mlx_pixel_put(data->mlx_ptr, data->mlx_win, x, y, color);
    //mlx_put_pixel(data->img_ptr, x, y, color); // put the pixel
}

float nor_angle(float angle) // normalize the angle
{
    if (angle < 0)
        angle += (2 * M_PI);
    if (angle > (2 * M_PI))
        angle -= (2 * M_PI);
    return (angle);
}

void draw_floor_ceiling(t_data *data, int ray, int top_pix, int bot_pix) // draw the floor and the ceiling
{
    int  i;
    int  c;

    i = bot_pix;
    while (i < S_H)
    {
        my_mlx_pixel_put(data, ray, i++, 0xB99470FF); // floor
    }
    i = 0;
    while (i < top_pix)
    {
        my_mlx_pixel_put(data, ray, i++, 0x89CFF3FF); // ceiling
    }
}

int get_color(t_data *data, int flag) // get the color of the wall
{
    data->ray->angle = nor_angle(data->ray->angle); // normalize the angle
    if (flag == 0)
    {
        if (data->ray->angle > M_PI / 2 && data->ray->angle < 3 * (M_PI / 2))
            return (0xB5B5B5FF); // west wall
        else
            return (0xB5B5B5FF); // east wall
    }
    else
    {
        if (data->ray->angle > 0 && data->ray->angle < M_PI)
            return (0xF5F5F5FF); // south wall
        else
            return (0xF5F5F5FF); // north wall
    }
}

void    draw_wall(t_data *data, int ray, int top_pix, int bot_pix) // draw the wall
{
    int color;

    color = get_color(data, data->ray->flag);
    while (top_pix < bot_pix)
    my_mlx_pixel_put(data, ray, top_pix++, color);
}

void    render_wall(t_data *data, int ray) // render the wall
{
    double wall_h;
    double bot_pix;
    double top_pix;

    data->ray->distance *= cos(nor_angle(data->ray->angle - data->player->angle)); // fix the fisheye
    wall_h = (TILE_SIZE / data->ray->distance) * ((S_W / 2) / tan(data->player->fov_rd / 2)); // get the wall height
    bot_pix = (S_H / 2) + (wall_h / 2); // get the bottom pixel
    top_pix = (S_H / 2) - (wall_h / 2); // get the top pixel
    if (bot_pix > S_H) // check the bottom pixel
    bot_pix = S_H;
    if (top_pix < 0) // check the top pixel
    top_pix = 0;
    draw_wall(data, ray, top_pix, bot_pix); // draw the wall
    draw_floor_ceiling(data, ray, top_pix, bot_pix); // draw the floor and the ceiling
}