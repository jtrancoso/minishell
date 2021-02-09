/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 13:59:13 by jtrancos          #+#    #+#             */
/*   Updated: 2020/01/26 16:10:27 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int counter;
	unsigned int result;

	if (!dst && !src)
		return (0);
	result = 0;
	while (src[result] != '\0')
		result++;
	counter = 0;
	if (dstsize == 0)
	{
		return (result);
	}
	while (src[counter] != '\0' && counter < (dstsize - 1))
	{
		dst[counter] = src[counter];
		counter++;
	}
	dst[counter] = '\0';
	return (result);
}
