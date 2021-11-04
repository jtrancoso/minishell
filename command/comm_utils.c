/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comm_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 13:52:19 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/04 14:17:42 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//void

char	**ft_superglue(t_list *list, t_comm *comm)
{
	char	**str;
	char	*aux;
	int		len;
	int		i;

	list = comm->env_head;
	len = ft_lstsize(list);
	str = malloc(sizeof(char *) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (list)
	{
		if (((t_env *)list->content)->value)
		{
			if (ft_strchr(((t_env *)list->content)->id, '='))
			{
				aux = ft_strjoin(((t_env *)list->content)->id,
						((t_env *)list->content)->value);
				str[i] = ft_strdup(aux);
				free(aux);
			}
			else
			{
				aux = ft_strjoin(((t_env *)list->content)->id, "=");
				str[i] = ft_strjoin(aux, ((t_env *)list->content)->value);
				free(aux);
			}
		}
		else
		{
			aux = ft_strdup(((t_env *)list->content)->id);
			str[i] = ft_strdup(aux);
			free (aux);
		}
		list = list->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

void	create_history(t_list *list, t_comm *comm, t_split *split)
{
	list = comm->env_head;
	while (list)
	{
		if (ft_strncmp(((t_env *)list->content)->id, "_", 1) == 0)
		{
			free(((t_env *)list->content)->value);
			if (comm->cmd.cmd[0])
				((t_env *)list->content)->value = ft_strdup(comm->cmd.cmd[0]);
			else
				((t_env *)list->content)->value = NULL;
		}
		list = list->next;
	}
}
