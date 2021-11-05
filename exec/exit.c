/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:27:45 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/05 11:16:21 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_exit(t_list *list, t_comm *comm, t_split *split)
{ 
	ft_lstclear(&comm->env_head, &free_env);  //TODO: proteger que exista para -i
	ft_lstclear(&comm->parse_head, &free_list);
	free(comm->user);
	free(comm->cmd.path);
	free(comm->dir);
	ft_malloc_free(comm, comm->cmd.cmd, 0);
	ft_malloc_free(comm, comm->cmd.env_array, 0);
	exit(split->errorcode);
}