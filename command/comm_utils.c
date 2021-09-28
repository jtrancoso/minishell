/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comm_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 13:52:19 by jtrancos          #+#    #+#             */
/*   Updated: 2021/09/28 13:53:09 by jtrancos         ###   ########.fr       */
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
		if (((t_env*)list->content)->value)
		{
			aux = ft_strjoin(((t_env*)list->content)->id, "=");
			str[i] = ft_strjoin(aux, ((t_env*)list->content)->value);
			free(aux);
			list = list->next;
			i++;
		}
	}
	str[i] = NULL;
	return(str);
}