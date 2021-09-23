/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:01:34 by jtrancos          #+#    #+#             */
/*   Updated: 2021/09/23 17:25:15 by jtrancos         ###   ########.fr       */
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

int parse_command(t_list *list, t_comm *comm, t_split *split)
{
	t_list *env_list;
	int	status;
	int i = 0;
	char **cmd;
	char *path;
	char **env_array;

	cmd = ft_split(((t_comm*)list->content)->t_word, ' ');
	env_array = ft_superglue(list, comm);
	path = get_path(list, comm, cmd[0]);
	status = 0;
	env_list = comm->env_head;
	list = comm->parse_head;
	comm->pid = fork();
	if (comm->pid == 0)
	{
		if (execve(path, cmd, env_array) != 0)
			ft_error(split, 4);
		exit(0);
	}
	else
		wait(&status);
	free(path);
	ft_malloc_free(comm, cmd, 0);
	ft_malloc_free(comm, env_array, 0);
	return(0);
}