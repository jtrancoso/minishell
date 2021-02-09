/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 14:06:37 by jtrancos          #+#    #+#             */
/*   Updated: 2020/01/26 18:30:09 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_size;
	size_t	src_size;
	size_t	i;
	size_t	j;

	if (!dst && !src)
		return (0);
	dst_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	if (dstsize == 0)
		return (src_size);
	if (dstsize < dst_size)
		return (src_size + dstsize);
	j = 0;
	i = dst_size;
	while (i < dstsize - 1 && src[j] != '\0')
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (src_size + dst_size);
}
