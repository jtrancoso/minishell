/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 19:07:08 by jtrancos          #+#    #+#             */
/*   Updated: 2020/01/22 20:49:14 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		n_len(long n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	if (n == 0)
	{
		len++;
		return (len);
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nbr;

	nbr = n;
	i = n_len(n);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (nbr < 0)
		nbr = -nbr;
	while (i >= 0)
	{
		str[i] = 48 + (nbr % 10);
		nbr = nbr / 10;
		i--;
	}
	if (str[0] == '0' && str[1])
		str[0] = '-';
	return (str);
}
