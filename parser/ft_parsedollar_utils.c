/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsedollar_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:15:58 by isoria-g          #+#    #+#             */
/*   Updated: 2021/11/17 09:46:14 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ndollar(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$') //FIXME: si es dolar solo pues se pone 
			j++;
		i++;
	}
	return (j);
}

int		lenval(t_list *list, t_comm *comm)
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

char	*ft_strcpy(char *str) //TODO: Si al final de todo no se usa, ELIMINAR
{
	int		i;
	int		j;
	char	*aux;

	i = 0;
	j = 0;
	while (str[i])
	{
		aux[j] = str[i];
		i++;
		j++;
	}
	aux[j] = '\0';
	return (aux);
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
