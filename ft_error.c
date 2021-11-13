/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:44:14 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/13 08:00:57 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error2(t_split *split, char *line, int error)
{
	if (error == 7)
	{
		ft_putstr_fd("galactic: error. Uneven number of backslashes\n", 2);
		return (-1);
	}
	if (error == 8)
		ft_putstr_fd("galactic: error. HOME not set\n", 2);
	return (1);
}

int	ft_error(t_split *split, char *line, int error)
{
	if (error == 1)
		ft_putstr_fd("galactic: error. Uneven number of quotes\n", 2);
	if (error == 2)
		ft_putstr_fd("galactic: error. Unexpected token ';'\n", 2);
	if (error == 3)
		ft_putstr_fd("galactic: syntax error.\n", 2);
	if (error == 4)
	{
		split->errorcode = 127;
		printf("galactic: %s: command not found.\n", line);
		return (127);
	}
	if (error == 5)
		ft_putstr_fd("galactic: error. No such file or directory.\n", 2);
	if (error == 6)
	{
		split->ret = 1;
		ft_putstr_fd("galactic: error. Not a valid identifier.\n", 2);
	}
	if (error == 7 || error == 8)
		ft_error2(split, line, error);
	split->errorcode = 1; //FIXME: ESTO ESTA EN TENGUERENGUE
	return (1);
}
