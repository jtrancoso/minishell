/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:48:13 by jtrancos          #+#    #+#             */
/*   Updated: 2020/01/26 15:39:38 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	q;

	q = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s + i) == q)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
