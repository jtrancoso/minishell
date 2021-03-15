/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:22:33 by jtrancos          #+#    #+#             */
/*   Updated: 2021/03/15 13:40:23 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isspace(int c)
{
	int	i;

	i = 0;
	if (c == ' ' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

void	ft_init(t_comm *comm)
{
	comm->echo.flag_n = 0;
}
