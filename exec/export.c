/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:09:32 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/22 19:49:32 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_list(t_list *list, t_comm *comm, int *swapped)
{	
	if (list->next)
	{
		*swapped = 0;
		if (ft_strncmp(((t_export *)list->content)->id,
				((t_export *)list->next->content)->id,
				export_len(((t_export *)list->content)->id,
					((t_export *)list->next->content)->id)) > 0)
		{
			swap_list(list, comm);
			*swapped = 1;
		}
		if (ft_strncmp(((t_export *)list->content)->id,
				((t_export *)list->next->content)->id,
				export_len(((t_export *)list->content)->id,
					((t_export *)list->next->content)->id)) == 0)
		{
			if (ft_strlen(((t_export *)list->content)->id)
				> ft_strlen(((t_export *)list->next->content)->id))
			{
				swap_list(list, comm);
				*swapped = 1;
			}
		}
	}
}

void	export_print(t_list *list, t_comm *comm, t_split *split)
{
	list = comm->export_head;
	while (list)
	{
		ft_putstr_fd("declare -x ", 1);
		if (ft_strchr((((t_export *)list->content)->id), '=') == 0)
			ft_putstr_fd(((t_export *)list->content)->id, 1);
		else
		{
			((t_export *)list->content)
				->id[strlen(((t_export *)list->content)->id) - 1] = '\0';
			ft_putstr_fd(((t_export *)list->content)->id, 1);
		}
		if (((t_export *)list->content)->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(((t_export *)list->content)->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		list = list->next;
	}
}

void	export_new_var(t_comm *comm, t_list *new, t_env *env)
{
	new = ft_malloc(sizeof(t_list));
	env = ft_malloc(sizeof(t_env));
	new->content = env;
	((t_env *)new->content)->id = comm->export.id;
	((t_env *)new->content)->value = comm->export.value;
	ft_lstadd_back(&comm->env_head, new);
}

int	ft_export(t_list *list, t_comm *comm, t_split *split)
{
	t_list	*new;
	t_env	*env;
	int		i;

	i = 1;
	while (comm->cmd.cmd[i])
	{
		comm->export.f_valid = 0;
		comm->export.f_exist = 0;
		check_export(list, comm, split, i);
		if (!comm->export.f_valid)
		{
			export_value(list, comm, i);
			if (!comm->export.f_exist)
				export_new_var(comm, new, env);
		}
		i++;
	}
	if (comm->cmd.cmd[1] == NULL)
	{
		export_list(list, comm, split);
		export_print(list, comm, split);
		ft_lstclear(&comm->export_head, &free_export);
	}
	return (comm->export.ret);
}
