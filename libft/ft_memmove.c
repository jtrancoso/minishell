/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:27:56 by jtrancos          #+#    #+#             */
/*   Updated: 2020/01/26 14:56:17 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*dst2;
	const char	*src2;

	dst2 = dst;
	src2 = src;
	i = 0;
	if (dst == src)
		return (dst);
	if (!dst2 && !src2)
		return (NULL);
	if (dst2 < src2)
	{
		while (i < len)
		{
			dst2[i] = src2[i];
			i++;
		}
	}
	else
		while (len-- > 0)
			dst2[len] = src2[len];
	return (dst);
}
