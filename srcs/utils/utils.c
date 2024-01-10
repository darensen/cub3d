/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusezett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:09:14 by lusezett          #+#    #+#             */
/*   Updated: 2023/12/19 20:03:14 by lusezett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_charset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (0);
		i++;
	}
	return (1);
}

int	print_error(char *str)
{
	int	ret;

	ret = write(STDERR, str, ft_strlen(str));
	(void)ret;
	return (1);
}

void	ft_print_map(char **map)
{
	int i = 0;

	printf("\n\n");
	while(map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
	printf("\n\n");
}
