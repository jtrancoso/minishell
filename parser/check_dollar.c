/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:39:15 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/22 17:04:12 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_dollar(t_list *list, t_comm *comm, t_split *split)
{
	char	*dollar_id;

	list = comm->parse_head;
	while (list)
	{
		split->u = 0;
		split->v = 0;
		if (((t_comm *)list->content)->t_word)
		{
			if (ft_strchr(((t_comm *)list->content)->t_word, '$'))
			{
				dollar_id = ft_parsedollar(list, comm, split,
						((t_comm *)list->content)->t_word);
				free(((t_comm *)list->content)->t_word);
				((t_comm *)list->content)->t_word = ft_strdup(dollar_id);
				free(dollar_id);
			}
		}
		list = list->next;
	}
}
