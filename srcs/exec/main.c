/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsenatus <dsenatus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:40:56 by lusezett          #+#    #+#             */
/*   Updated: 2024/01/10 18:51:49 by dsenatus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_tab(char **tab)
{
	int		idx;

	idx = 0;
	if (!tab)
		return ;
	while (tab[idx] != NULL)
	{
		free(tab[idx]);
		idx++;
	}
	free (tab);
}

void	ft_free_all(t_data *data)
{
	ft_free_tab(data->map);
	free(data->av);
}

int	handle_no_event(void *data)
{
	char	*i;

	i = data;
	i++;
	return (0);
}

int	clear_all(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	mlx_clear_window(data->mlx_ptr, data->mlx_win);
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	mlx_destroy_display(data->mlx_ptr);
	mlx_loop_end(data->mlx_ptr);
	free(data->mlx_ptr);
	ft_free_all(data);
	exit(0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape || keysym == 113)
		clear_all(data);
	clear_pixel(data);
	if (keysym == XK_w)
		data->playery--;
	else if (keysym == XK_s)
		data->playery++;
	else if (keysym == XK_a)
		data->playerx--;
	else if (keysym == XK_d)
		data->playerx++;
	draw_map2D(data);
	draw_pixel(data);
	return (0);
}

void init_ray(t_ray *ray, t_data *data)
{
	double		inter_v;
	double		inter_h;
	int			ray;

	ray = 0;
	ray->ray_angle = player->angle - (player->fov_rd / 2); // angle de depart
	while (ray < S_W)
	{
		ray->flag = 0;
		inter_h = 
		inter_v = 
		if (inter_v < inter_h)
			ray->distance = inter_v;
		else
		{ 
			ray->distance = inter_h;
			ray->flag = 1;
		}
		ray++;
		ray_angle += 
		
		
	}  
	
}

void	find_xy(t_data *data)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	while(data->map[j])
	{
		i = 0;
		str = data->map[j];
		while (str[i])
		{
			if (is_charset(str[i], "NSEW") == 0)
			{
				data->playerx = (i * 32) + 16;
				data->playery = (j * 32) + 16;
				return ;	
			}
			i++;
		}
		j++;
	}
}

void init_the_player(t_data *data, t_player *player) // init the player structure
{
	player->x = data->playerx * TILE_SIZE + TILE_SIZE / 2; // player x position in pixels in the center of the tile
	player->y = data->playery * TILE_SIZE + TILE_SIZE / 2; // player y position in pixels in the center of the tile
	player->fov_rd = (FOV * M_PI) / 180; // field of view in radians
	player->angle = M_PI; // player angle
	//the rest of the variables are initialized to zero by calloc
}

void    init(t_data *data, t_ray *ray)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return ;
	find_xy(data);
	cast_ray(ray, data);
	data->mapx = ft_strlen(data->map[0]);
	data->mapy = map_size(data->av);
	data->mapt = data->mapx * data->mapy;
	data->img_ptr = mlx_new_image(data->mlx_ptr, data->mapx * 32, data->mapy * 32);
	data->mlx_win = mlx_new_window(data->mlx_ptr, data->mapx * 32,
			data->mapy * 32, "cub3d");
	if (data->mlx_win == NULL)
		return ;
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_loop_hook(data->mlx_ptr, &handle_no_event, data);
	mlx_hook(data->mlx_win, 17, 0, &clear_all, data);
	draw_map2D(data);
    mlx_loop(data->mlx_ptr);
}

int main(int ac, char **av)
{
    t_data data;
	t_ray ray;

	if (ac != 2)
		return (print_error("Error in arguments\n"));
	if (checkextension(av[1]) == 1)
		return (1);
	data.av = ft_strdup(av[1]);
	if (ac != 2 || check_map(&data) == 1)
		return (ft_free_all(&data), 1);
	ft_free_tab(data.map);
	data.map = create_map(av[1], 1);
    init(&data, &ray);
    return (0);
}
