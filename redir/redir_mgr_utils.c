/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_mgr_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 19:34:57 by isoria-g          #+#    #+#             */
/*   Updated: 2021/11/23 16:41:41 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_redir_mgr(t_comm *comm, t_split *split)
{
	comm->redir.fdin = 0;
	comm->redir.fdout = 0;
	split->str = NULL;
}
