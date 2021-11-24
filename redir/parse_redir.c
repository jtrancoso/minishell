/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:22:11 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/24 09:18:50 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_file(t_list *list, char *aux)
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

void	parse_redir(t_list *list, t_comm *comm)
{
	int		i;
	char	*aux;

	list = comm->parse_head;
	while (list)
	{
		if (((t_comm *)list->content)->t_word == NULL)
			i = 0;
		if (((t_comm *)list->content)->t_gt == 1
			|| ((t_comm *)list->content)->t_gtgt == 1
			|| ((t_comm *)list->content)->t_lt == 1)
		{
			while (ft_isspace(((t_comm *)list->next->content)->t_word[i]))
				i++;
			aux = ft_strdup(((t_comm *)list->next->content)->t_word + i);
			get_file(list, aux);
			free (aux);
		}
		list = list->next;
	}
}
