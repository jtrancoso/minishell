/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:44:14 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/24 12:22:16 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_error_syntax(t_split *split, char c)
{
	if (!c)
		ft_putstr_fd("galactic: syntax error near unexpected token 'newline'\n",
			2);
	else
	{
		ft_putstr_fd("galactic: syntax error near unexpected token '", 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd("'\n", 2);
	}
	split->errorcode = 1;
	return (1);
}

void	ft_export_error(t_split *split, char *cmd, char *var)
{
	ft_putstr_fd("galactic: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	split->ret = 1;
	split->errorcode = 1;
}

void	ft_error_bis(char *line, int error)
{
	if (error == 5)
	{
		ft_putstr_fd("galactic: ", 2);
		ft_putstr_fd(line, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	if (error == 7)
		ft_putstr_fd("galactic: uneven number of backslashes\n", 2);
	if (error == 8)
	{
		ft_putstr_fd("galactic: ", 2);
		ft_putstr_fd(line, 2);
		ft_putstr_fd(": HOME not set\n", 2);
	}
}

int	ft_error(t_split *split, char *line, int error)
{
	if (error == 1)
		ft_putstr_fd("galactic: uneven number of quotes\n", 2);
	if (error == 4)
	{
		split->errorcode = 127;
		if (ft_strchr(line, '/'))
		{
			ft_putstr_fd("galactic: ", 2);
			ft_putstr_fd(line, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else
		{
			ft_putstr_fd("galactic: ", 2);
			ft_putstr_fd(line, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		return (127);
	}
	if (error > 5)
		ft_error_bis(line, error);
	split->errorcode = 1;
	return (1);
}
