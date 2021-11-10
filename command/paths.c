/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:21:59 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/10 17:05:06 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_realpath(char *path, char *cmd)
{
	char	*aux;

	if (!path)
		return (NULL);
	aux = path;
	path = ft_strjoin(path, cmd);
	free (aux);
	return (path);
}

char	*pathing(t_comm *comm, char **paths, char *aux_cmd, int i)
{
	struct stat	t_stat;
	int			is_stat;
	char		*real_path;
	char		*aux;

	real_path = create_realpath(paths[i], aux_cmd);
	is_stat = lstat(real_path, &t_stat);
	if (is_stat == 0)
	{
		aux = ft_strdup(real_path);
		free(real_path);
		free(aux_cmd);
		return (aux);
	}
	free(real_path);
	return (NULL);
}

char	*get_path(t_list *list, t_comm *comm, char *cmd)
{
	char		*aux;
	char		*aux_cmd;
	char		**paths;
	int			i;

	list = comm->env_head;
	i = 0;
	aux = NULL;
	while (list)
	{
		if (ft_strncmp(((t_env *)list->content)->id, "PATH", 4) == 0)
			aux = ft_strdup(((t_env *)list->content)->value);
		list = list->next;
	}
	paths = ft_split(aux, ':');
	free(aux);
	if (!paths)
		return (NULL);
	aux_cmd = ft_strjoin("/", cmd);
	i = 0;
	while (paths[i])
	{
		aux = pathing(comm, &paths[i], aux_cmd, i); //TODO: mirar este malloc
		if (aux)
		{
			ft_malloc_free(comm, paths, i + 1);
			return (aux);
		}
		i++;
		/*real_path = create_realpath(paths[i], aux_cmd);
		is_stat = lstat(real_path, &t_stat);
		if (is_stat == 0)
		{
			aux = ft_strdup(real_path);
			free(real_path);
			free(aux_cmd);
			ft_malloc_free(comm, paths, i + 1);
			return (aux);
		}
		free(real_path);
		i++;*/
	}
	free(paths);
	free(aux_cmd);
	return (NULL);
}
