/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_id.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 13:26:41 by jtrancos          #+#    #+#             */
/*   Updated: 2021/03/04 17:49:46 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_print_number(int *n, int num_len, t_flags *flags)
{
	int	i;

	if (*n < 0 && flags->precision > num_len)
	{
		*n = *n * -1;
		flags->count += write(1, "-", 1);
	}
	i = 0;
	while (i < (flags->precision - num_len))
	{
		flags->count += write(1, "0", 1);
		i++;
	}
	ft_putnbr(*n, flags);
}

void	save_lines(t_flags *flags, int n, int len, int true_len)
{
	if (n < 0 && flags->zero == 1)
	{
		n = -n;
		flags->count += write(1, "-", 1);
	}
	if (true_len < flags->width)
		flags->count += ft_filling(flags->width - true_len, flags->zero);
	else
		flags->count += 0;
	ft_print_number(&n, len, flags);
}

void	save_space(t_flags *flags, int n, int len, int true_len)
{
	if (flags->width != -1)
	{
		if (flags->minus == 1)
		{
			ft_print_number(&n, len, flags);
			if (true_len < flags->width)
				flags->count += ft_filling(flags->width - true_len,
						flags->zero);
			else
				flags->count += 0;
		}
		else
			save_lines(flags, n, len, true_len);
	}
	else
		ft_print_number(&n, len, flags);
}

void	ft_print_id(va_list args, t_flags *flags, int n, int len)
{
	int	true_len;

	n = va_arg(args, int);
	len = find_len(&n, flags);
	true_len = find_true_len_id(&n, len, flags);
	save_space(flags, n, len, true_len);
}
