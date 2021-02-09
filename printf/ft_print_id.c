/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_id.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 13:26:41 by jtrancos          #+#    #+#             */
/*   Updated: 2020/09/25 13:26:07 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		find_len(int *n, t_flags *flags)
{
	int aux;
	int len;

	if (*n == 0 && flags->precision == 0)
		len = 0;
	else
		len = 1;
	aux = *n;
	while (aux / 10 != 0)
	{
		aux = aux / 10;
		len++;
	}
	return (len);
}

int		find_true_len(int *n, int len, t_flags *flags)
{
	int true_len;

	true_len = len;
	if (flags->precision > len)
		true_len = flags->precision;
	if (*n < 0)
		true_len++;
	return (true_len);
}

void	ft_putnbr(int n, t_flags *flags)
{
	char	aux;
	long	num;

	if (n == 0 && flags->precision == 0)
		return ;
	num = n;
	if (num < 0 && flags->zero == -1)
	{
		num = -num;
		flags->count += write(1, "-", 1);
	}
	if (num > 9)
		ft_putnbr(num / 10, flags);
	aux = num % 10 + '0';
	flags->count += write(1, &aux, 1);
}

void	ft_print_number(int *n, int num_len, t_flags *flags)
{
	int i;

	if (*n < 0 && flags->precision > num_len)
	{
		*n = -*n;
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

void	ft_print_id(va_list args, t_flags *flags, int n, int len)
{
	int true_len;

	n = va_arg(args, int);
	len = find_len(&n, flags);
	true_len = find_true_len(&n, len, flags);
	if (flags->width != -1)
		if (flags->minus == 1)
		{
			ft_print_number(&n, len, flags);
			(true_len < flags->width) ? flags->count +=
			ft_filling(flags->width - true_len, flags->zero) : 0;
		}
		else
		{
			if (n < 0 && flags->zero == 1)
			{
				n = -n;
				flags->count += write(1, "-", 1);
			}
			(true_len < flags->width) ? flags->count +=
			ft_filling(flags->width - true_len, flags->zero) : 0;
			ft_print_number(&n, len, flags);
		}
	else
		ft_print_number(&n, len, flags);
}
