/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:21:59 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/22 20:24:44 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*relative_path(t_split *split, char *cmd)
{
	char	*aux;
	char	*pwd;
	char	*expand;

	if (cmd[0] == '.')
	{
		aux = getcwd(NULL, 0);
		expand = ft_strjoin(aux, cmd + 1);
		free (aux);
		return (expand);
	}
	pwd = getcwd(NULL, 0);
	aux = ft_strjoin(pwd, "/");
	free (pwd);
	expand = ft_strjoin(aux, cmd);
	free (aux);
	return (expand);
}

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

char	**extract_path(t_list *list, t_comm *comm)
{
	char	*aux;
	char	**paths;

	list = comm->env_head;
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
	return (paths);
}

char	*get_path(t_list *list, t_comm *comm, char *cmd, int i)
{
	char		*aux;
	char		*aux_cmd;
	char		**paths;
	char		*real_path;
	struct stat	t_stat;

	paths = extract_path(list, comm);
	if (paths)
	{
		aux_cmd = ft_strjoin("/", cmd);
		while (paths[++i])
		{
			real_path = create_realpath(paths[i], aux_cmd);
			comm->path.is_stat = lstat(real_path, &t_stat);
			if (comm->path.is_stat == 0)
			{
				aux = dup_free_aux(real_path, aux_cmd);
				ft_malloc_free(paths, i + 1);
				return (aux);
			}
			free(real_path);
		}
		free_aux(aux_cmd, paths);
	}
	return (NULL);
}
