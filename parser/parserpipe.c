/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserpipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:22:26 by isoria-g          #+#    #+#             */
/*   Updated: 2021/11/22 14:25:35 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_splitpipe(t_list	*list, t_comm *comm, t_split *split, char *line)
{
	char	**aux;
	t_list	*new;
	t_comm	*otro;
		
	list = comm->parse_head;
	while (list)
	{
		split->u = 0;
		split->v = 0;
		if (((t_comm *)list->content)->t_word)
		{
			aux = ft_splitshell(split,
					((t_comm *)list->content)->t_word, '|');
			while (aux[split->u])
				split->u++;
			split->w = 0;
			if (split->u > 1)
			{
				while (split->v < split->u * 2 - 1 && list)
				{
					if (split->v == 0)
					{
						free(((t_comm *)list->content)->t_word);
						((t_comm *)list->content)->t_word = NULL;
						((t_comm *)list->content)->t_word
							= ft_strdup(aux[split->w]);
						split->w++;
					}
					else
					{
						new = ft_malloc(sizeof(t_list));
						otro = ft_malloc(sizeof(t_comm));
						new->content = otro;
						ft_init((t_comm *)new->content);
						if (split->v % 2 == 0 && split->v != 0)
						{
							((t_comm *)new->content)->t_word
								= ft_strdup(aux[split->w]);
							split->w++;
						}
						else if (split->v % 2 != 0)
							((t_comm *)new->content)->t_pipe = 1;
						ft_lstadd_middle(&list, &new);
						list = list->next;
					}
					split->v++;
				}
			}
			else
			{
				free(aux[0]);
				aux[0] = NULL;
			}
			ft_malloc_free(comm, aux, 0);
		}
		else
			free(((t_comm *)list->content)->t_word);
		list = list->next;
	}	
}
