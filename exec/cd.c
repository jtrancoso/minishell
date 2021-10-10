/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:49:30 by jtrancos          #+#    #+#             */
/*   Updated: 2021/10/10 11:36:21 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(t_list *list, t_comm *comm, t_split *split)
{
	int 	i;

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
	list = comm->env_head;
	while (list)
	{
		if (ft_strncmp(((t_env*)list->content)->id, "PWD", 3) == 0)
		{
			comm->dir = ft_strdup(((t_env*)list->content)->value);
			free(((t_env*)list->content)->value);
			((t_env*)list->content)->value = getcwd(NULL, 0);
			break ;
		}
		list = list->next;
	}
	list = comm->env_head;
	while (list)
	{
		if (ft_strncmp(((t_env*)list->content)->id, "OLDPWD", 6) == 0)
		{
			free(((t_env*)list->content)->value);
			((t_env*)list->content)->value = ft_strdup(comm->dir);
			break ;
		}
		list = list->next;
	}
	free(comm->dir);
}