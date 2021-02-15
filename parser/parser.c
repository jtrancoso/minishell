/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:45:00 by jtrancos          #+#    #+#             */
/*   Updated: 2021/02/15 17:40:49 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parseline(t_comm *comm, char *line)
{
	int i;
	char aux[8];
	int j;

	i = 0;
	j = 0;
	ft_bzero(aux, 8);
	while (ft_isspace(line[i]))
		i++;
	while (ft_isalpha(line[i]))
	{
		aux[j] = line[i];
		i++;
		j++;
	}
	aux[j] = '\0';
	while (ft_isspace(line[i]))
		i++;
	if (ft_strncmp(aux, "echo", 4) == 0 && ft_strlen(aux) == 4)
		return(ft_echo(comm, line + i));
	return (0);
}