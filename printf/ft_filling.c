/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filling.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 12:46:13 by jtrancos          #+#    #+#             */
/*   Updated: 2020/10/13 14:05:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_filling(int width, int zero)
{
	int i;

	i = 0;
	if (zero == -1)
	{
		while (i < width)
		{
			write(1, " ", 1);
			i++;
		}
	}
	else
	{
		while (i < width)
		{
			write(1, "0", 1);
			i++;
		}
	}
	return (i);
}
