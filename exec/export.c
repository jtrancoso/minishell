/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:09:32 by jtrancos          #+#    #+#             */
/*   Updated: 2021/10/01 13:26:28 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_export(t_list *list, t_comm *comm, t_split *split, int i)
{
	int j;

	j = 0;
	if (!ft_isalpha(comm->cmd.cmd[i][0]) && comm->cmd.cmd[i][0] != '_')
		return(0);
	while (comm->cmd.cmd[i][j] != '=' && comm->cmd.cmd[i][j])
	{
		if (!ft_isalnum(comm->cmd.cmd[i][j]) && comm->cmd.cmd[i][j] != '_')
			return(0);
		j++;
	}
	return (1);
}

void ft_export(t_list *list, t_comm *comm, t_split *split)
{
	int i;
	t_list *new;
	t_env *env;

	i = 1;
	list = comm->env_head;
	while (comm->cmd.cmd[i]) //el bucle es para cuando hay export algo
	{
		if (!check_export(list, comm, split, i))
		{
			ft_error(split, 6);
			comm->export.f_valid = 1;
		}
		if (!comm->export.f_valid)
		{
			if (ft_strchr(comm->cmd.cmd[i], '='))
			{
				comm->export.id = ft_substr(comm->cmd.cmd[i], 0, ft_strchr(comm->cmd.cmd[i], '=') - comm->cmd.cmd[i] + 1);
				comm->export.value =ft_strdup(ft_strchr(comm->cmd.cmd[i], '=') + 1);
			}
			else if (!ft_strchr(comm->cmd.cmd[i], '='))
			{
				comm->export.id = ft_strdup(comm->cmd.cmd[i]);
				comm->export.value = NULL;
			}
			list = comm->env_head;
			while (list)
			{
				if (ft_strncmp(comm->export.id, ((t_env*)list->content)->id, ft_strlen(((t_env*)list->content)->id)) == 0)
				{
					((t_env*)list->content)->value = comm->export.value;
					comm->export.f_exist = 1;
				}
				list = list->next;
			}
			if (!comm->export.f_exist)
			{
				new = malloc(sizeof(t_list));
				env = malloc(sizeof(t_env));
				new->content = env;
				((t_env*)new->content)->id = comm->export.id;
				((t_env*)new->content)->value = comm->export.value;
				ft_lstadd_back(&comm->env_head, new);
			}
			//free(id);
			//free(value);
		}
		i++;
	}
	/*else
	{
		

	}*/
}
