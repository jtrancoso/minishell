/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:31:30 by jtrancos          #+#    #+#             */
/*   Updated: 2021/06/23 14:09:36 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test_list(t_list *list, t_comm *comm)
{
	list = comm->parse_head;
	while (list)
	{
		//printf("id: %s value: %s\n", ((t_env*)list->content)->id, ((t_env*)list->content)->value);
		printf("word: %s pipe: %d semi: %d gtgt: %d gt: %d lt: %d\n", ((t_comm*)list->content)->t_word, ((t_comm*)list->content)->t_pipe, ((t_comm*)list->content)->t_semi, ((t_comm*)list->content)->t_gtgt, ((t_comm*)list->content)->t_gt, ((t_comm*)list->content)->t_lt);
		list = list->next;
	}
	printf("\n");
	/*list = comm->env_head;
	while (list)
	{
		printf("id: %s value: %s\n", ((t_env*)list->content)->id, ((t_env*)list->content)->value);
		//printf("word: %s pipe: %d semi: %d\n", ((t_comm*)list->content)->t_word, ((t_comm*)list->content)->t_pipe, ((t_comm*)list->content)->t_semi);
		list = list->next;
	}*/
}
