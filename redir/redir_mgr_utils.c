/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_mgr_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 19:34:57 by isoria-g          #+#    #+#             */
/*   Updated: 2021/11/20 19:36:40 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_redir_mgr(t_comm *comm, t_split *split)
{
	comm->redir.fdin = 0;
	comm->redir.fdout = 0;
	split->str = NULL;
}
