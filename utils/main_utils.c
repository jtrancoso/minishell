/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 19:41:14 by isoria-g          #+#    #+#             */
/*   Updated: 2021/11/22 17:44:07 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_env(t_comm *comm, char **envp)
{
	t_list	*new;
	t_env	*env;
	int		i;
	char	**split_env;

	i = 0;
	comm->env_head = NULL;
	if (!envp[i])
		galactic_env(comm);
	i = 0;
	while (envp[i])
	{
		new = ft_malloc(sizeof(t_list));
		env = ft_malloc(sizeof(t_env));
		split_env = ft_split(envp[i], '=');
		new->content = env;
		if (split_env[1])
		{
			((t_env *)new->content)->id = split_env[0];
			((t_env *)new->content)->value = split_env[1];
			ft_lstadd_back(&comm->env_head, new);
		}
		free(split_env);
		i++;
	}
}

void	set_flags(t_list *list, t_comm *comm)
{
	list = comm->parse_head;
	while (list)
	{
		if (((t_comm *)list->content)->t_word != NULL && list->next)
		{
			if (((t_comm *)list->next->content)->t_pipe == 1)
				((t_comm *)list->content)->post_pipe = 1;
			if (((t_comm *)list->next->content)->t_semi == 1)
				((t_comm *)list->content)->next_semi = 1;
		}
		if (((t_comm *)list->content)->t_gt == 1
			|| ((t_comm *)list->content)->t_lt == 1
			|| ((t_comm *)list->content)->t_gtgt == 1)
			((t_comm *)list->next->content)->prev_redir = 1;
		if (((t_comm *)list->content)->t_pipe == 1)
		{
			if (((t_comm *)list->next->content)->t_word != NULL)
				((t_comm *)list->next->content)->prev_pipe = 1;
		}
		list = list->next;
	}
}

void	set_shlvl(t_list *list, t_comm *comm, t_split *split)
{
	list = comm->env_head;
	while (list)
	{
		if (ft_strncmp(((t_env *)list->content)->id, "USER", 4) == 0)
			comm->user = ft_strdup(((t_env *)list->content)->value);
		else if (ft_strncmp(((t_env *)list->content)->id, "SHLVL", 5) == 0)
			((t_env *)list->content)->value
				= next_shlvl(((t_env *)list->content)->value);
		list = list->next;
	}
	split->errorcode = 0;
}
