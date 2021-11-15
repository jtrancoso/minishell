/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_quotes2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 12:59:52 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/15 13:08:07 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_str(t_list *list, t_comm *comm, t_split *split, char **aux)
{
	int	i;

	i = 0;
	while (aux[i])
	{
		split->str = ft_strdup(comm->cmd.cmd[i]);
		free(comm->cmd.cmd[i]);
		comm->cmd.cmd[i] = aux[i];
		free(split->str);
		i++;
	}
}
