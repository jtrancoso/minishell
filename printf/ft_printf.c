/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 12:02:12 by jtrancos          #+#    #+#             */
/*   Updated: 2020/10/13 14:27:43 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	check_format(const char *s, int *i, va_list args, t_flags *flags)
{
	if (s[*i] == 'c')
		ft_print_c((char)va_arg(args, int), flags);
	else if (s[*i] == 's')
		ft_print_s(args, flags);
	else if (s[*i] == '%')
		ft_print_c('%', flags);
	else if (s[*i] == 'd' || s[*i] == 'i')
		ft_print_id(args, flags, 0, 0);
	else if (s[*i] == 'x')
		ft_print_x_lower(args, flags);
	else if (s[*i] == 'X')
		ft_print_x_upper(args, flags);
	else if (s[*i] == 'u')
		ft_print_u(args, flags);
	else if (s[*i] == 'p')
		ft_print_p(args, flags);
	else if (!s[*i])
		*i -= 1;
	else if (s[*i + 1] != '\0')
		*i += 1;
}

int		ft_printf(const char *s, ...)
{
	int			i;
	va_list		args;
	t_flags		flags;

	va_start(args, s);
	i = 0;
	flags.count = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			start_flags(&flags);
			check_flags(s, &i, args, &flags);
			check_format(s, &i, args, &flags);
		}
		else
			flags.count += write(1, &s[i], 1);
		i++;
	}
	va_end(args);
	return (flags.count);
}
