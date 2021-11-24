/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:27:45 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/24 09:30:32 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error_exit(t_split *split, char *cmd, char *arg, int flag)
{
	if (flag == 1)
	{
		printf("exit\n");
		printf("galactic: %s: %s: numeric argument required\n", cmd, arg);
		split->errorcode = 255;
	}
	if (flag == 2)
	{
		printf("exit\n");
		printf("galactic: %s: too many arguments\n", cmd);
		split->errorcode = 1;
	}
}

void	ft_exit(t_comm *comm, t_split *split, int flag)
{
	ft_lstclear(&comm->env_head, &free_env);
	ft_lstclear(&comm->parse_head, &free_list);
	free(comm->user);
	free(comm->cmd.path);
	free(comm->dir);
	ft_malloc_free(comm->cmd.cmd, 0);
	ft_malloc_free(comm->cmd.env_array, 0);
	if (!flag)
		printf("exit\n");
	exit(split->errorcode);
}

int	check_exit_digit(t_comm *comm, t_split *split)
{
	size_t	j;

	j = 0;
	while (ft_isdigit(comm->cmd.cmd[1][j]))
		j++;
	if (j < ft_strlen(comm->cmd.cmd[1]))
	{
		ft_error_exit(split, "exit", comm->cmd.cmd[1], 1);
		ft_exit(comm, split, 1);
	}
	return (j);
}

void	check_exit(t_comm *comm, t_split *split)
{
	int		i;
	size_t	j;

	i = 0;
	while (comm->cmd.cmd[i])
		i++;
	if (i > 2)
	{
		j = check_exit_digit(comm, split);
		if (i > 2 && j == ft_strlen(comm->cmd.cmd[1]))
		{
			ft_error_exit(split, "exit", comm->cmd.cmd[1], 2);
			return ;
		}
	}
	if (i == 2)
	{
		j = check_exit_digit(comm, split);
		if (j == ft_strlen(comm->cmd.cmd[1]))
		{
			split->errorcode = ft_atoi(comm->cmd.cmd[1]);
			ft_exit(comm, split, 0);
		}
	}
	ft_exit(comm, split, 0);
}
