/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:01:34 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/20 18:37:37 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_parse(t_list *list, t_comm *comm, t_split *split)
{
	comm->cmd.cmd = ft_splitshell(split, ((t_comm *)list->content)
			->t_command, ' ');
	comm->cmd.env_array = ft_superglue(list, comm);
	clean_quotes(list, comm, split);
}

int	check_path(char *cmd)
{
	if (cmd[0] == '/')
		return (1);
	else if (cmd[0] == '.' && cmd[1] == '/')
		return (3);
	else if (ft_strlen(cmd) == 3 && ft_strncmp(cmd, "pwd", 3) == 0)
		return (2);
	else if (ft_strlen(cmd) == 4 && ft_strncmp(cmd, "echo", 4) == 0)
		return (2);
	else if (ft_strlen(cmd) == 4 && ft_strncmp(cmd, "exit", 4) == 0)
		return (2);
	else if (ft_strlen(cmd) == 3 && ft_strncmp(cmd, "env", 3) == 0)
		return (2);
	else if (ft_strlen(cmd) == 2 && ft_strncmp(cmd, "cd", 2) == 0)
		return (2);
	else if (ft_strlen(cmd) == 5 && ft_strncmp(cmd, "unset", 5) == 0)
		return (2);
	else if (ft_strlen(cmd) == 6 && ft_strncmp(cmd, "export", 6) == 0)
		return (2);
	return (0);
}

int	exec_comm(t_list *list, t_comm *comm, t_split *split)
{
	if (ft_strncmp(comm->cmd.path, "pwd", 3) == 0)
		return (ft_pwd(list, comm));
	else if (ft_strncmp(comm->cmd.path, "echo", 4) == 0)
		return (ft_echo(list, comm, split));
	else if (ft_strncmp(comm->cmd.path, "exit", 4) == 0)
		check_exit(list, comm, split);
	else if (ft_strncmp(comm->cmd.path, "env", 3) == 0)
		return (ft_env(list, comm, split));
	else if (ft_strncmp(comm->cmd.path, "cd", 2) == 0)
		return (ft_cd(list, comm, split));
	else if (ft_strncmp(comm->cmd.path, "unset", 5) == 0)
		return (ft_unset(list, comm, split));
	else if (ft_strncmp(comm->cmd.path, "export", 6) == 0)
		return (ft_export(list, comm, split));
	return (split->errorcode);
}

/*line 87 = BLACKMAGIC*/

void	exec_made_function(t_list *list, t_comm *comm, t_split *split)
{
	int		status;
	t_list	*env_list;

	if (check_path(comm->cmd.cmd[0]) != 2)
	{
		status = 0;
		env_list = comm->env_head;
		list = comm->parse_head;
		comm->pid = fork();
		if (comm->pid == 0)
		{
			if (execve(comm->cmd.path, comm->cmd.cmd, comm->cmd.env_array) != 0)
				exit(ft_error(split, comm->cmd.cmd[0], 4));
		}
		else
		{
			wait(&status);
			split->errorcode = status >> 8;
		}
	}	
}

int	parse_command(t_list *list, t_comm *comm, t_split *split)
{
	char	**cmd;
	char	*path;
	char	**env_array;

	init_parse(list, comm, split);
	if (comm->cmd.cmd[0])
	{
		if (!check_path(comm->cmd.cmd[0]))
			comm->cmd.path = get_path(list, comm, comm->cmd.cmd[0], -1);
		else if (check_path(comm->cmd.cmd[0]) == 1)
			comm->cmd.path = ft_strdup(comm->cmd.cmd[0]);
		else if (check_path(comm->cmd.cmd[0]) == 3)
			comm->cmd.path = point_path(split, comm->cmd.cmd[0]);
		else
		{
			comm->cmd.path = ft_strdup(comm->cmd.cmd[0]);
			split->errorcode = exec_comm(list, comm, split);
		}
		exec_made_function(list, comm, split);
		free(comm->cmd.path);
		ft_malloc_free(comm, comm->cmd.cmd, 0);
		ft_malloc_free(comm, comm->cmd.env_array, 0);
	}
	return (0);
}
