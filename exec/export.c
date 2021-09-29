/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:09:32 by jtrancos          #+#    #+#             */
/*   Updated: 2021/09/29 13:30:36 by jtrancos         ###   ########.fr       */
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
		printf("hola\n");
		if (!ft_isalnum(comm->cmd.cmd[i][j]) && comm->cmd.cmd[i][j] != '_')
			return(0);
		j++;
	}
	return (1);
}

void ft_export(t_list *list, t_comm *comm, t_split *split)
{
	int i;
	char *id;
	char *value;
	int flag;

	i = 1;
	list = comm->env_head;
	while (comm->cmd.cmd[i])
	{
		flag = 0;
		printf("holi\n");
		if (!check_export(list, comm, split, i))
		{
			ft_error(split, 6);
			flag = 1;
		}
		if (ft_strchr(comm->cmd.cmd[i], '=') && !flag)
		{
			id = ft_substr(comm->cmd.cmd[i], 0, ft_strchr(comm->cmd.cmd[i], '=') - comm->cmd.cmd[i]);
			value =ft_strdup(ft_strchr(comm->cmd.cmd[i], '=') + 1);
			printf("id:%s value:%s\n", id, value);
		}
		i++;
	}
	/*else
	{
		

	}*/
}
