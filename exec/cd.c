/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:49:30 by jtrancos          #+#    #+#             */
/*   Updated: 2021/09/27 13:43:44 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(t_list *list, t_comm *comm, t_split *split)
{
	int i;

	i = 0;
	if (comm->cmd.cmd[1])
	{
		if (chdir(comm->cmd.cmd[1]) != 0)
			ft_error(split, 5);
	}
	else
	{
		list = comm->env_head;
		while (list)
		{
			if (ft_strncmp(((t_env*)list->content)->id, "HOME", 4) == 0)
				chdir(((t_env*)list->content)->value);				
			list = list->next;
		}
	}
}