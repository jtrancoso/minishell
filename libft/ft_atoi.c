/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:31:44 by jtrancos          #+#    #+#             */
/*   Updated: 2020/01/22 22:20:33 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		neg;
	long	num;

	num = 0;
	neg = 1;
	while (*str == ' ' || *str == '\n' || *str == '\r' ||
				*str == '\t' || *str == '\v' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = neg * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = (10 * num) + (*str - '0');
		str++;
		if ((neg * num) > 2147483647)
			return (-1);
		else if ((neg * num) < -2147483648)
			return (0);
	}
	return (num * neg);
}
