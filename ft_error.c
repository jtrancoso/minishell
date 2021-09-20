/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:44:14 by jtrancos          #+#    #+#             */
/*   Updated: 2021/09/20 16:15:10 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(t_split *split, int error)
{
	if (error == 1)
		ft_putstr_fd("Error. Uneven number of quotes\n", 2);
	if (error == 2)
		ft_putstr_fd("Error. Unexpected token ';'\n", 2);
	if (error == 3)
		ft_putstr_fd("Syntax error.\n", 2);
	split->errorcode = 1;
	return (-1);
}
