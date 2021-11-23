/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_gt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:30:38 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/23 09:40:38 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	list_gt_flag(t_list **list, t_split *split, char **aux)
{
	t_list	*new;
	t_comm	*otro;

	new = ft_malloc(sizeof(t_list));
	otro = ft_malloc(sizeof(t_comm));
	new->content = otro;
	ft_init((t_comm *)new->content);
	if (split->v % 2 == 0 && split->v != 0)
	{
		((t_comm *)new->content)->t_word = ft_strdup(aux[split->w]);
		split->w++;
	}
	else if (split->v % 2 != 0)
		((t_comm *)new->content)->t_gt = 1;
	ft_lstadd_middle(list, &new);
	*list = ((*list)->next);
}

void	gt_flag_list(t_list *list, t_split *split, char **aux)
{
	while (split->v < split->u * 2 - 1 && list)
	{
		if (split->v == 0)
			list_no_flag(list, split, aux);
		else
			list_gt_flag(&list, split, aux);
		split->v++;
	}
}

void	ft_splitgt(t_list *list, t_comm *comm, t_split *split)
{
	char	**aux;

	list = comm->parse_head;
	while (list)
	{
		split->u = 0;
		split->v = 0;
		if (((t_comm *)list->content)->t_word)
		{
			aux = ft_splitshell(split, ((t_comm *)list->content)->t_word, '>');
			while (aux[split->u])
				split->u++;
			split->w = 0;
			if (split->u > 1)
				gt_flag_list(list, split, aux);
			else
				free_words(aux);
			ft_malloc_free(aux, 0);
		}
		else
			free(((t_comm *)list->content)->t_word);
		list = list->next;
	}
}
