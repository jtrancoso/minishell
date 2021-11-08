/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:40:30 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/08 13:54:08 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_unset(t_comm *comm, int i)
{
	int	j;

	j = 0;
	if (!ft_isalpha(comm->cmd.cmd[i][j]) && comm->cmd.cmd[i][j] != '_')
		return (0);
	j++;
	while (comm->cmd.cmd[i][j])
	{
		if (!ft_isalnum(comm->cmd.cmd[i][j]) && comm->cmd.cmd[i][j] != '_')
			return (0);
		j++;
	}
	return (1);
}

void	unset_var(t_list *list, t_comm *comm, int *i)
{
	t_list	*aux;
	t_list	*prev;
	int		len;

	list = comm->env_head;
	prev = list;
	while (list)
	{
		len = ft_strlen(((t_env *)list->content)->id);
		if (ft_strchr(((t_env *)list->content)->id, '='))
			len = len - 1;
		if (ft_strncmp(((t_env *)list->content)->id, comm->cmd.cmd[*i],
				ft_strlen(comm->cmd.cmd[*i])) == 0
			&& (ft_strlen(comm->cmd.cmd[*i]) == len))
		{
			if (list->next)
				aux = list->next;
			else
				aux = NULL;
			ft_lstdelone(list, &free_env);
			prev->next = aux;
		}
		prev = list;
		list = list->next;
	}
}

int	ft_unset(t_list *list, t_comm *comm, t_split *split)
{
	int		i;
	int		len;
	int		ret;

	i = 1;
	ret = 0;
	while (comm->cmd.cmd[i])
	{
		comm->export.f_valid = 0;
		if (!check_unset(comm, i))
		{
			ft_error(split, 6);
			ret = 1;
			comm->export.f_valid = 1;
		}
		if (!comm->export.f_valid)
			unset_var(list, comm, &i);
		i++;
	}
	if (ret)
		return (1);
	return (0);
}
