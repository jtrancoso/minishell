/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:31:30 by jtrancos          #+#    #+#             */
/*   Updated: 2021/05/20 16:31:02 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test_list(t_list *list, t_comm *comm)
{
	list = comm->parse_head;
	while (list)
	{
		//printf("id: %s value: %s\n", ((t_env*)list->content)->id, ((t_env*)list->content)->value);
		printf("word: %s pipe: %d semi: %d\n", ((t_comm*)list->content)->t_word, ((t_comm*)list->content)->t_pipe, ((t_comm*)list->content)->t_semi);
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
