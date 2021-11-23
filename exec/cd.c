/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:49:30 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/23 17:09:44 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd_error(t_split *split, char *cmd, char *file)
{
	printf("galactic: %s: %s: No such file or directory\n", cmd, file);
	split->errorcode = 1;
	return (1);
}

int	cd_home(t_list *list, t_comm *comm, t_split *split)
{
	int	i;

	i = 1;
	if (comm->cmd.cmd[1])
	{
		if (chdir(comm->cmd.cmd[1]) != 0)
			return (ft_cd_error(split, comm->cmd.cmd[0], comm->cmd.cmd[1]));
	}
	else
	{
		list = comm->env_head;
		while (list)
		{
			if (ft_strncmp(((t_env *)list->content)->id, "HOME", 4) == 0)
				i = chdir(((t_env *)list->content)->value);
			list = list->next;
		}
		if (i != 0)
			return (ft_error(split, comm->cmd.cmd[0], 8));
	}
	return (0);
}

void	export_oldpwd(t_comm *comm, t_list *new, t_env *env)
{
	new = ft_malloc(sizeof(t_list));
	env = ft_malloc(sizeof(t_env));
	new->content = env;
	((t_env *)new->content)->id = "OLDPWD";
	((t_env *)new->content)->value = NULL;
	ft_lstadd_back(&comm->env_head, new);
}

void	create_oldpwd(t_list *list, t_comm *comm)
{
	int		i;
	t_env	*env;
	t_list	*new;

	new = NULL;
	env = NULL;
	i = 0;
	list = comm->env_head;
	while (list)
	{
		if (ft_strncmp(((t_env *)list->content)->id, "OLDPWD", 6) == 0)
		{
			i = 1;
			free(((t_env *)list->content)->value);
			((t_env *)list->content)->value = ft_strdup(comm->dir);
		}
		list = list->next;
	}
	if (i == 0)
		export_oldpwd(comm, new, env);
}

int	ft_cd(t_list *list, t_comm *comm, t_split *split)
{
	if (cd_home(list, comm, split))
		return (1);
	list = comm->env_head;
	while (list)
	{
		if (ft_strncmp(((t_env *)list->content)->id, "PWD", 3) == 0)
		{
			comm->dir = ft_strdup(((t_env *)list->content)->value);
			free(((t_env *)list->content)->value);
			((t_env *)list->content)->value = getcwd(NULL, 0);
		}
		list = list->next;
	}
	create_oldpwd(list, comm);
	free(comm->dir);
	return (0);
}
