/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:51:07 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/22 16:54:21 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_words(t_comm *comm, char **aux)
{
	free(aux[0]);
	aux[0] = NULL;
}

void	list_no_flag(t_list *list, t_comm *comm, t_split *split, char **aux)
{
	free(((t_comm *)list->content)->t_word);
	((t_comm *)list->content)->t_word = NULL;
	((t_comm *)list->content)->t_word = ft_strdup(aux[split->w]);
	split->w++;
}
