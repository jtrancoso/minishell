/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 13:19:20 by jtrancos          #+#    #+#             */
/*   Updated: 2020/10/15 12:06:45 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "./libft/libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

typedef struct	s_flags
{
	int		minus;
	int		zero;
	int		precision;
	int		width;
	int		count;
}				t_flags;

int				ft_printf(const char *s, ...);
void			ft_print_c(int c, t_flags *flags);
void			ft_print_s(va_list args, t_flags *flags);
void			ft_print_id(va_list args, t_flags *flags, int n, int len);
void			ft_print_x_lower(va_list args, t_flags *flags);
void			ft_print_x_upper(va_list args, t_flags *flags);
void			put_hex(size_t n, char lettercase, t_flags *flags);
int				find_hex_len(unsigned int *n, t_flags *flags);
void			ft_print_hexnum_lower(unsigned int *n, int hex_len,
				t_flags *flags);
void			ft_print_hexnum_upper(unsigned int *n, int hex_len,
				t_flags *flags);
void			ft_print_u(va_list args, t_flags *flags);
void			ft_print_p(va_list args, t_flags *flags);
void			check_flags(const char *s, int *i, va_list args,
				t_flags *flags);
int				ft_filling(int width, int zero);
void			start_flags(t_flags *flags);

#endif
