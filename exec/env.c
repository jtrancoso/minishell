/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:58:07 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/23 17:10:32 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_comm *comm)
{
	int	i;

	i = 0;
	while (comm->cmd.env_array[i])
	{
		if (ft_strchr(comm->cmd.env_array[i], '='))
		{
			ft_putstr_fd(comm->cmd.env_array[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	return (0);
}
