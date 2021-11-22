/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsedollar_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:15:58 by isoria-g          #+#    #+#             */
/*   Updated: 2021/11/22 17:07:26 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ndollar(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$')
			j++;
		i++;
	}
	return (j);
}

int	lenval(t_list *list, t_comm *comm)
{
	int	lmax;

	list = comm->env_head;
	while (list)
	{
		if (((t_env *)list->content)->value)
		{
			if (ft_strlen(((t_env *)list->content)->value) > lmax)
				lmax = ft_strlen(((t_env *)list->content)->value);
		}
		list = list->next;
	}
	return (lmax);
}

char	*expand_dollar(t_comm *comm, char *aux_id)
{
	t_list	*list;
	int		i;
	char	*content;

	list = comm->env_head;
	i = 0;
	i = ft_strlen(aux_id);
	content = ft_strdup("");
	while (list)
	{
		if (ft_strncmp(((t_env *)list->content)->id, aux_id, i) == 0)
		{
			free (content);
			content = ft_strdup(((t_env *)list->content)->value);
		}
		list = list->next;
	}
	return (content);
}

char	*ft_askdollar(t_comm *comm, t_split *split, char *aux_id)
{
	char	*value;

	value = ft_itoa(split->errorcode);
	return (value);
}
