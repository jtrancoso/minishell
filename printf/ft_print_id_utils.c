/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_id_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 17:35:58 by jtrancos          #+#    #+#             */
/*   Updated: 2021/03/04 17:51:14 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	find_len(int *n, t_flags *flags)
{
	int	aux;
	int	len;

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

int	find_truelen(t_flags *flags, int len)
{
	if (flags->precision > len)
		return (flags->precision);
	else
		return (len);
}

int	find_true_len_id(int *n, int len, t_flags *flags)
{
	int	true_len;

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
