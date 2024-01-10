/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusezett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:58:45 by mudoh             #+#    #+#             */
/*   Updated: 2023/11/24 16:24:29 by lusezett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*strtmp;
	int				i;

	strtmp = (unsigned char *) str;
	i = 0;
	while (n > 0)
	{
		strtmp[i] = c;
		i++;
		n--;
	}
	return (strtmp);
}
