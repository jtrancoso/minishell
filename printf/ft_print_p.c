/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 13:08:43 by jtrancos          #+#    #+#             */
/*   Updated: 2020/10/14 13:11:29 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_ptr_len(size_t *address, t_flags *flags)
{
	int		len;
	size_t	aux;

	aux = *address;
	if (flags->precision == 0 && *address == 0)
		len = 0;
	else
		len = 1;
	while (aux / 16 != 0)
	{
		len++;
		aux /= 16;
	}
	return (len);
}

void	ft_print_ptr(size_t *address, int len, t_flags *flags)
{
	int i;

	i = 0;
	flags->count += write(1, "0x", 2);
	while (i < (flags->precision - len))
	{
		flags->count += write(1, "0", 1);
		i++;
	}
	put_hex(*address, 'l', flags);
}

void	ft_print_p(va_list args, t_flags *flags)
{
	void	*ptr;
	size_t	address;
	int		len;
	int		truelen;

	ptr = va_arg(args, void *);
	address = (size_t)ptr;
	len = ft_ptr_len(&address, flags);
	truelen = (flags->precision > len) ? flags->precision : len;
	if (flags->width != -1)
	{
		if (flags->minus == 1)
		{
			ft_print_ptr(&address, len, flags);
			flags->count += ft_filling(flags->width - truelen - 2, flags->zero);
		}
		else
		{
			flags->count += ft_filling(flags->width - truelen - 2, flags->zero);
			ft_print_ptr(&address, len, flags);
		}
	}
	else
		ft_print_ptr(&address, len, flags);
}
