/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:40:56 by lusezett          #+#    #+#             */
/*   Updated: 2024/01/17 21:55:55 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_tab(char **tab)
{
	int		i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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
	if (keysym == XK_w)
	{
		data->player->x = roundf((cos(data->player->angle) * MOVE_SPEED) + data->player->x);
  		data->player->y = roundf((sin(data->player->angle) * MOVE_SPEED) + data->player->y);
	}
	else if (keysym == XK_s)
	{
		data->player->x = roundf((-cos(data->player->angle) * MOVE_SPEED) + data->player->x);
  		data->player->y = roundf((-sin(data->player->angle) * MOVE_SPEED) + data->player->y);
	}
	else if (keysym == XK_a)
	{
		data->player->x -= roundf(cos(data->player->angle + M_PI / 2) * MOVE_SPEED);
  		data->player->y -= roundf(sin(data->player->angle + M_PI / 2) * MOVE_SPEED);
	}
	else if (keysym == XK_d)
	{
		data->player->x = roundf((cos(data->player->angle + M_PI / 2 ) * MOVE_SPEED) + data->player->x);
  		data->player->y = roundf((sin(data->player->angle +  M_PI / 2 ) * MOVE_SPEED) + data->player->y);
	}
	if (keysym == XK_Left)
	{
  		data->player->angle -= ROTATION_SPEED;
		//if (data->player->angle < 0)
   		//	data->player->angle += 2 * M_PI;
	}
	else if (keysym == XK_Right)
	{
    	data->player->angle += ROTATION_SPEED;
		//if (data->player->angle > 2 * M_PI)
   		//	data->player->angle -= 2 * M_PI;
	}
	
	cast_ray(data);
	return (0);
}

void	get_pos(t_data *data, char **str)
{
	int	x;
	int	y;

	y = 0;
	while (str[y])
	{
		x = 0;
		while (str[y][x])
		{
			if (str[y][x] == 'N' || str[y][x] == 'S' || str[y][x] == 'E' || str[y][x] == 'W')
			{
				data->posy = y;
				data->posx = x;
			}
			x++;
		}
		y++;
	}
	data->x_max = x;
	data->y_max = y;
}


int unit_circle(float angle, char c) 
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
		return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
		return (1);
	}
 return (0);
}

int inter_check(float angle, float *inter, float *step, int is_horizon) 
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
	*step *= -1;
	}
	else
	{
	if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2)) 
	{
		*inter += TILE_SIZE;
		return (-1);
	}
	*step *= -1;
 }
 return (1);
}

int wall_hit(float x, float y, t_data *data) 
{
	int  x_m;
	int  y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE); 
	y_m = floor (y / TILE_SIZE);
	if ((y_m >= data->mapy || x_m >= data->mapx))
		return (0);
	if (data->map[y_m] && x_m <= ft_strlen(data->map[y_m]))
	{
		if (data->map[y_m][x_m] == '1')
			return (0);
	}
	return(1);
}

float	get_h_inter(t_data *data, float angle)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angle);
	h_y = floor(data->player->y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &h_y, &y_step, 1);
	h_x = data->player->x + (h_y - data->player->y) / tan(angle);
	if ((unit_circle(angle, 'y') && x_step > 0) || (!unit_circle(angle, 'y') && x_step < 0)) // check x_step value
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, data))
	{
		h_x += x_step;
		h_y += y_step;
	}
	return (sqrt(pow(h_x - data->player->x, 2) + pow(h_y - data->player->y, 2)));
}

float get_v_inter(t_data *data, float angle)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE; 
	y_step = TILE_SIZE * tan(angle);
	v_x = floor(data->player->x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &v_x, &x_step, 0); 
	v_y = data->player->y + (v_x - data->player->x) * tan(angle);
	if ((unit_circle(angle, 'x') && y_step < 0) || (!unit_circle(angle, 'x') && y_step > 0)) 
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, data)) 
	{
		v_x += x_step;
		v_y += y_step;
	}
	return (sqrt(pow(v_x - data->player->x, 2) + pow(v_y - data->player->y, 2)));
}

void cast_ray(t_data *data)
{
	double		inter_v;
	double		inter_h;
	int			ray;

	ray = 0;
	data->ray->angle = data->player->angle - (data->player->fov_rd / 2);
	while (ray < S_W)
	{
		data->ray->flag = 0;
		inter_h = get_v_inter(data, data->ray->angle); 
		inter_v = get_h_inter(data, data->ray->angle);
		if (inter_v < inter_h)
			data->ray->distance = inter_v;
		else
		{ 
			data->ray->distance = inter_h;
			data->ray->flag = 1;
		}
		render_wall(data, ray);
		ray++;
		data->ray->angle += (data->player->fov_rd / S_W);
		printf("Initial player x: %d\n", data->player->x);
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
				data->posx = i;
				data->posy = j;
				return ;	
			}
			i++;
		}
		j++;
	}
}

void init_the_player(t_data *data)
{
	data->player->x = data->posx * TILE_SIZE + TILE_SIZE / 2;
	data->player->y = data->posy * TILE_SIZE + TILE_SIZE / 2; 
	data->player->fov_rd = (FOV * M_PI) / 180; 
	data->player->angle = M_PI;
	data->ray->distance = 0;
	data->ray->angle = 0;
	data->ray->flag = 0;

}

void    init(t_data *data, t_ray *ray)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return ;
	data->mapx = ft_strlen(data->map[0]);
	data->mapy = map_size(data->av);
	data->mapt = data->mapx * data->mapy;
	data->mlx_win = mlx_new_window(data->mlx_ptr, S_W, S_H, "cub3d");
	data->img_ptr = mlx_new_image(data->mlx_ptr, S_W, S_H); // create new image
	find_xy(data);
	init_the_player(data);
	if (data->mlx_win == NULL)
		return ;
	mlx_hook(data->mlx_win, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_loop_hook(data->mlx_ptr, &handle_no_event, data);
	mlx_hook(data->mlx_win, 17, 0, &clear_all, data);
	cast_ray(data);
    mlx_loop(data->mlx_ptr);
}

int main(int ac, char **av)
{
    t_data data;
	t_ray ray;

	data.player = ft_calloc(1, sizeof(t_player)); 
 	data.ray = ft_calloc(1, sizeof(t_ray));
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
