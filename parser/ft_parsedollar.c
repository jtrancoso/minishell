/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsedollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 13:46:08 by jtrancos          #+#    #+#             */
/*   Updated: 2021/06/10 13:58:03 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_parsedollar(t_list *list, t_comm *comm, char *line)
{
	char *aux;

	list = comm->env_head;
	while (list)
	{
		printf("id: %s\nvalue: %s \n", (((t_env*)list->content)->id),(((t_env*)list->content)->value));
		list = list->next;
	}
	return ("hola");

}