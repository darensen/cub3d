/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusezett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:07:13 by lusezett          #+#    #+#             */
/*   Updated: 2023/12/19 19:33:30 by lusezett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int checkextension(char *s)
{
	if (s[ft_strlen(s) - 1] == 'b' && s[ft_strlen(s) - 2] == 'u'
		&& s[ft_strlen(s) - 3] == 'c' && s[ft_strlen(s) - 4] == '.')
		return (0);
	else
		return (print_error("Error\nWrong file extension\n"));
}

static int	isclosed_2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]) == 0)
			i++;
		while (is_charset(str[i], "1") == 0)
			i++;
		if (str[i] && str[i] != '\n')
			return (print_error("Error\nMap is not closed\n"), 1);
		if (str[i] == '\n' && !str[i + 1])
			return (0);
	}
	return (0);
}

static int	isclosed(char **map)
{
	int		i;
	char	*str;
	int		j;

	j = 1;
	while (map[j])
	{	
		str = map[j];
		i = 0;
		while (ft_isspace(str[i]) == 0)
			i++;
		if ((str[i] != '1') || (str[strlen(str) - 2] != '1'))
			return (print_error("Error\nMap is not closed\n"));
		j++;
	}
	if (isclosed_2(map[j - 1]) == 1 || isclosed_2(map[0]) == 1)
		return (1);
	return (0);
}

static int check_spaces(char **map)
{
	int		i;
	int		j;
	char	*str;

	j = 0;	
	while (map[j])
	{
		str = map[j];
		i = 0;
		while (str[i])
		{
			if (str[i] == ' ')
			{
				if (str[i - 1] != '1')
					return (print_error("Error\nBad map\n"));
				while (str[i] && str[i] == ' ')
					i++;
				if (str[i] != '1' || !str[i])
					return (print_error("Error\nBad map\n"));
			}
			i++;
		}
		j++;
	}
	return (0);
}

static int	check_chars(char **map)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	while (map[j])
	{
		str = map[j];
		i = 0;
		while (str[i])
		{
			if (is_charset(str[i], "01NSEW\n ") == 1 && str[i] != '\0')
				return (print_error("Error\nBad map\n"));
			i++;
		}
		j++;
	}
	return (0);
}

int	check_map(t_data *data)
{
    data->map = create_map(data->av, 0);
    if (isclosed(data->map) == 0 && check_chars(data->map) == 0 && check_spaces(data->map) == 0)
        return (0);
	return (1);
}
