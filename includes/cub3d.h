/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsenatus <dsenatus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:51:19 by lusezett          #+#    #+#             */
/*   Updated: 2024/01/12 17:29:38 by dsenatus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "libft.h"
# define FOV 60
# define mapWidth 24
# define mapHeight 24
# define S_W 640
# define S_H 480
# define TILE_SIZE 10

typedef struct s_img
{
    void	*mlx_img;
    char	*addr;
    int		bpp; /* bits per pixel */
    int		line_len;
    int		endian;
}	t_img;

typedef struct s_player
{
    int         x;
    int         y;
    double      angle;
    float       fov_rd;
} t_player;

typedef struct s_ray
{
    double      angle;
    double      distance;	
    int         flag;		
    
} t_ray;

typedef struct s_data
{
    void        *mlx_ptr;
    void        *mlx_win;
	void        *img_ptr;
	t_img       img;

    char        *av;
    char        **map;
	int		    mapx;
	int		    mapy;
	int		    mapt;

    int         playerx;
    int         playery;
    int         posx;
    int         posy;
    int         x_max;
    int         y_max;
    t_player    *player;
    t_ray       *ray;
}              t_data;

enum	e_fd
{
	STDIN,
	STDOUT,
	STDERR,
	gnl_loop
};

//MAP 2D
void	draw_map2D(t_data *data);
void draw_pixel(t_data *data);
void clear_pixel(t_data *data);

//PARSING
int     check_map(t_data *data);
int     checkextension(char *s);

//UTILS
char	**create_map(char *s, int n);
void	ft_print_map(char **map);
int     print_error(char *str);
int     is_charset(char c, char *set);
void	ft_print_map(char **map);
int     map_size(char *s);

void    render_wall(t_data *data, int ray);

#endif