/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 13:04:23 by jtrancos          #+#    #+#             */
/*   Updated: 2020/09/29 11:01:45 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	space_or_zero(const char *s, int *i, t_flags *flags)
{
	while (s[*i] == '-' || s[*i] == '0')
	{
		if (s[*i] == '-')
		{
			flags->minus = 1;
			flags->zero = -1;
		}
		if (s[*i] == '0' && flags->minus == -1)
			flags->zero = 1;
		*i += 1;
	}
}

void	check_width(const char *s, int *i, va_list args, t_flags *flags)
{
	if (s[*i] >= '0' && s[*i] <= '9')
	{
		flags->width = ft_atoi(&s[*i]);
		while (s[*i] >= '0' && s[*i] <= '9')
			*i += 1;
	}
}

void	check_star(const char *s, int *i, va_list args, t_flags *flags)
{
	if (s[*i] == '*')
	{
		flags->width = va_arg(args, int);
		if (flags->width < 0)
		{
			flags->width = -flags->width;
			flags->zero = -1;
			flags->minus = 1;
		}
		*i += 1;
	}
}

void	check_point(const char *s, int *i, va_list args, t_flags *flags)
{
	if (s[*i] == '.')
	{
		flags->precision = 0;
		flags->zero = -1;
		*i += 1;
		if (s[*i] == '*')
		{
			flags->precision = va_arg(args, int);
			*i += 1;
		}
		else
		{
			flags->precision = ft_atoi(&s[*i]);
			while (s[*i] >= '0' && s[*i] <= '9')
				*i += 1;
		}
	}
}

void	check_flags(const char *s, int *i, va_list args, t_flags *flags)
{
	space_or_zero(s, i, flags);
	check_star(s, i, args, flags);
	check_width(s, i, args, flags);
	check_point(s, i, args, flags);
}
