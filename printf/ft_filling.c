/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filling.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 12:46:13 by jtrancos          #+#    #+#             */
/*   Updated: 2021/03/04 12:44:05 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_filling(int width, int zero)
{
	int	i;

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
