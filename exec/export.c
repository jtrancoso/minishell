/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:09:32 by jtrancos          #+#    #+#             */
/*   Updated: 2021/10/21 11:49:38 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void swap_list(t_list *list, t_comm *comm, t_split *split)
{
	char *aux_id;
	char *aux_value;

	aux_id = ((t_export*)list->content)->id;
	((t_export*)list->content)->id = ((t_export*)list->next->content)->id;
	((t_export*)list->next->content)->id = aux_id;
	aux_value = ((t_export*)list->content)->value;
	((t_export*)list->content)->value = ((t_export*)list->next->content)->value;
	((t_export*)list->next->content)->value = aux_value;
}

size_t export_len(char *s1, char *s2)
{
	size_t len1;
	size_t len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 > len2)
		return (len2);
	return (len1);
}

void export_list(t_list *list, t_comm *comm, t_split *split)
{
	t_list *new;
	t_list *export;
	int i;
	int swapped;

	comm->export_head = NULL;
	list = comm->env_head;
	while (list)
	{
		new = malloc(sizeof(t_list));
		export = malloc(sizeof(t_export));
		new->content = export;
		((t_export*)new->content)->id = ft_strdup(((t_env*)list->content)->id);
		if (((t_env*)list->content)->value)
			((t_export*)new->content)->value = ft_strdup(((t_env*)list->content)->value);
		else 
			((t_export*)new->content)->value = NULL;
		ft_lstadd_back(&comm->export_head, new);
		list = list->next;
	}
	list = comm->export_head;
	while (list)
	{
		if (list->next)
		{
			swapped = 0;
			if (ft_strncmp(((t_export*)list->content)->id, ((t_export*)list->next->content)->id, export_len(((t_export*)list->content)->id, ((t_export*)list->next->content)->id)) > 0)
			{
				swap_list(list, comm, split);
				swapped = 1;
			}
			if (ft_strncmp(((t_export*)list->content)->id, ((t_export*)list->next->content)->id, export_len(((t_export*)list->content)->id, ((t_export*)list->next->content)->id)) == 0)
			{
				if (ft_strlen(((t_export*)list->content)->id) > ft_strlen(((t_export*)list->next->content)->id))
				{
					swap_list(list, comm, split);
					swapped = 1;
				}
			}
		}
		if (swapped == 1)
			list = comm->export_head;
		else
			list = list->next;
	}
}

void export_print(t_list *list, t_comm *comm, t_split *split)
{
	list = comm->export_head;
	while (list)
	{
		ft_putstr_fd("declare -x ", comm->redir.last_fdin);
		if (ft_strchr((((t_export*)list->content)->id), '=') == 0)
			ft_putstr_fd(((t_export*)list->content)->id, comm->redir.last_fdin);
		else
		{
			((t_export*)list->content)->id[strlen(((t_export*)list->content)->id) - 1] = '\0'; //FIXME: si se te ocurre algo mejor, adelante
			ft_putstr_fd(((t_export*)list->content)->id, comm->redir.last_fdin);
		}
		if (((t_export*)list->content)->value)
		{
			ft_putstr_fd("=\"", comm->redir.last_fdin);
			ft_putstr_fd(((t_export*)list->content)->value, comm->redir.last_fdin);
			ft_putstr_fd("\"", comm->redir.last_fdin);
		}
		ft_putstr_fd("\n", comm->redir.last_fdin);
		list = list->next;
	}
}

int	check_export(t_list *list, t_comm *comm, t_split *split, int i)
{
	int j;

	j = 0;
	if (!ft_isalpha(comm->cmd.cmd[i][0]) && comm->cmd.cmd[i][0] != '_')
		return(0);
	while (comm->cmd.cmd[i][j] != '=' && comm->cmd.cmd[i][j])
	{
		if (!ft_isalnum(comm->cmd.cmd[i][j]) && comm->cmd.cmd[i][j] != '_')
			return(0);
		j++;
	}
	return (1);
}

void ft_export(t_list *list, t_comm *comm, t_split *split)
{
	int i;
	t_list *new;
	t_env *env;

	i = 1;
	while (comm->cmd.cmd[i]) //el bucle es para cuando hay export algo
	{
		comm->export.f_valid = 0;
		if (!check_export(list, comm, split, i)) //checkeamos que el formato es valido (a=c si, =c no)
		{
			ft_error(split, 6);
			comm->export.f_valid = 1;
		}
		if (!comm->export.f_valid) //si es valido
		{
			if (ft_strchr(comm->cmd.cmd[i], '=')) //si hay igual, copiamos el id + = y el value
			{
				comm->export.id = ft_substr(comm->cmd.cmd[i], 0, ft_strchr(comm->cmd.cmd[i], '=') - comm->cmd.cmd[i] + 1);
				comm->export.value =ft_strdup(ft_strchr(comm->cmd.cmd[i], '=') + 1);
			}
			else if (!ft_strchr(comm->cmd.cmd[i], '=')) //si no hay igual, solo copiamos el id y dejamos value null
			{
				comm->export.id = ft_strdup(comm->cmd.cmd[i]);
				comm->export.value = NULL;
			}
			list = comm->env_head;
			while (list) //recorremos la lista para ver si ya tenemos ese id, y sobreescribimos el value en tal caso
			{
				if (ft_strncmp(comm->export.id, ((t_env*)list->content)->id, ft_strlen(((t_env*)list->content)->id)) == 0)
				{
					((t_env*)list->content)->value = comm->export.value;
					comm->export.f_exist = 1;
				}
				list = list->next;
			}
			if (!comm->export.f_exist) //si la hemos recorrido y no estaba el id, alocamos un nuevo id con value copiados
			{
				new = malloc(sizeof(t_list));
				env = malloc(sizeof(t_env));
				new->content = env;
				((t_env*)new->content)->id = comm->export.id;
				((t_env*)new->content)->value = comm->export.value;
				ft_lstadd_back(&comm->env_head, new);
			}
		}
		i++;
	}
	if (comm->cmd.cmd[1] == NULL)
	{
		export_list(list, comm, split);
		export_print(list, comm, split);
		ft_lstclear(&comm->export_head, &free_export);

	}
}
