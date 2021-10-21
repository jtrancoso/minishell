/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:44:14 by jtrancos          #+#    #+#             */
/*   Updated: 2021/10/21 11:49:53 by jtrancos         ###   ########.fr       */
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
	if (error == 4)
	{
		split->errorcode = 127;
		ft_putstr_fd("Error. Command not found.\n", 2);
		return(127);
	}
	if (error == 5)
		ft_putstr_fd("Error. No such file or directory.\n", 2);
	if (error == 6)
		ft_putstr_fd("Error. Not a valid identifier.\n", 2);
	if (error == 7)
		ft_putstr_fd("Error. Uneven number of backslashes\n", 2);
	split->errorcode = 1; //FIXME: ESTO ESTA EN TENGUERENGUE
	return (1);
}
