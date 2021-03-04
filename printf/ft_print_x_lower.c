/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x_lower.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 11:16:40 by jtrancos          #+#    #+#             */
/*   Updated: 2021/03/04 12:51:49 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_print_hexnum_lower(unsigned int *n, int hex_len, t_flags *flags)
{
	int	i;

	i = 0;
	while (i < (flags->precision - hex_len))
	{
		flags->count += write(1, "0", 1);
		i++;
	}
	put_hex(*n, 'l', flags);
}

void	ft_print_x_lower(va_list args, t_flags *flags)
{
	unsigned int	n;
	int				hex_len;
	int				true_len;

	n = va_arg(args, unsigned int);
	hex_len = find_hex_len(&n, flags);
	if (flags->precision > hex_len)
		true_len = flags->precision;
	else
		true_len = hex_len;
	if (flags->width > true_len)
	{
		if (flags->minus == 1)
		{
			ft_print_hexnum_lower(&n, hex_len, flags);
			flags->count += ft_filling(flags->width - true_len, flags->zero);
		}
		else
		{
			flags->count += ft_filling(flags->width - true_len, flags->zero);
			ft_print_hexnum_lower(&n, hex_len, flags);
		}
	}
	else
		ft_print_hexnum_lower(&n, hex_len, flags);
}
