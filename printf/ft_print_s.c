/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 13:23:10 by jtrancos          #+#    #+#             */
/*   Updated: 2020/10/08 11:06:30 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	find_string(char **s, int *len, va_list args, t_flags *flags)
{
	char *tmp;

	*s = ft_strdup(va_arg(args, char *));
	if (*s == NULL)
	{
		*s = ft_strdup("(null)");
	}
	if (flags->precision != -1)
	{
		tmp = *s;
		*s = ft_substr(tmp, 0, flags->precision);
		free(tmp);
	}
	*len = ft_strlen(*s);
}

void	ft_print_s(va_list args, t_flags *flags)
{
	char	*s;
	int		len;

	if (flags->precision != -1 && flags->precision < 0)
		flags->precision = -1;
	find_string(&s, &len, args, flags);
	if (flags->width != -1)
	{
		if (flags->minus == 1)
		{
			flags->count += write(1, s, len);
			flags->count += ft_filling(flags->width - len, flags->zero);
		}
		else
		{
			flags->count += ft_filling(flags->width - len, flags->zero);
			flags->count += write(1, s, len);
		}
	}
	else
		flags->count += write(1, s, len);
	free(s);
}
