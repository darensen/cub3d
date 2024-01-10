/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusezett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:42:09 by mudoh             #+#    #+#             */
/*   Updated: 2023/11/24 16:26:04 by lusezett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dst, const char *src, int size)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (src[len])
		len++;
	if (size > 0)
	{
		while (src[i] && size -1 > 0)
		{
			dst[i] = src[i];
			i++;
			size--;
		}
		dst[i] = '\0';
	}
	return (len);
}
