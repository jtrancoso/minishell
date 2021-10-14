/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:27:45 by jtrancos          #+#    #+#             */
/*   Updated: 2021/10/14 13:09:40 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_exit(t_list *list, t_comm *comm)
{
	ft_lstclear(&comm->env_head, &free_env);
	ft_lstclear(&comm->parse_head, &free_list);
	free(comm->user);
	free(comm->cmd.path);
	free(comm->dir);
	ft_malloc_free(comm, comm->cmd.cmd, 0);
	ft_malloc_free(comm, comm->cmd.env_array, 0);
	exit(0);
}