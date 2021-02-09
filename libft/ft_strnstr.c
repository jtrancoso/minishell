/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:27:33 by jtrancos          #+#    #+#             */
/*   Updated: 2020/01/13 14:35:57 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*str;
	size_t	i;
	size_t	k;

	str = (char *)haystack;
	i = 0;
	if (needle[0] == '\0')
		return (str);
	if (len == 0)
		return (NULL);
	while (str[i] != '\0' && i < len)
	{
		k = 0;
		while (str[i + k] == needle[k] && haystack[i + k] != '\0' &&
				i + k < len)
		{
			if (needle[k + 1] == '\0')
				return (&str[i]);
			k++;
		}
		i++;
	}
	return (0);
}
