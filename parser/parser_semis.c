/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_semis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:56:48 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/22 20:24:44 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_splitsemi(t_comm *comm, t_split *split, char **line)
{
	char	**aux;
	t_list	*new;
	t_comm	*otro;

	aux = line;
	comm->parse_head = NULL;
	while (split->v < split->u * 2 - 1)
	{
		new = ft_malloc(sizeof(t_list));
		otro = ft_malloc(sizeof(t_comm));
		new->content = otro;
		ft_init((t_comm *)new->content);
		if (split->v == 0 || split->v % 2 == 0)
		{
			((t_comm *)new->content)->t_word = ft_strdup(aux[split->w]);
			split->w++;
		}
		if (split->v % 2 != 0)
			((t_comm *)new->content)->t_semi = 1;
		ft_lstadd_back(&comm->parse_head, new);
		split->v++;
	}
	ft_malloc_free(aux, 0);
}
