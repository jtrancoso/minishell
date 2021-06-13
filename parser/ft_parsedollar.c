/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsedollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 13:46:08 by jtrancos          #+#    #+#             */
/*   Updated: 2021/06/13 10:43:56 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_parsedollar(t_list *list, t_comm *comm, char *line)
{
	char *aux;
	int	lmax;

	list = comm->env_head;
	lmax = 0;
	while (list)
	{
		printf("id: %s\nvalue: %s \n", (((t_env*)list->content)->id),(((t_env*)list->content)->value));
		if (ft_strlen(((t_env*)list->content)->value) > lmax)
			lmax = ft_strlen(((t_env*)list->content)->value);
		list = list->next;
	}
	printf("lmax: %d", lmax);
	return ("hola");

}