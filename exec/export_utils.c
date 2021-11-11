/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:52:52 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/11 20:01:46 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	export_len(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 > len2)
		return (len2);
	return (len1);
}

void	export_list(t_list *list, t_comm *comm, t_split *split)
{
	t_list	*new;
	t_list	*export;
	int		i;
	int		swapped;

	fill_list(list, comm, new, export);
	list = comm->export_head;
	while (list)
	{
		sort_list(list, comm, &swapped);
		if (swapped == 1)
			list = comm->export_head;
		else
			list = list->next;
	}
}

void	fill_list(t_list *list, t_comm *comm, t_list *new, t_list *export)
{
	comm->export_head = NULL;
	list = comm->env_head;
	while (list)
	{
		new = ft_malloc(sizeof(t_list));
		export = ft_malloc(sizeof(t_export));
		new->content = export;
		((t_export *)new->content)->id
			= ft_strdup(((t_env *)list->content)->id);
		if (((t_env *)list->content)->value)
			((t_export *)new->content)->value
				= ft_strdup(((t_env *)list->content)->value);
		else
			((t_export *)new->content)->value = NULL;
		ft_lstadd_back(&comm->export_head, new);
		list = list->next;
	}
}

void	swap_list(t_list *list, t_comm *comm)
{
	char	*aux_id;
	char	*aux_value;

	aux_id = ((t_export *)list->content)->id;
	((t_export *)list->content)->id = ((t_export *)list->next->content)->id;
	((t_export *)list->next->content)->id = aux_id;
	aux_value = ((t_export *)list->content)->value;
	((t_export *)list->content)->value
		= ((t_export *)list->next->content)->value;
	((t_export *)list->next->content)->value = aux_value;
}

void	check_export(t_list *list, t_comm *comm, t_split *split, int i)
{
	int	j;

	j = 0;
	if (!ft_isalpha(comm->cmd.cmd[i][0]) && comm->cmd.cmd[i][0] != '_')
	{
		ft_error(split, comm->cmd.cmd[0], 6);
		comm->export.ret = 1;
		comm->export.f_valid = 1;
		return ;
	}
	while (comm->cmd.cmd[i][j] != '=' && comm->cmd.cmd[i][j])
	{
		if (!ft_isalnum(comm->cmd.cmd[i][j]) && comm->cmd.cmd[i][j] != '_')
		{
			ft_error(split, comm->cmd.cmd[0], 6);
			comm->export.ret = 1;
			comm->export.f_valid = 1;
			return ;
		}
		j++;
	}
}
