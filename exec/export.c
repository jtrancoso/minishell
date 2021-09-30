/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:09:32 by jtrancos          #+#    #+#             */
/*   Updated: 2021/09/30 12:10:29 by jtrancos         ###   ########.fr       */
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
	t_list *new;
	t_env *env;

	i = 1;
	list = comm->env_head;
	while (comm->cmd.cmd[i]) //el bucle es para cuando hay export algo
	{
		flag = 0;
		printf("holi\n");
		if (!check_export(list, comm, split, i))
		{
			ft_error(split, 6);
			flag = 1;
		}
		if (!flag)
		{
			if (ft_strchr(comm->cmd.cmd[i], '='))
			{
				id = ft_substr(comm->cmd.cmd[i], 0, ft_strchr(comm->cmd.cmd[i], '=') - comm->cmd.cmd[i] + 1);
				value =ft_strdup(ft_strchr(comm->cmd.cmd[i], '=') + 1);
				printf("id:%s value:%s\n", id, value);
			}
			else
			{
				id = ft_strdup(comm->cmd.cmd[i]);
				value = NULL;
				printf("id:%s value:%s\n", id, value);
			}
			new = malloc(sizeof(t_list));
			env = malloc(sizeof(t_env));
			new->content = env;
			((t_env*)new->content)->id = id;
			((t_env*)new->content)->value = value;
			ft_lstadd_back(&comm->env_head, new);
			//free(id);
			//free(value);
		}
		i++;
	}
	/*else
	{
		

	}*/
}
