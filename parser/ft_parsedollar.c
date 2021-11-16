/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsedollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 13:46:08 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/16 10:34:57 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_parsedollar(t_list *list, t_comm *comm, t_split *split, char *line)
{
	char	*aux;
	char	*aux2;
	char	*aux_id;
	char	*final_aux;
	int		lmax;
	int		i;
	int		j;
	int		q;
	char	*content;

	list = comm->env_head;
	lmax = 0;
	i = 0;
	j = 0;
	q = 0;
	while (line[i])
	{
		if (line[i] == '$') //FIXME: si es dolar solo pues se pone 
			j++;
		i++;
	}
	while (list)
	{
		if (((t_env *)list->content)->value)
		{
			if (ft_strlen(((t_env *)list->content)->value) > lmax)
				lmax = ft_strlen(((t_env *)list->content)->value);
		}
		list = list->next;
	}
	aux = ft_malloc(sizeof(char *) * (lmax * j) + 1);
	aux_id = ft_malloc(sizeof(char *) * (ft_strlen(line)));
	i = 0;
	j = 0;
	split->f_simple = 0;
	split->f_double = 0;
	while (line[i])
	{
		if (check_inverted_var(&line[i]) == 1)
			i += 2;
		check_quote(split, &line[i]);
		if (line[i] != '$' || (line[i] == '$' && split->f_simple != 0)
			|| (line[i] == '$' && line[i - 1] == '\\' && i != 0)
			|| (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			|| (line[i] == '$' && line[i - 1] == '\"' && line[i + 1] == '\"'))
			aux[j++] = line[i];
		else if (line[i] == '$')
		{
			i++;
			q = 0;
			while (line[i] != ' ' && line[i] != '\0' && line[i] != '\"'
				&& line[i] != '\'' && ((ft_isalnum(line[i]) || line[i] == '_'
						|| line[i] == '?')))
			{
				if (ft_isdigit(line[i]) && line[i - 1] == '$')
				{
					aux_id[q++] = line[i++];
					break ;
				}
				else
					aux_id[q++] = line[i++];
			}
			aux_id[q] = '\0';
			if (aux_id[0] == '?')
				content = ft_askdollar(comm, split, aux_id);
			else
				content = expand_dollar(comm, aux_id);
			q = 0;
			if (content)
			{
				if (aux_id[0] == '?' && ft_strlen(aux_id) > 1)
				{
					aux2 = ft_strjoin(content, aux_id + 1);
					free(content);
					while (aux2[q])
						aux[j++] = aux2[q++];
					free (aux2);
				}
				else//FIXME: a ver el lio de las lineas y los mallocs
				{
					while (content[q])
						aux[j++] = content[q++];
					free (content);
				}
			}
			i--;
		}
		i++;
	}
	aux[j] = '\0';
	free (aux_id);
	return (aux);
}
