/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusezett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:33:28 by lusezett          #+#    #+#             */
/*   Updated: 2023/12/19 18:08:41 by lusezett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_size(char *s)
{
	char	*str;
	int		i;
	int		fd;

	i = 0;
	fd = open(s, O_RDWR);
	if (fd == -1)
		return (0);
	str = get_next_line(fd);
	while (str)
	{
		free (str);
		i++;
		str = get_next_line(fd);
	}
	if (str)
		free(str);
	close(fd);
	return (i);
}

static char	*ft_strdup2(const char *s)
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	str = malloc(ft_strlen(s) + 1 * sizeof(char));
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (ft_isspace(s[i]) == 0)
			str[i] = '1';
		else
			str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}


char	**create_map(char *s, int n)
{
	char	**map;
	char	*str;
	int		i;
	int		fd;

	i = 0;
	fd = open(s, O_RDWR);
	if (fd == -1)
		return (NULL);
	map = malloc(sizeof(char *) * (map_size(s) + 1));
	if (!map)
		return (NULL);
	str = get_next_line(fd);
	while (str)
	{
		if (n == 0)
			map[i++] = ft_strdup(str);
		else if (n == 1)
			map[i++] = ft_strdup2(str);
		if (str)
			free(str);
		str = get_next_line(fd);
	}
	map[i] = NULL;
	if (str)
		free(str);
	close(fd);
	return (map);
}
