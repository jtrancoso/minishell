/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:01:34 by jtrancos          #+#    #+#             */
/*   Updated: 2021/09/21 18:20:54 by jtrancos         ###   ########.fr       */
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

int parse_command(t_list *list, t_comm *comm, t_split *split)
{
	t_list *env_list;
	int	status;
	int i = 0;
	char **cmd;
	char **env_array;

	env_array = ft_superglue(list, comm);
	status = 0;
	env_list = comm->env_head;
	list = comm->parse_head;
	comm->pid = fork();
	cmd = malloc (sizeof(char *) * 3);
	cmd[0] = strdup("/bin/ls");
	cmd[1] = strdup("-la");
	cmd[2] = NULL;

	int q = 0;
	int h = 0;
	if (comm->pid == 0)
	{
		if (execve(cmd[0], cmd, env_array) != 0)
			ft_error(split, 4);
		exit(0);
	}
	else
	{
		wait(&status);
		printf("%d Hello from Parent!\n", comm->pid);
	}
	ft_malloc_free(comm, env_array);
	return(1);
}