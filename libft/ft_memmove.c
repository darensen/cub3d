/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusezett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:25:34 by mudoh             #+#    #+#             */
/*   Updated: 2023/11/24 16:24:26 by lusezett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned char		*s;
	long unsigned int	i;

	s = (unsigned char *) src;
	d = (unsigned char *) dest;
	i = 0;
	if (!dest && !src)
		return (NULL);
	while (n > 0)
	{
		if (d < s)
		{
			d[i] = s[i];
			i++;
			n--;
		}
		else
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	}
	return (d);
}
