/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 09:58:57 by jtrancos          #+#    #+#             */
/*   Updated: 2020/09/30 13:27:59 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		unsigned_len(unsigned int *n, t_flags *flags)
{
	int len;
	int aux;

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

void	ft_putunsigned(unsigned int n, t_flags *flags)
{
	char	aux;

	if (n == 0 && flags->precision == 0)
		return ;
	if (n > 9)
		ft_putunsigned(n / 10, flags);
	aux = n % 10 + '0';
	flags->count += write(1, &aux, 1);
}

void	ft_print_unsigned(unsigned int *n, int num_len, t_flags *flags)
{
	int i;

	i = 0;
	while (i < (flags->precision - num_len))
	{
		flags->count += write(1, "0", 1);
		i++;
	}
	ft_putunsigned(*n, flags);
}

void	ft_print_u(va_list args, t_flags *flags)
{
	unsigned int	n;
	int				len;
	int				true_len;

	n = va_arg(args, unsigned int);
	len = unsigned_len(&n, flags);
	true_len = (flags->precision > len) ? flags->precision : len;
	if (flags->width != -1)
	{
		if (flags->minus == 1)
		{
			ft_print_unsigned(&n, len, flags);
			flags->count += ft_filling(flags->width - true_len, flags->zero);
		}
		else
		{
			flags->count += ft_filling(flags->width - true_len, flags->zero);
			ft_print_unsigned(&n, len, flags);
		}
	}
	else
		ft_print_unsigned(&n, len, flags);
}
