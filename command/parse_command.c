/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:01:34 by jtrancos          #+#    #+#             */
/*   Updated: 2021/09/27 13:24:25 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **ft_superglue(t_list *list, t_comm *comm)
{
	char **str;
	char *aux;
	int len;
	int i;

	list = comm->env_head;
	len = ft_lstsize(list);
	str = malloc(sizeof(char *) * (len + 1));
	if(!str)
		return (NULL);
	i = 0;
	while (list)
	{
		aux = ft_strjoin(((t_env*)list->content)->id, "=");
		str[i] = ft_strjoin(aux, ((t_env*)list->content)->value);
		free(aux);
		list = list->next;
		i++;
	}
	str[i] = NULL;
	return(str);
}

char *create_realpath(char *path, char *cmd)
{
	char *aux;

	if (!path)
		return (NULL);
	aux = path;
	path = ft_strjoin(path, cmd);
	free (aux);
	return (path);
}

char *get_path(t_list *list, t_comm *comm, char *cmd)
{
	char *aux;
	char *aux_cmd;
	char **paths;
	char *real_path;
	int i;
	struct stat	t_stat;
	int is_stat;

	list = comm->env_head;
	i = 0;
	while (list)
	{
		if (ft_strncmp(((t_env*)list->content)->id, "PATH", 4) == 0)
			aux = ft_strdup(((t_env*)list->content)->value);
		list = list->next;
	}
	paths = ft_split(aux, ':');
	free(aux);
	aux_cmd = ft_strjoin("/", cmd);
	i = 0;
	while (paths[i])
	{
		real_path = create_realpath(paths[i], aux_cmd);
		is_stat = lstat(real_path, &t_stat);
		if (is_stat == 0)
		{
			aux = ft_strdup(real_path);
			free(real_path);
			free(aux_cmd);
			ft_malloc_free(comm, paths, i + 1);
			return(aux);
		}
		free(real_path);
		i++;
	}
	free(paths);
	free(aux_cmd);
	return (NULL);
}

int check_path(char *cmd)
{
	if (cmd[0] == '/')
		return (1);
	else if (ft_strlen(cmd) == 3 && ft_strncmp(cmd, "pwd", 3) == 0)
		return(2);
	else if (ft_strlen(cmd) == 4 && ft_strncmp(cmd, "echo", 4) == 0)
		return(2);
	else if (ft_strlen(cmd) == 4 && ft_strncmp(cmd, "exit", 4) == 0)
		return(2);
	/*else if (ft_strlen(cmd) == 3 && ft_strncmp(cmd, "env", 3) == 0)
		return(2);*/
	else if (ft_strlen(cmd) == 2 && ft_strncmp(cmd, "cd", 2) == 0)
		return(2);
	else if (ft_strlen(cmd) == 5 && ft_strncmp(cmd, "unset", 5) == 0)
		return(2);
	else if (ft_strlen(cmd) == 6 && ft_strncmp(cmd, "export", 6) == 0)
		return(2);
	return (0);
}

int exec_comm(t_list *list, t_comm *comm, t_split *split) //TODO: ver si hace falta return o no
{
	if (ft_strncmp(comm->cmd.path, "pwd", 3) == 0)
	{
		ft_pwd(list, comm);
		return(1);
	}
	else if (ft_strncmp(comm->cmd.path, "echo", 4) == 0)
		return(1);
	else if (ft_strncmp(comm->cmd.path, "exit", 4) == 0)
	{
		ft_exit(list, comm);
		return(1);
	}
	else if (ft_strncmp(comm->cmd.path, "env", 3) == 0)
		return(1);
	else if (ft_strncmp(comm->cmd.path, "cd", 2) == 0)
	{	
		ft_cd(list, comm, split);
		return(1);
	}
	else if (ft_strncmp(comm->cmd.path, "unset", 5) == 0)
		return(1);
	else if (ft_strncmp(comm->cmd.path, "export", 6) == 0)
		return(1);
	return(0);
}

int parse_command(t_list *list, t_comm *comm, t_split *split)
{
	t_list *env_list;
	int	status;
	char **cmd;
	char *path;
	char **env_array;

	comm->cmd.cmd = ft_split(((t_comm*)list->content)->t_word, ' ');
	comm->cmd.env_array = ft_superglue(list, comm);
	//printf("%s\n", comm->cmd.cmd[0]);
	if (!check_path(comm->cmd.cmd[0]))
		comm->cmd.path = get_path(list, comm, comm->cmd.cmd[0]);
	else if (check_path(comm->cmd.cmd[0]) == 1)
		comm->cmd.path = ft_strdup(comm->cmd.cmd[0]);
	else
	{
		comm->cmd.path = ft_strdup(comm->cmd.cmd[0]);
		exec_comm(list, comm, split);
		//printf("%d\n", check_path(comm->cmd.cmd[0]));
	}
	//printf("%s\n", comm->cmd.path);
	if (check_path(comm->cmd.cmd[0]) != 2)
	{
		status = 0;
		env_list = comm->env_head;
		list = comm->parse_head;
		comm->pid = fork();
		if (comm->pid == 0)
		{
			if (execve(comm->cmd.path, comm->cmd.cmd, comm->cmd.env_array) != 0)
				ft_error(split, 4);
			exit(0);
		}
		else
			wait(&status);
	} 
	free(comm->cmd.path);
	ft_malloc_free(comm, comm->cmd.cmd, 0);
	ft_malloc_free(comm, comm->cmd.env_array, 0);
	return(0);
}