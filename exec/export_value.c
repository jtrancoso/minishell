/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 19:41:44 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/22 19:50:56 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_id_value(t_comm *comm, int i)
{
	if (ft_strchr(comm->cmd.cmd[i], '='))
	{
		comm->export.id = ft_substr(comm->cmd.cmd[i], 0,
				ft_strchr(comm->cmd.cmd[i], '=')
				- comm->cmd.cmd[i] + 1);
		comm->export.value = ft_strdup(ft_strchr(comm->cmd.cmd[i],
					'=') + 1);
	}
	else if (!ft_strchr(comm->cmd.cmd[i], '='))
	{
		comm->export.id = ft_strdup(comm->cmd.cmd[i]);
		comm->export.value = NULL;
	}
}

void	if_not_id(t_list *list, t_comm *comm, int len)
{
	if (!ft_strchr(((t_env *)list->content)->id, '='))
	{
		if (ft_strncmp(comm->export.id, ((t_env *)list->content)->id, len) == 0)
			comm->export.f_exist = 1;
	}
	else
	{
		if (ft_strncmp(comm->export.id, ((t_env *)list->content)->id, len - 1)
			== 0)
			comm->export.f_exist = 1;
	}
}

void	if_id(t_list *list, t_comm *comm, int len)
{
	if (ft_strchr(((t_env *)list->content)->id, '='))
	{
		if (ft_strncmp(comm->export.id, ((t_env *)list->content)->id, len) == 0)
		{
			((t_env *)list->content)->value = comm->export.value;
			comm->export.f_exist = 1;
		}
	}
	else
	{
		if (ft_strncmp(comm->export.id, ((t_env *)list->content)->id, len - 1)
			== 0)
		{
			((t_env *)list->content)->value = comm->export.value;
			comm->export.f_exist = 1;
		}
	}
}

void	export_value(t_list *list, t_comm *comm, int i)
{
	int	len;

	set_id_value(comm, i);
	list = comm->env_head;
	while (list)
	{
		if (ft_strlen(comm->export.id)
			> ft_strlen(((t_env *)list->content)->id))
			len = ft_strlen(comm->export.id);
		else
			len = ft_strlen(((t_env *)list->content)->id);
		if (!ft_strchr(comm->export.id, '='))
			if_not_id(list, comm, len);
		else
			if_id(list, comm, len);
		list = list->next;
	}
}
