/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_mgr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 12:19:48 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/18 18:50:20 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	manage_redir(t_list **list, t_comm *comm, t_split *split)
{
	char	*str;
	char	*aux;

	comm->redir.fdin = 0;
	comm->redir.fdout = 0;
	str = NULL;
	while (*list)
	{
		if (((t_comm *)((*list)->content))->t_word && !str)
			str = ft_strdup(((t_comm *)((*list)->content))->t_word);
		else if (!((t_comm *)((*list)->content))->t_word && str)
		{
			aux = str;
			if (((t_comm *)((*list)->content))->redir.rest)
			{
				str = ft_strjoin(str, ((t_comm *)((*list)
								->content))->redir.rest);
				free (aux);
			}
			if (comm->redir.fdout)
				close(comm->redir.fdout);
			if (comm->redir.fdin)
				close(comm->redir.fdin);
			if (((t_comm *)((*list)->content))->t_gt)
				comm->redir.fdout = \
					open(((t_comm *)((*list)->content))->redir.file, O_RDWR
						| O_TRUNC | O_CREAT, 0700);
			if (((t_comm *)((*list)->content))->t_gtgt)
				comm->redir.fdout = \
					open(((t_comm *)((*list)->content))->redir.file, O_RDWR
						| O_APPEND | O_CREAT, 0700);
			if (comm->redir.fdout)
				comm->redir.real_fdout = dup(1);
			if (((t_comm *)((*list)->content))->t_lt)
				comm->redir.fdin = \
					open(((t_comm *)((*list)->content))->redir.file, O_RDONLY);
			if (comm->redir.fdin)
				comm->redir.real_fdin = dup(0);
		}
		if ((((*list)->next) && ((((t_comm *)((*list)->next)->content)->t_semi) == 1 || (((t_comm *)((*list))->content)->post_pipe))) || ((*list)->next) == NULL ) //FIXME: reevaluar uso de pages
		{
			((t_comm *)((*list)->content))->t_command = ft_strdup(str);
			if (str)
				free(str);
			if (comm->redir.fdout)
				dup2(comm->redir.fdout, 1);
			if (comm->redir.fdin)
				dup2(comm->redir.fdin, 0);
			parse_command(*list, comm, split); 
			if (comm->redir.fdout)
			{
				close(comm->redir.fdout);
				dup2(comm->redir.real_fdout, 1);
				close (comm->redir.real_fdout);
			}
			if (comm->redir.fdin)
			{
				close(comm->redir.fdin);
				dup2(comm->redir.real_fdin, 0);
				close(comm->redir.real_fdin);
			}
			if (((*list)->next) && ((t_comm *)((*list)->content))->post_pipe == 0)
				*list = ((*list)->next);
			else
				break ;
		}
		if (((*list)->next) && ((t_comm *)((*list)->content))->t_semi == 0)
		{
			if (((t_comm *)((*list)->content))->t_pipe == 1)
				str = NULL;
			*list = ((*list)->next);
		}
		else
			return ;
	}
}
