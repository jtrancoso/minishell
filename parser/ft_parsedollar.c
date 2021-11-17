/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsedollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 13:46:08 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/17 11:26:48 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_var_parsedollar(t_list *list, t_comm *comm, t_split *split)
{
	split->s_quote = 0;
	split->d_quote = 0;
	split->k = 0;
	split->i = 0;
	split->j = 0;
	split->str = NULL;
}

int	check_ifdollar(t_split *split, char *line)
{
	if (line[split->i] != '$' || (line[split->i] == '$'
			&& split->f_simple != 0) || (line[split->i] == '$'
			&& line[split->i - 1] == '\\' && split->i != 0)
		|| (line[split->i] == '$' && (line[split->i + 1] == ' '
				|| line[split->i + 1] == '\0')) || (line[split->i] == '$'
			&& line[split->i - 1] == '\"' && line[split->i + 1] == '\"'))
		return (1);
	return (0);
}

void	is_dollar1(t_comm *comm, t_split *split, char *line, char *aux_id)
{
	split->i++;
	split->k = 0;
	while (line[split->i] != ' ' && line[split->i] != '\0'
		&& line[split->i] != '\"' && line[split->i] != '\''
		&& ((ft_isalnum(line[split->i]) || line[split->i] == '_'
				|| line[split->i] == '?')))
	{
		if (ft_isdigit(line[split->i]) && line[split->i - 1] == '$')
		{
			aux_id[split->k++] = line[split->i++];
			break ;
		}
		else
			aux_id[split->k++] = line[split->i++];
	}
	aux_id[split->k] = '\0';
	split->k = 0;
}

void	is_dollar2(t_comm *comm, t_split *split, char *aux, char *aux_id)
{
	char	*content;
	char	*aux2;

	if (aux_id[0] == '?')
		content = ft_askdollar(comm, split, aux_id);
	else
		content = expand_dollar(comm, aux_id);
	split->k = 0;
	if (content)
	{
		if (aux_id[0] == '?' && ft_strlen(aux_id) > 1)
		{
			aux2 = ft_strjoin(content, aux_id + 1);
			free(content);
			while (aux2[split->k])
				aux[split->j++] = aux2[split->k++];
			free (aux2);
		}
		else//FIXME: a ver el lio de las lineas y los mallocs
		{
			while (content[split->k])
				aux[split->j++] = content[split->k++];
			free (content);
		}
	}
}

char	*ft_parsedollar(t_list *list, t_comm *comm, t_split *split, char *line)
{
	char	*aux;
	char	*aux_id;
	char	*final_aux;

	init_var_parsedollar(list, comm, split);
	aux = ft_malloc(sizeof(char *) * (lenval(list, comm) * ndollar(line)) + 1);
	aux_id = ft_malloc(sizeof(char *) * (ft_strlen(line)));
	while (line[split->i])
	{
		if (check_inverted_var(&line[split->i]) == 1)
			split->i += 2;
		check_quote(split, &line[split->i]);
		if (check_ifdollar(split, line))
			aux[split->j++] = line[split->i];
		else if (line[split->i] == '$')
		{
			is_dollar1(comm, split, line, aux_id);
			is_dollar2(comm, split, aux, aux_id);
			split->i--;
		}
		split->i++;
	}
	aux[split->j] = '\0';
	free (aux_id);
	return (aux);
}
