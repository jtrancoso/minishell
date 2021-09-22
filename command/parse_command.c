/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:01:34 by jtrancos          #+#    #+#             */
/*   Updated: 2021/09/22 14:26:59 by jtrancos         ###   ########.fr       */
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

char *get_path(t_list *list, t_comm *comm, char *cmd)
{
	char *aux;
	char *aux_cmd;
	char **paths;
	char **aux_paths;
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
	while (paths[i])
	{
		aux_paths[i] = ft_strjoin(paths[i], aux_cmd);
		i++;
	}
	free(aux_cmd);
	//ft_malloc_free(comm, paths);  //TODO: HAY LEAKS Y DOBLES FREES POR AQUI!!
	i = 0;
	while (aux_paths[i])
	{
		is_stat = lstat(aux_paths[i], &t_stat);
		if (is_stat == 0)
		{
			printf("%s\n", aux_paths[i]);
			aux = ft_strdup(aux_paths[i]);
			//ft_malloc_free(comm, aux_paths); 
			return(aux);
		}
		i++;
	}
	ft_malloc_free(comm, aux_paths);
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

	//list = comm->parse_head;
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
	{
		wait(&status);
		printf("%d Hello from Parent!\n", comm->pid);
	}
	free(path);
	ft_malloc_free(comm, cmd);
	ft_malloc_free(comm, env_array);
	return(0);
}