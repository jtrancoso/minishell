/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:09:32 by jtrancos          #+#    #+#             */
/*   Updated: 2021/09/28 13:58:19 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_export(t_list *list, t_comm *comm, t_split *split)
{
	int i;

	i = 0;
	while (comm->cmd.cmd[1])
	{
		if (!ft_isalpha(comm->cmd.cmd[1][0]) || comm->cmd.cmd[1][0] != '_')
			return(1);
	}
	return (0);
}

void ft_export(t_list *list, t_comm *comm, t_split *split)
{
	char **export;
	int i;
	int len;

	i = 0;
	list = comm->env_head;
	len = ft_lstsize(list);
	export = malloc(sizeof(char *) * (len + 1));
	if (!export)
		return ;
	if (comm->cmd.cmd[1])
	{
		if (check_export(list, comm, split))
			return(ft_error(split, 6));
	}
	else
	{
		

	}

}
