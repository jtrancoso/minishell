/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:01:34 by jtrancos          #+#    #+#             */
/*   Updated: 2021/10/13 14:31:15 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void clean_quotes(t_list *list, t_comm *comm, t_split *split)
{
	char **aux;
	int i;
	int j;
	int k;
	int l;
	char *str;

	i = 0;
	j = 0;
	while (comm->cmd.cmd[i])
		i++;
	aux = malloc(sizeof(char **) * (i + 1));
	i = 0;
	while (comm->cmd.cmd[i])
	{
		l = 0;
		k = 0;
		aux[j] = malloc(sizeof(char *) * (ft_strlen(comm->cmd.cmd[i])) + 1);
		while (comm->cmd.cmd[i][k])
		{
			if (check_inverted_var(&comm->cmd.cmd[i][k]) == 1)
				k += 2;
			check_quote(split, &comm->cmd.cmd[i][k]);
			if (comm->cmd.cmd[i][k] == '\"' && split->f_double == 1)
			{
				k++;
				comm->f_d = 1;
			}
			else if (comm->cmd.cmd[i][k] == '\"' && split->f_double == 0 && comm->f_d == 1)
			{
				k++;
				comm->f_d = 0;
			}
			else if (comm->cmd.cmd[i][k] == '\'' && split->f_simple == 1)
			{
				k++;
				comm->f_s = 1;
			}
			else if (comm->cmd.cmd[i][k] == '\'' && split->f_simple == 0 && comm->f_s == 1)
			{
				k++;
				comm->f_s = 0;
			}
			else
			{
				aux[j][l] = comm->cmd.cmd[i][k];
				l++;
				k++;
			}
		}
		aux[j][l] = '\0';
		i++;
		j++;
	}
	aux[j] = NULL;
	i = 0;
	while (aux[i])
	{
		str = ft_strdup(comm->cmd.cmd[i]);
		free(comm->cmd.cmd[i]);
		comm->cmd.cmd[i] = aux[i];
		free(str);
		printf("finalcmd[%d]%s\n", i, comm->cmd.cmd[i]);
		i++;
	}
	ft_malloc_free(comm, aux, j);
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
	else if (ft_strlen(cmd) == 3 && ft_strncmp(cmd, "env", 3) == 0)
		return(2);
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
	{
		ft_env(list, comm, split);
		return(1);
	}
	else if (ft_strncmp(comm->cmd.path, "cd", 2) == 0)
	{	
		ft_cd(list, comm, split);
		return(1);
	}
	else if (ft_strncmp(comm->cmd.path, "unset", 5) == 0)
		return(1);
	else if (ft_strncmp(comm->cmd.path, "export", 6) == 0)
	{
		ft_export(list, comm, split);
		return(1);
	}
	return(0);
}

int parse_command(t_list *list, t_comm *comm, t_split *split)
{
	t_list *env_list;
	int	status;
	char **cmd;
	char *path;
	char **env_array;

	comm->cmd.cmd = ft_splitshell(split, ((t_comm*)list->content)->t_word, ' ');
	comm->cmd.env_array = ft_superglue(list, comm);
	printf("cmd[0]:%s cmd[1]:%s\n", comm->cmd.cmd[0], comm->cmd.cmd[1]);
	clean_quotes(list, comm, split);
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