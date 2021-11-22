/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:44:14 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/22 12:03:08 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_error_syntax(t_split *split, char c)
{
	if (!c)
		printf("galactic: syntax error near unexpected token 'newline'\n");
	else
		printf("galactic: syntax error near unexpected token '%c'\n", c);
	split->errorcode = 1;
	return (1);
}

void	ft_export_error(t_split *split, char *cmd, char *var)
{
	printf("galactic: %s: '%s': not a valid identifier\n", cmd, var);
	split->ret = 1;
	split->errorcode = 1;
}

int	ft_error(t_split *split, char *line, int error)
{
	if (error == 1)
		ft_putstr_fd("galactic: uneven number of quotes\n", 2);
	if (error == 4)
	{
		split->errorcode = 127;
		printf("galactic: %s: command not found\n", line);
		return (127);
	}
	if (error == 5)
		printf("galactic: %s: No such file or directory\n", line);
	if (error == 7)
		ft_putstr_fd("galactic: uneven number of backslashes\n", 2);
	if (error == 8)
		printf("galactic: %s: HOME not set\n", line);
	split->errorcode = 1;
	return (1);
}
