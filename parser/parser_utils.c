/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:22:33 by jtrancos          #+#    #+#             */
/*   Updated: 2021/03/04 17:53:29 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_isspace(int c)
{
	int i;

	i = 0;
	if (c == 32 || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

void	ft_init(t_comm *comm)
{
	comm->echo.flag_n = 0;
}