/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:22:11 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/18 19:00:51 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_file(t_list *list, t_comm *comm, char *aux)
{
	char	*file;
	char	*rest;

	if (ft_strchr(aux, ' '))
	{
		file = ft_substr(aux, 0, ft_strchr(aux, ' ') - aux);
		((t_comm *)list->content)->redir.file = file;
		rest = ft_substr(aux, ft_strchr(aux, ' ') - aux, ft_strlen(aux));
		((t_comm *)list->content)->redir.rest = rest;
	}
	else
	{
		file = ft_strdup(aux);
		((t_comm *)list->content)->redir.file = file;
	}
}

void	parse_redir(t_list *list, t_comm *comm, t_split *split)
{
	int		i;
	char	*aux;

	list = comm->parse_head;
	while (list)
	{
		if (((t_comm*)list->content)->t_word == NULL)
		i = 0;
		if (((t_comm *)list->content)->t_gt == 1
			|| ((t_comm *)list->content)->t_gtgt == 1
			|| ((t_comm *)list->content)->t_lt == 1)
		{
			while (ft_isspace(((t_comm *)list->next->content)->t_word[i]))
				i++;
			aux = ft_strdup(((t_comm *)list->next->content)->t_word + i);
			get_file(list, comm, aux);
			free (aux);
		}
			list = list->next;
	}
}
