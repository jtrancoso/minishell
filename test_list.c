/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:31:30 by jtrancos          #+#    #+#             */
/*   Updated: 2021/10/22 13:06:21 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test_list(t_list *list, t_comm *comm)
{
	/*list = comm->parse_head;
	while (list)
	{
		//printf("id: %s value: %s\n", ((t_env*)list->content)->id, ((t_env*)list->content)->value);
		printf("word: %s pipe: %d semi: %d gtgt: %d ltlt: %d gt: %d lt: %d, page: %d file: %s rest: %s\n", ((t_comm*)list->content)->t_word, ((t_comm*)list->content)->t_pipe, ((t_comm*)list->content)->t_semi, ((t_comm*)list->content)->t_gtgt, ((t_comm*)list->content)->t_ltlt, ((t_comm*)list->content)->t_gt, ((t_comm*)list->content)->t_lt, ((t_comm*)list->content)->page, ((t_comm*)list->content)->redir.file, ((t_comm*)list->content)->redir.rest);
		list = list->next;
	}
	printf("\n");
	list = comm->export_head;
	while (list)
	{
		//printf("id: %s value: %s\n", ((t_env*)list->content)->id, ((t_env*)list->content)->value);
		printf("id: %s", ((t_export*)list->content)->id);
		printf(" value: %s", ((t_export*)list->content)->value);
		printf("\n");
		list = list->next;
	}*/
	list = comm->env_head;
	while (list)
	{
		printf("id: %s value: %s\n", ((t_env*)list->content)->id, ((t_env*)list->content)->value);
		//printf("word: %s pipe: %d semi: %d\n", ((t_comm*)list->content)->t_word, ((t_comm*)list->content)->t_pipe, ((t_comm*)list->content)->t_semi);
		list = list->next;
	}
}
