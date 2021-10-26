/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:22:11 by jtrancos          #+#    #+#             */
/*   Updated: 2021/10/26 13:16:01 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_redir(t_list *list, t_comm *comm, t_split *split)
{
	int i;
	char *aux;
	char *file; //FIXME: si faltan lineas, podemos jugar con solo un extra char y liberarlo
	char *rest;

	i = 0;
	if (((t_comm*)list->content)->t_gt == 1)
	{
		while (ft_isspace(((t_comm*)list->next->content)->t_word[i]))
			i++;
		aux = ft_strdup(((t_comm*)list->next->content)->t_word + i);
		if (ft_strchr(aux, ' '))
		{
			file = ft_substr(aux, 0, ft_strchr(aux, ' ') - aux);
			((t_comm*)list->content)->redir.file = file;
			rest = ft_substr(aux, ft_strchr(aux, ' ') - aux, ft_strlen(aux));
			((t_comm*)list->content)->redir.rest = rest;
		}
		else
		{
			file = ft_strdup(aux);
			((t_comm*)list->content)->redir.file = file;
		}
		free (aux);
	}
	else if (((t_comm*)list->content)->t_gtgt == 1)
	{
		while (ft_isspace(((t_comm*)list->next->content)->t_word[i]))
			i++;
		aux = ft_strdup(((t_comm*)list->next->content)->t_word + i);
		if (ft_strchr(aux, ' '))
		{
			file = ft_substr(aux, 0, ft_strchr(aux, ' ') - aux);
			((t_comm*)list->content)->redir.file = file;
			rest = ft_substr(aux, ft_strchr(aux, ' ') - aux, ft_strlen(aux));
			((t_comm*)list->content)->redir.rest = rest;
		}
		else
		{
			file = ft_strdup(aux);
			((t_comm*)list->content)->redir.file = file;
		}
		free (aux);
	}
	else if (((t_comm*)list->content)->t_lt == 1)
	{
		while (ft_isspace(((t_comm*)list->next->content)->t_word[i]))
			i++;
		aux = ft_strdup(((t_comm*)list->next->content)->t_word + i);
		if (ft_strchr(aux, ' '))
		{
			file = ft_substr(aux, 0, ft_strchr(aux, ' ') - aux);
			((t_comm*)list->content)->redir.file = file;
			rest = ft_substr(aux, ft_strchr(aux, ' ') - aux, ft_strlen(aux));
			((t_comm*)list->content)->redir.rest = rest;
		}
		else
		{
			file = ft_strdup(aux);
			((t_comm*)list->content)->redir.file = file;
		}
		free (aux);
	}
	/*
	else if (((t_comm*)list->content)->t_ltlt == 1)
	{

	}*/
}