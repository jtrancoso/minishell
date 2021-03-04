/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:45:00 by jtrancos          #+#    #+#             */
/*   Updated: 2021/03/04 17:53:52 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parseline(t_comm *comm, char *line)
{
	int i;
	char builtin[BUFFERSIZE];
	int j;

	i = 0;
	j = 0;
	ft_bzero(builtin, BUFFERSIZE - 1);
	while (ft_isspace(line[i]))
		i++;
	while (ft_isascii(line[i]))
	{
		builtin[j] = line[i];
		i++;
		j++;
	}
	builtin[j] = '\0';
	//printf("%s\n", builtin);
	while (ft_isspace(line[i]))
		i++;
	if (ft_strncmp(builtin, "echo", 4) == 0 && ft_strlen(builtin) == 4)
		return(ft_echo(comm, line + i));
	return (0);
}