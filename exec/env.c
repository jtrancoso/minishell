/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:58:07 by jtrancos          #+#    #+#             */
/*   Updated: 2021/10/22 17:07:58 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_env(t_list *list, t_comm *comm, t_split *split)
{
	int i;

	i = 0;
	while (comm->cmd.env_array[i])
	{
		if (ft_strchr(comm->cmd.env_array[i], '='))
		{
			ft_putstr_fd(comm->cmd.env_array[i], comm->redir.last_fdin);
			ft_putchar_fd('\n', comm->redir.last_fdin);
		}
		i++;
	}
}